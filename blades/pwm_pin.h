#ifndef BLADES_PWM_PIN_H
#define BLADES_PWM_PIN_H

#include "led_interface.h"

// First some abstractions for controlling PWM pin
#ifdef TEENSYDUINO
void LSanalogWriteSetup(uint32_t pin) {
  analogWriteResolution(16);
  analogWriteFrequency(pin, 1000);
}
void LSanalogWriteTeardown(uint32_t pin) {}
void LSanalogWrite(uint32_t pin, int value) {
  analogWrite(pin, value);
}
#else
#include <stm32l4_timer.h>

namespace {

static stm32l4_timer_t stm32l4_pwm[PWM_INSTANCE_COUNT];
static uint8_t timer_use_counts[PWM_INSTANCE_COUNT];

#define PWM_SYNC_INSTANCE 3  // TIM15

#ifdef ULTRA_PROFFIE
static uint8_t activeChannels[4];
#endif

void SetupTimer(uint32_t instance) {
#ifndef ULTRA_PROFFIE
  timer_use_counts[instance]++;
  if (stm32l4_pwm[instance].state == TIMER_STATE_NONE) {
    stm32l4_timer_create(&stm32l4_pwm[instance], g_PWMInstances[instance], 15, 0);
  }

  if (stm32l4_pwm[instance].state == TIMER_STATE_INIT) {
    // 813 Hz, 32768 steps
    uint32_t carrier = 26666666;
    uint32_t modulus = 32768;
    uint32_t divider = stm32l4_timer_clock(&stm32l4_pwm[instance]) / carrier;
    
    if (divider == 0) divider = 1;
    
    stm32l4_timer_enable(&stm32l4_pwm[instance], divider -1, modulus -1, 0, NULL, NULL, 0);
    stm32l4_timer_start(&stm32l4_pwm[instance], false);
    if (instance != PWM_SYNC_INSTANCE)  {
      SetupTimer(PWM_SYNC_INSTANCE);
      // TIM16 cannot be synchronized in hardware, so let's do the best we can.
      // We use TIM15 to synchromize with, because it is used for PWM on all proffieboards.
      volatile uint32_t* from = &stm32l4_pwm[PWM_SYNC_INSTANCE].TIM->CNT;
      volatile uint32_t* to = &stm32l4_pwm[instance].TIM->CNT;
      noInterrupts();
      *to = *from + 10;
      interrupts();
    } else {
      // avoid slow startup
      stm32l4_pwm[instance].TIM->CNT = 0;
    }
    // Buffer counters from now on.
    stm32l4_pwm[instance].TIM->CR1 |= TIM_CR1_ARPE;
  }
#else
  if(instance == TIMER_INSTANCE_TIM2) {
    if (stm32l4_pwm[instance].state == TIMER_STATE_NONE) {
        stm32l4_timer_create(&stm32l4_pwm[instance], g_PWMInstances[instance], 10, 0);
    }
    if (stm32l4_pwm[instance].state == TIMER_STATE_INIT) {
        uint32_t carrier = 26666666;
        uint32_t modulus = 32768;
        uint32_t divider = stm32l4_timer_clock(&stm32l4_pwm[instance]) / carrier;
    
        if (divider == 0) divider = 1;
        stm32l4_timer_enable(&stm32l4_pwm[instance], divider-1, modulus -1, TIMER_OPTION_COUNT_PRELOAD, NULL, NULL, 0);
        stm32l4_pwm[instance].TIM->EGR = TIM_EGR_UG;          // update enable 
        stm32l4_timer_start(&stm32l4_pwm[instance], false);

    }
  }
#endif
}

void TeardownTimer(uint32_t instance) {
#ifndef ULTRA_PROFFIE
  if (0 == --timer_use_counts[instance]) {
    stm32l4_timer_stop(&stm32l4_pwm[instance]);
    stm32l4_timer_disable(&stm32l4_pwm[instance]);
    if (instance != PWM_SYNC_INSTANCE) {
      TeardownTimer(PWM_SYNC_INSTANCE);
    }
  }
#else 
  if(activeChannels[0] == 0 && activeChannels[1] == 0 &&  activeChannels[2] == 0 && activeChannels[3] == 0)
  {
    stm32l4_timer_stop(&stm32l4_pwm[instance]);
    stm32l4_timer_disable(&stm32l4_pwm[instance]);
  }
#endif
}

void LSanalogWriteSetup(uint32_t pin) {
  // Handle the case the pin isn't usable as PIO
  if (pin >= NUM_TOTAL_PINS || g_APinDescription[pin].GPIO == NULL) {
    STDOUT.print("Analog Setup: NOT A PIN: ");
    STDOUT.println(pin);
    return;
  }
  
  if (!(g_APinDescription[pin].attr & PIN_ATTR_PWM)) {
    STDOUT.println("Analog Setup: Pin is not configured for PWM: ");
    STDOUT.println(pin);
    return;
  }
  uint32_t instance = g_APinDescription[pin].pwm_instance;
#ifndef ULTRA_PROFFIE  
  SetupTimer(instance);
  stm32l4_timer_channel(&stm32l4_pwm[instance], g_APinDescription[pin].pwm_channel, 0, TIMER_CONTROL_PWM);
  stm32l4_gpio_pin_configure(g_APinDescription[pin].pin, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
#else
  SetupTimer(instance);
  stm32l4_timer_channel(&stm32l4_pwm[instance], g_APinDescription[pin].pwm_channel, 0, TIMER_CONTROL_PWM); 
  stm32l4_gpio_pin_configure(g_APinDescription[pin].pin, (GPIO_PUPD_PULLDOWN | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
  activeChannels[g_APinDescription[pin].pwm_channel] = 1;
#endif
}

void LSanalogWriteTeardown(uint32_t pin) {
#ifndef ULTRA_PROFFIE  
  pinMode(pin, INPUT_ANALOG);
  TeardownTimer(g_APinDescription[pin].pwm_instance);
#else 
  activeChannels[g_APinDescription[pin].pwm_channel] = 0;
  // pinMode(pin, INPUT_ANALOG);	// TODO was active , chek on power manager 
  TeardownTimer(g_APinDescription[pin].pwm_instance);

#endif
}

void LSanalogWrite(uint32_t pin, int value) {
  TIM_TypeDef* TIM = stm32l4_pwm[g_APinDescription[pin].pwm_instance].TIM;
#ifndef OSx
  value >>= 1;
#endif
  if (value < 0) value = 0;  if (value > 32767) value = 32767;
  // stm32l4_timer_channel(&stm32l4_pwm[instance], g_APinDescription[pin].pwm_channel, value, TIMER_CONTROL_PWM);
  switch (g_APinDescription[pin].pwm_channel) {
    case TIMER_CHANNEL_1: TIM->CCR1 = value; break;
    case TIMER_CHANNEL_2: TIM->CCR2 = value; break;
    case TIMER_CHANNEL_3: TIM->CCR3 = value; break;
    case TIMER_CHANNEL_4: TIM->CCR4 = value; break;
    case TIMER_CHANNEL_5: TIM->CCR5 = value; break;
    case TIMER_CHANNEL_6: TIM->CCR6 = value; break;
  }
}

};
#endif

class PWMPinInterface {
public:
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
  virtual void set(const Color16& c) = 0;
  virtual void set_overdrive(const Color16& c) = 0;
  virtual bool rgb() { return false; }
};

template<int PIN>
class SimplePWMPin {
public:
  void Activate() {
    static_assert(PIN >= -1, "PIN is negative");
    LSanalogWriteSetup(PIN);
    LSanalogWrite(PIN, 0);  // make it black
  }
  void Deactivate() {
    LSanalogWrite(PIN, 0);  // make it black
    LSanalogWriteTeardown(PIN);
  }
  void set(int32_t v) {
    LSanalogWrite(PIN, v);
  }
};

#endif
