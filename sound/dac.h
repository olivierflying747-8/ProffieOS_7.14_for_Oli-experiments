#ifndef SOUND_DAC_H
#define SOUND_DAC_H

#include "filter.h"

#if defined(__IMXRT1062__)
void set_audioClock(int nfact, int32_t nmult, uint32_t ndiv,  bool force = false); // sets PLL4
#endif

#ifdef USE_I2S

#ifdef TEENSYDUINO
// MCLK needs to be 48e6 / 1088 * 256 = 11.29411765 MHz -> 44.117647 kHz sample rate
//
#if defined(KINETISK) || defined(KINETISL)

#if F_CPU == 96000000 || F_CPU == 48000000 || F_CPU == 24000000
  // PLL is at 96 MHz in these modes
  #define MCLK_MULT 2
  #define MCLK_DIV  17
#elif F_CPU == 72000000
  #define MCLK_MULT 8
  #define MCLK_DIV  51
#elif F_CPU == 120000000
  #define MCLK_MULT 8
  #define MCLK_DIV  85
#elif F_CPU == 144000000
  #define MCLK_MULT 4
  #define MCLK_DIV  51
#elif F_CPU == 168000000
  #define MCLK_MULT 8
  #define MCLK_DIV  119
#elif F_CPU == 180000000
  #define MCLK_MULT 16
  #define MCLK_DIV  255
  #define MCLK_SRC  0
#elif F_CPU == 192000000
  #define MCLK_MULT 1
  #define MCLK_DIV  17
#elif F_CPU == 216000000
  #define MCLK_MULT 8
  #define MCLK_DIV  153
  #define MCLK_SRC  0
#elif F_CPU == 240000000
  #define MCLK_MULT 4
  #define MCLK_DIV  85
#elif F_CPU == 16000000
  #define MCLK_MULT 12
  #define MCLK_DIV  17
#else
  #error "This CPU Clock Speed is not supported.";
#endif

#ifndef MCLK_SRC
#if F_CPU >= 20000000
  #define MCLK_SRC  3  // the PLL
#else
  #define MCLK_SRC  0  // system clock
#endif
#endif

#endif // KINETISK/L

#define CHANNELS 2

#else // TEENSYDUINO

#define CHANNELS 1


void my_stm32l4_system_saiclk_configure_22579200()
{
  RCC->PLLSAI1CFGR &= ~RCC_PLLSAI1CFGR_PLLSAI1PEN;
  RCC->CR &= ~RCC_CR_PLLSAI1ON;

  /* Wait till the PLLSAI1 is turned off */
  while (RCC->CR & RCC_CR_PLLSAI1RDY) {}

  RCC->PLLSAI1CFGR = ((11 << 27) | (62 << 8) | RCC_PLLSAI1CFGR_PLLSAI1PEN);
  RCC->CR |= RCC_CR_PLLSAI1ON;

  /* Wait till the PLLSAI1 is ready */
  while (!(RCC->CR & RCC_CR_PLLSAI1RDY)){}
}

#endif

#else   // USE_I2S
#define CHANNELS 1
#endif  // USE_I2S

#define PDB_CONFIG (PDB_SC_TRGSEL(15) | PDB_SC_PDBEN | PDB_SC_CONT | PDB_SC_PDBIE | PDB_SC_DMAEN)


  #if defined(USE_DAC) && defined(ULTRA_PROFFIE)

#include "stm32l4_timer.h"
#include "stm32l4_dac.h"
#include "stm32l4_dma.h"
#include "stm32l4_gpio.h"

stm32l4_timer_t stm32l4_dac1Timer;
stm32l4_dac_t stm32l4_dac1;
uint32_t timPeriphClock;
// stm32l4_dma_t stm32l4_dac1DMA;


#endif

class LS_DAC : CommandParser, Looper {
public:
  virtual void Loop() override {}
  virtual const char* name() { return "DAC"; }
  void Setup() override {
    if (!needs_setup_) return;
    needs_setup_ = false;

#ifdef TEENSYDUINO
    dma.begin(true); // Allocate the DMA channel first

  #ifdef USE_I2S

    #if defined(KINETISK) || defined(KINETISL)
        SIM_SCGC6 |= SIM_SCGC6_I2S;
        SIM_SCGC7 |= SIM_SCGC7_DMA;
        SIM_SCGC6 |= SIM_SCGC6_DMAMUX;

        // enable MCLK output
        I2S0_MCR = I2S_MCR_MICS(MCLK_SRC) | I2S_MCR_MOE;
        while (I2S0_MCR & I2S_MCR_DUF) ;
        I2S0_MDR = I2S_MDR_FRACT((MCLK_MULT-1)) | I2S_MDR_DIVIDE((MCLK_DIV-1));

        // configure transmitter
        I2S0_TMR = 0;
        I2S0_TCR1 = I2S_TCR1_TFW(1);  // watermark at half fifo size
        I2S0_TCR2 = I2S_TCR2_SYNC(0) | I2S_TCR2_BCP | I2S_TCR2_MSEL(1)
          | I2S_TCR2_BCD | I2S_TCR2_DIV(3);
        I2S0_TCR3 = I2S_TCR3_TCE;
        I2S0_TCR4 = I2S_TCR4_FRSZ(1) | I2S_TCR4_SYWD(15) | I2S_TCR4_MF
          | I2S_TCR4_FSE | I2S_TCR4_FSP | I2S_TCR4_FSD;
        I2S0_TCR5 = I2S_TCR5_WNW(15) | I2S_TCR5_W0W(15) | I2S_TCR5_FBT(15);

        // configure pin mux for 3 clock signals
        CORE_PIN23_CONFIG = PORT_PCR_MUX(6); // pin 23, PTC2, I2S0_TX_FS (LRCLK)
        CORE_PIN9_CONFIG  = PORT_PCR_MUX(6); // pin  9, PTC3, I2S0_TX_BCLK
        CORE_PIN22_CONFIG = PORT_PCR_MUX(6); // pin 22, PTC1, I2S0_TXD0

    #elif defined(__IMXRT1062__)

        CCM_CCGR5 |= CCM_CCGR5_SAI1(CCM_CCGR_ON);
        int fs = AUDIO_RATE;
        // PLL between 27*24 = 648MHz und 54*24=1296MHz
        int n1 = 4; //SAI prescaler 4 => (n1*n2) = multiple of 4
        int n2 = 1 + (24000000 * 27) / (fs * 256 * n1);

        double C = ((double)fs * 256 * n1 * n2) / 24000000;
        int c0 = C;
        int c2 = 10000;
        int c1 = C * c2 - (c0 * c2);
        set_audioClock(c0, c1, c2);

        // clear SAI1_CLK register locations
        CCM_CSCMR1 = (CCM_CSCMR1 & ~(CCM_CSCMR1_SAI1_CLK_SEL_MASK))
          | CCM_CSCMR1_SAI1_CLK_SEL(2); // &0x03 // (0,1,2): PLL3PFD0, PLL5, PLL4
        CCM_CS1CDR = (CCM_CS1CDR & ~(CCM_CS1CDR_SAI1_CLK_PRED_MASK | CCM_CS1CDR_SAI1_CLK_PODF_MASK))
          | CCM_CS1CDR_SAI1_CLK_PRED(n1-1) // &0x07
          | CCM_CS1CDR_SAI1_CLK_PODF(n2-1); // &0x3f

        // Select MCLK
        IOMUXC_GPR_GPR1 = (IOMUXC_GPR_GPR1
                          & ~(IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK))
          | (IOMUXC_GPR_GPR1_SAI1_MCLK_DIR | IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(0));

        CORE_PIN23_CONFIG = 3;  //1:MCLK
        CORE_PIN21_CONFIG = 3;  //1:RX_BCLK
        CORE_PIN20_CONFIG = 3;  //1:RX_SYNC

        int rsync = 0;
        int tsync = 1;

        I2S1_TMR = 0;
        //I2S1_TCSR = (1<<25); //Reset
        I2S1_TCR1 = I2S_TCR1_RFW(1);
        I2S1_TCR2 = I2S_TCR2_SYNC(tsync) | I2S_TCR2_BCP // sync=0; tx is async;
          | (I2S_TCR2_BCD | I2S_TCR2_DIV((1)) | I2S_TCR2_MSEL(1));
        I2S1_TCR3 = I2S_TCR3_TCE;
        I2S1_TCR4 = I2S_TCR4_FRSZ((2-1)) | I2S_TCR4_SYWD((32-1)) | I2S_TCR4_MF
          | I2S_TCR4_FSD | I2S_TCR4_FSE | I2S_TCR4_FSP;
        I2S1_TCR5 = I2S_TCR5_WNW((32-1)) | I2S_TCR5_W0W((32-1)) | I2S_TCR5_FBT((32-1));

        I2S1_RMR = 0;
        //I2S1_RCSR = (1<<25); //Reset
        I2S1_RCR1 = I2S_RCR1_RFW(1);
        I2S1_RCR2 = I2S_RCR2_SYNC(rsync) | I2S_RCR2_BCP  // sync=0; rx is async;
          | (I2S_RCR2_BCD | I2S_RCR2_DIV((1)) | I2S_RCR2_MSEL(1));
        I2S1_RCR3 = I2S_RCR3_RCE;
        I2S1_RCR4 = I2S_RCR4_FRSZ((2-1)) | I2S_RCR4_SYWD((32-1)) | I2S_RCR4_MF
          | I2S_RCR4_FSE | I2S_RCR4_FSP | I2S_RCR4_FSD;
        I2S1_RCR5 = I2S_RCR5_WNW((32-1)) | I2S_RCR5_W0W((32-1)) | I2S_RCR5_FBT((32-1));

        CORE_PIN7_CONFIG  = 3;  //1:TX_DATA0
    #endif

    #if defined(KINETISK)
        dma.TCD->SADDR = dac_dma_buffer;
        dma.TCD->SOFF = 2;
        dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
        dma.TCD->NBYTES_MLNO = 2;
        dma.TCD->SLAST = -sizeof(dac_dma_buffer);
        dma.TCD->DADDR = &I2S0_TDR0;
        dma.TCD->DOFF = 0;
        dma.TCD->CITER_ELINKNO = sizeof(dac_dma_buffer) / 2;
        dma.TCD->DLASTSGA = 0;
        dma.TCD->BITER_ELINKNO = sizeof(dac_dma_buffer) / 2;
        dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
        dma.triggerAtHardwareEvent(DMAMUX_SOURCE_I2S0_TX);
        dma.enable();

        I2S0_TCSR = I2S_TCSR_SR;
        I2S0_TCSR = I2S_TCSR_TE | I2S_TCSR_BCE | I2S_TCSR_FRDE;
    #elif defined(__IMXRT1062__)
        dma.TCD->SADDR = dac_dma_buffer;
        dma.TCD->SOFF = 2;
        dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
        dma.TCD->NBYTES_MLNO = 2;
        dma.TCD->SLAST = -sizeof(dac_dma_buffer);
        dma.TCD->DOFF = 0;
        dma.TCD->CITER_ELINKNO = sizeof(dac_dma_buffer) / 2;
        dma.TCD->DLASTSGA = 0;
        dma.TCD->BITER_ELINKNO = sizeof(dac_dma_buffer) / 2;
        dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
        dma.TCD->DADDR = (void *)((uint32_t)&I2S1_TDR0 + 2);
        dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_TX);
        dma.enable();

        I2S1_RCSR |= I2S_RCSR_RE | I2S_RCSR_BCE;
        I2S1_TCSR = I2S_TCSR_TE | I2S_TCSR_BCE | I2S_TCSR_FRDE;
    #endif

  #else   // USE_I2S

    SIM_SCGC2 |= SIM_SCGC2_DAC0;
    DAC0_C0 = DAC_C0_DACEN;
#ifdef LOUD
    DAC0_C0 |= DAC_C0_DACRFS;  // 3.3V, much louder
#endif
    // This would cause a click, but the amp is not on yet...
    *(int16_t *)&(DAC0_DAT0L) = 2048;

    // set the programmable delay block to trigger DMA requests
    SIM_SCGC6 |= SIM_SCGC6_PDB;
    PDB0_IDLY = 1;
    PDB0_MOD = F_BUS / AUDIO_RATE;
    PDB0_SC = PDB_CONFIG | PDB_SC_LDOK;
    PDB0_SC = PDB_CONFIG | PDB_SC_SWTRIG;
    PDB0_CH0C1 = 0x0101;

    dma.TCD->SADDR = dac_dma_buffer;
    dma.TCD->SOFF = 2;
    dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
    dma.TCD->NBYTES_MLNO = 2;
    dma.TCD->SLAST = -sizeof(dac_dma_buffer);
    dma.TCD->DADDR = &DAC0_DAT0L;
    dma.TCD->DOFF = 0;
    dma.TCD->CITER_ELINKNO = NELEM(dac_dma_buffer);
    dma.TCD->DLASTSGA = 0;
    dma.TCD->BITER_ELINKNO = NELEM(dac_dma_buffer);
    dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
    dma.triggerAtHardwareEvent(DMAMUX_SOURCE_PDB);
    dma.enable();
#endif
    dma.attachInterrupt(isr);

#else  // teensyduino
    // check return value?
	
  #if defined(USE_DAC) && defined(ULTRA_PROFFIE)
    bool result;
    unsigned int priority = STM32L4_SAI_IRQ_PRIORITY;
    // uint32_t timPeriphClock;
    // uint32_t dmaOption = 0;
    // 1. Create instance of timer6 , with desired priority
    result = stm32l4_timer_create(&stm32l4_dac1Timer, TIMER_INSTANCE_TIM6, priority, 0);  // prio was 2 
    if(result && stm32l4_dac1Timer.state == TIMER_STATE_INIT) // if created OK proceed configureing it
    {
        timPeriphClock = stm32l4_timer_clock(&stm32l4_dac1Timer);  // get clock peripheral
        result = stm32l4_timer_enable(&stm32l4_dac1Timer, 0, 1814, 0, NULL, NULL, TIMER_OPTION_COUNT_UP);  //  | TIMER_EVENT_PERIOD   // 1300 // 1814
        stm32l4_dac1Timer.TIM->CR2 = 0X20; // The update event is selected as a trigger output (TRGO). 
        // stm32l4_timer_start(&stm32l4_dac1Timer, 0); // start the timer 
    } // end creation of TIMER6 for triggering DAC conversion 

        // 0 AMP enable GPIO // toDo Move from here 
    stm32l4_gpio_pin_configure(GPIO_PIN_PB4, GPIO_MODE_OUTPUT | GPIO_OTYPE_PUSHPULL | GPIO_OSPEED_LOW | GPIO_PUPD_PULLDOWN);
    //stm32l4_gpio_pin_write(GPIO_PIN_PB4, 0); // RESET FOr NOW 
    // 1. GPIO INit - PA4 , prepare pin for DAC1 USAGE 
    stm32l4_gpio_pin_configure(GPIO_PIN_PA4, GPIO_MODE_ANALOG | GPIO_OTYPE_PUSHPULL | GPIO_OSPEED_LOW | GPIO_PUPD_NONE); 
    // 2. DMA1 Channel3  preparing
    stm32l4_dma_create(&dma, DMA_CHANNEL_DMA1_CH3_DAC1, priority);
    stm32l4_dma_enable(&dma, isr, NULL);
    // stm32l4_dac1DMA.DMA->CCR = DMA_CCR_PL_1 | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_DIR | DMA_CCR_MINC | DMA_CCR_CIRC;


    // 3. DAC1 Initialization
    stm32l4_dac_create(&stm32l4_dac1, DAC_INSTANCE_DAC, priority, 0);
    stm32l4_dac_enable(&stm32l4_dac1, 0, NULL, NULL, 0);
    stm32l4_dac_channel(&stm32l4_dac1, DAC_CHANNEL_1, 0, DAC_CONTROL_EXTERNAL);     // make calibration   DAC_CONTROL_INTERNAL
    stm32l4_dac1.DACx->CR |= DAC_CR_TEN1;     // and DAC channel1 DMA Underrun Interrupt enabled
    stm32l4_dac1.DACx->CR &= ~DAC_CR_EN1;     // Disable for now , further config folllow 

    stm32l4_dac1.DACx->CR |= DAC_CR_DMAEN1 | DAC_CR_DMAUDRIE1; // enable underrrun IT and DMA ENABLE

  #else // end USE_DAC
    #if PROFFIEBOARD_VERSION == 3
        stm32l4_dma_create(&dma, DMA_CHANNEL_DMA2_CH1_SAI1_A, STM32L4_SAI_IRQ_PRIORITY);
    #else
        stm32l4_dma_create(&dma, DMA_CHANNEL_DMA2_CH6_SAI1_A, STM32L4_SAI_IRQ_PRIORITY);
    #endif
    #if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
        stm32l4_dma_create(&dma2, DMA_CHANNEL_DMA2_CH2_SAI1_B, STM32L4_SAI_IRQ_PRIORITY);
        // stm32l4_dma_create(&dma2, DMA_CHANNEL_DMA2_CH7_SAI1_B, STM32L4_SAI_IRQ_PRIORITY);
    #endif
  #endif // end else  USE_DAC

#endif // end else TEENSYDUINO

  }

  void begin() {
    if (on_) return;
    on_ = true;
    Setup();

    memset(dac_dma_buffer, 0, sizeof(dac_dma_buffer));
#if defined(ENABLE_SPDIF_OUT) || defined(ENABLE_I2S_OUT)
    memset(dac_dma_buffer2, 0, sizeof(dac_dma_buffer2));
#endif
#ifdef FILTER_CUTOFF_FREQUENCY
    filter_.clear();
#endif

  #if defined(USE_DAC) && defined(ULTRA_PROFFIE)

  uint32_t dmaOption = 0;
  dmaOption = DMA_OPTION_MEMORY_TO_PERIPHERAL | DMA_OPTION_PERIPHERAL_DATA_SIZE_16 | DMA_OPTION_PRIORITY_HIGH | DMA_OPTION_MEMORY_DATA_SIZE_16 \
                  | DMA_OPTION_CIRCULAR | DMA_OPTION_MEMORY_DATA_INCREMENT;
  dmaOption |= DMA_OPTION_EVENT_TRANSFER_HALF | DMA_OPTION_EVENT_TRANSFER_DONE | DMA_OPTION_EVENT_TRANSFER_ERROR;  // | DMA_OPTION_EVENT_TRANSFER_HALF

  stm32l4_dma_start(&dma, ((uint32_t)(stm32l4_dac1.DACx))+12, (uint32_t)(dac_dma_buffer), AUDIO_BUFFER_SIZE * 2, dmaOption);  // was +8
  // DMA1->ISR |= DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3;
  // stm32l4_dma_poll(&stm32l4_dac1DMA);
  stm32l4_timer_start(&stm32l4_dac1Timer, 0); // start the timer 
  stm32l4_dac1.DACx->CR |= DAC_CR_EN1; // enable underrrun IT and DMA ENABLE

#else // end USE_DAC
  #ifndef TEENSYDUINO
      stm32l4_system_periph_enable(SYSTEM_PERIPH_SAI1);
      stm32l4_dma_enable(&dma, &isr, 0);
      SAI_Block_TypeDef *SAIx = SAI1_Block_A;
      SAIx->CR1 = SAI_xCR1_DS_2 | SAI_xCR1_MONO | SAI_xCR1_CKSTR
  #ifdef ENABLE_SPDIF_OUT
      | (1 << SAI_xCR1_MCKDIV_Pos)
  #endif
      ;
      SAIx->FRCR = (31 << SAI_xFRCR_FRL_Pos) | (15 << SAI_xFRCR_FSALL_Pos) | SAI_xFRCR_FSDEF | SAI_xFRCR_FSOFF;
      SAIx->SLOTR = SAI_xSLOTR_NBSLOT_0 | (0x0003 << SAI_xSLOTR_SLOTEN_Pos) | SAI_xSLOTR_SLOTSZ_0;

  #ifdef ENABLE_I2S_OUT
      stm32l4_dma_enable(&dma2, &isr2, 0);
      SAI_Block_TypeDef *SAI2 = SAI1_Block_B;
      SAI2->CR1 = SAI_xCR1_DS_2 | SAI_xCR1_MONO | SAI_xCR1_CKSTR;
      SAI2->FRCR = (31 << SAI_xFRCR_FRL_Pos) | (15 << SAI_xFRCR_FSALL_Pos) | SAI_xFRCR_FSDEF | SAI_xFRCR_FSOFF;
      SAI2->SLOTR = SAI_xSLOTR_NBSLOT_0 | (0x0003 << SAI_xSLOTR_SLOTEN_Pos) | SAI_xSLOTR_SLOTSZ_0;
  #endif

  #ifdef ENABLE_SPDIF_OUT
      stm32l4_dma_enable(&dma2, &isr2, 0);
      SAI_Block_TypeDef *SAI2 = SAI1_Block_B;
      SAI2->CR1 = SAI_xCR1_PRTCFG_0;
  #endif

      stm32l4_system_saiclk_configure(SYSTEM_SAICLK_11289600);
  #ifdef ENABLE_SPDIF_OUT
      my_stm32l4_system_saiclk_configure_22579200();
  #endif
      extern const stm32l4_sai_pins_t g_SAIPins;
      stm32l4_gpio_pin_configure(g_SAIPins.sck, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
      stm32l4_gpio_pin_configure(g_SAIPins.fs, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
      stm32l4_gpio_pin_configure(g_SAIPins.sd, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
      stm32l4_dma_start(&dma, (uint32_t)&SAIx->DR, (uint32_t)dac_dma_buffer, AUDIO_BUFFER_SIZE * 2,
                        DMA_OPTION_EVENT_TRANSFER_DONE |
                        DMA_OPTION_EVENT_TRANSFER_HALF |
                        DMA_OPTION_MEMORY_TO_PERIPHERAL |
                        DMA_OPTION_PERIPHERAL_DATA_SIZE_32 |
                        DMA_OPTION_MEMORY_DATA_SIZE_16 |
                        DMA_OPTION_MEMORY_DATA_INCREMENT |
                        DMA_OPTION_PRIORITY_HIGH |
                        DMA_OPTION_CIRCULAR);
      SAIx->CR1 |= SAI_xCR1_DMAEN;

  #define SAIB_SCK g_SAIPins.sck
  #define SAIB_FS g_SAIPins.fs
  #define SAIB_SD g_SAIPins.sd
      
  #if PROFFIEBOARD_VERSION < 3
  #undef SAIB_FS
  #define SAIB_FS GPIO_PIN_PA4_SAI1_FS_B
  #endif    

  #ifdef ENABLE_I2S_OUT
      // Neopixel data 3 pin is SCK
      stm32l4_gpio_pin_configure(SAIB_SCK, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));

      // Neopixel data 4 is FS, it is also possible to use GPIO_PIN_PB6_SAI1_FS_B, which is the power button pin.
      stm32l4_gpio_pin_configure(SAIB_FS, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));

      // aux/Button2 button pin is DATA
      stm32l4_gpio_pin_configure(SAIB_SD, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
      stm32l4_dma_start(&dma2, (uint32_t)&SAI2->DR, (uint32_t)dac_dma_buffer2, AUDIO_BUFFER_SIZE * 2,
                        DMA_OPTION_EVENT_TRANSFER_DONE |
                        DMA_OPTION_EVENT_TRANSFER_HALF |
                        DMA_OPTION_MEMORY_TO_PERIPHERAL |
                        DMA_OPTION_PERIPHERAL_DATA_SIZE_32 |
                        DMA_OPTION_MEMORY_DATA_SIZE_16 |
                        DMA_OPTION_MEMORY_DATA_INCREMENT |
                        DMA_OPTION_PRIORITY_HIGH |
                        DMA_OPTION_CIRCULAR);
      SAI2->CR1 |= SAI_xCR1_DMAEN;
  #endif

  #ifdef ENABLE_SPDIF_OUT
      // aux button pin becomes S/PDIF out
      stm32l4_gpio_pin_configure(SAIB_SD, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
      stm32l4_dma_start(&dma2, (uint32_t)&SAI2->DR, (uint32_t)dac_dma_buffer2, AUDIO_BUFFER_SIZE * 2 * 2,
                        DMA_OPTION_EVENT_TRANSFER_DONE |
                        DMA_OPTION_EVENT_TRANSFER_HALF |
                        DMA_OPTION_MEMORY_TO_PERIPHERAL |
                        DMA_OPTION_PERIPHERAL_DATA_SIZE_32 |
                        DMA_OPTION_MEMORY_DATA_SIZE_32 |
                        DMA_OPTION_MEMORY_DATA_INCREMENT |
                        DMA_OPTION_PRIORITY_HIGH |
                        DMA_OPTION_CIRCULAR);
      SAI2->CR1 |= SAI_xCR1_DMAEN;
  #endif

      noInterrupts();
      if (!(SAIx->CR1 & SAI_xCR1_SAIEN))
      {
        SAIx->CR2 = SAI_xCR2_FTH_1;
        SAIx->CR1 |= SAI_xCR1_SAIEN;
      }
  #if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
      if (!(SAI2->CR1 & SAI_xCR1_SAIEN))
      {
        SAI2->CR2 = SAI_xCR2_FTH_1;
        SAI2->CR1 |= SAI_xCR1_SAIEN;
      }
  #endif // I2S || SPDIF
      interrupts();
  #endif
#endif // end else USE_DAC


  }

  void end() {
    if (!on_) return;
    on_ = false;
#if defined(USE_DAC) && defined(ULTRA_PROFFIE)
    stm32l4_dac1.DACx->CR &= ~DAC_CR_EN1;     // Disable DAC output
    //stm32l4_gpio_pin_write(GPIO_PIN_PB4, 0);  // Disable amp TODO , remove from here maybe 
    stm32l4_timer_stop(&stm32l4_dac1Timer);   // start the timer 
    stm32l4_dma_stop(&dma);       // stop DMA
#else 
  #ifndef TEENSYDUINO
      SAI_Block_TypeDef *SAIx = SAI1_Block_A;

      SAIx->CR1 &=~ SAI_xCR1_SAIEN;
      // Poll until actually off
      while (SAIx->CR1 & SAI_xCR1_SAIEN);

  #if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
      SAI_Block_TypeDef *SAI2 = SAI1_Block_B;

      SAI2->CR1 &=~ SAI_xCR1_SAIEN;
      // Poll until actually off
      while (SAI2->CR1 & SAI_xCR1_SAIEN);
  #endif

      stm32l4_system_saiclk_configure(SYSTEM_SAICLK_NONE);

      stm32l4_dma_disable(&dma);
  #if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
      stm32l4_dma_disable(&dma2);
  #endif
      stm32l4_system_periph_disable(SYSTEM_PERIPH_SAI1);
      extern const stm32l4_sai_pins_t g_SAIPins;
      stm32l4_gpio_pin_configure(g_SAIPins.sck, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
      stm32l4_gpio_pin_configure(g_SAIPins.fs, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
      stm32l4_gpio_pin_configure(g_SAIPins.sd, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));

  #ifdef ENABLE_I2S_OUT
      stm32l4_gpio_pin_configure(GPIO_PIN_PB3_SAI1_SCK_B, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
      stm32l4_gpio_pin_configure(GPIO_PIN_PA4_SAI1_FS_B, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
      stm32l4_gpio_pin_configure(GPIO_PIN_PB5_SAI1_SD_B, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  #endif

  #ifdef ENABLE_SPDIF_OUT
      stm32l4_gpio_pin_configure(GPIO_PIN_PB5_SAI1_SD_B,  (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  #endif

  #endif
#endif 
  }

  bool Parse(const char* cmd, const char* arg) override {
#ifndef DISABLE_DIAGNOSTIC_COMMANDS
    if (!strcmp(cmd, "dacbuf")) {
#ifndef TEENSYDUINO
      SAI_Block_TypeDef *SAIx = SAI1_Block_A;
      STDOUT.print("STATUS: ");
      STDOUT.print(SAIx->SR, HEX);
      STDOUT.print(" CR1: ");
      STDOUT.print(SAIx->CR1, HEX);
      STDOUT.print(" CR2: ");
      STDOUT.println(SAIx->CR2, HEX);
#endif
      STDOUT.print("Current position: ");
      STDOUT.println(((uint16_t*)current_position()) - dac_dma_buffer);
      for (size_t i = 0; i < NELEM(dac_dma_buffer); i++) {
#if defined(TEENSYDUINO) && !defined(USE_I2S)
        STDOUT.print(dac_dma_buffer[i] - 2048);
#else
        STDOUT.print(dac_dma_buffer[i]);
#endif
        if ((i & 0xf) == 0xf)
          STDOUT.println("");
        else
          STDOUT.print(" ");
      }
      STDOUT.println("");
      return true;
    }
#endif
    return false;
  }

  bool isSilent() {
     for (size_t i = 0; i < NELEM(dac_dma_buffer); i++)
       if (dac_dma_buffer[i] != dac_dma_buffer[0])
         return false;
     return true;
  }

  void Help() override {
    #if defined(COMMANDS_HELP) || !defined(OSx)
    STDOUT.println(" dacbuf - print the current contents of the dac buffer");
    #endif
  }

  // TODO: Replace with enable/disable
  void SetStream(class ProffieOSAudioStream* stream) {
    stream_ = stream;
  }

private:
  static uint32_t current_position() {
#ifdef TEENSYDUINO
    return (uint32_t)(dma.TCD->SADDR);
#else
    return (uint32_t)(dac_dma_buffer + stm32l4_dma_count(&dma));
#endif
  }
  // Interrupt handler.
  // Fills the dma buffer with new sample data.
#ifdef TEENSYDUINO
  static void isr(void)
#else
  static void isr(void* arg, unsigned long int event)
#endif
  {
    ScopedCycleCounter cc(audio_dma_interrupt_cycles);
    int16_t *dest;
    uint32_t saddr = current_position();
#ifdef ENABLE_SPDIF_OUT
    uint32_t *secondary;
#endif
#ifdef ENABLE_I2S_OUT
    uint16_t *secondary;
#endif

#ifdef TEENSYDUINO
    dma.clearInterrupt();
#endif
    if (saddr < (uint32_t)dac_dma_buffer + sizeof(dac_dma_buffer) / 2) {
      // DMA is transmitting the first half of the buffer
      // so we must fill the second half
      dest = (int16_t *)&dac_dma_buffer[AUDIO_BUFFER_SIZE*CHANNELS];
#if defined(ENABLE_SPDIF_OUT) || defined(ENABLE_I2S_OUT)
      secondary = dac_dma_buffer2 + AUDIO_BUFFER_SIZE * 2;
#endif
    } else {
      // DMA is transmitting the second half of the buffer
      // so we must fill the first half
      dest = (int16_t *)dac_dma_buffer;
#if defined(ENABLE_SPDIF_OUT) || defined(ENABLE_I2S_OUT)
      secondary = dac_dma_buffer2;
#endif
    }
#ifdef __IMXRT1062__
    int16_t *clear_cache = dest;
#endif

#ifndef LINE_OUT_VOLUME
// LINE_OUT_VOLUME can be defined as dynamic_mixer.get_volume() to follow normal volume.
#define LINE_OUT_VOLUME 2000
#endif      
    
#if defined(ENABLE_SPDIF_OUT) || defined(ENABLE_I2S_OUT) || defined(FILTER_CUTOFF_FREQUENCY)
#define DAC_GET_FLOATS
#endif

#ifdef DAC_GET_FLOATS
    float data[AUDIO_BUFFER_SIZE];
#else    
    int16_t data[AUDIO_BUFFER_SIZE];
#endif    
    int n = 0;
    if (stream_) {
      n = dynamic_mixer.read(data, AUDIO_BUFFER_SIZE);
    }
    while (n < AUDIO_BUFFER_SIZE) data[n++] = 0;

#if defined(ENABLE_SPDIF_OUT) || defined(ENABLE_I2S_OUT)
    for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
#ifdef ENABLE_I2S_OUT
      *(secondary++) = clamptoi16(data[i] * (LINE_OUT_VOLUME));
#endif
#ifdef ENABLE_SPDIF_OUT
      int32_t sample24 = clamptoi24(data[i] * (LINE_OUT_VOLUME * 256));
      *(secondary++) = sample24 & 0xFFFFFF;
      *(secondary++) = sample24 & 0xFFFFFF;
#endif
    }
#endif  // GET_FLOATS

#ifdef FILTER_CUTOFF_FREQUENCY
    // Run the filter
    static_assert(AUDIO_BUFFER_SIZE % 4 == 0);
    for (int i = 0; i < AUDIO_BUFFER_SIZE; i+=4) {
      filter_.Run4(data + i);
    }
#endif    
    for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
#ifdef DAC_GET_FLOATS
      int16_t sample = clamptoi16(data[i] * dynamic_mixer.get_volume());
#else   // GET_FLOATS
      int16_t sample = data[i];
#endif  // GET_FLOATS

#ifdef USE_I2S
        *(dest++) = sample;
  #if CHANNELS == 2
        // Duplicate sample to left and right channel.
        *(dest++) = sample;
  #endif
#elif defined(USE_DAC)

    *(dest++) = (((uint16_t)sample) + 32768);   // was  32767

#else // I2S
      // For Teensy DAC
      *(dest++) = (((uint16_t)sample) + 32768) >> 4;
#endif
    }
    
#ifdef __IMXRT1062__
    arm_dcache_flush_delete(clear_cache, sizeof(dac_dma_buffer)/2);
#endif
  }

  static void isr2(void* arg, unsigned long int event) {}

  bool on_ = false;
  bool needs_setup_ = true;
  DMAMEM static uint16_t dac_dma_buffer[AUDIO_BUFFER_SIZE*2*CHANNELS];
#ifdef ENABLE_SPDIF_OUT
  DMAMEM static uint32_t dac_dma_buffer2[AUDIO_BUFFER_SIZE*2*2];
#endif
#ifdef ENABLE_I2S_OUT
  DMAMEM static uint16_t dac_dma_buffer2[AUDIO_BUFFER_SIZE*2*CHANNELS];
#endif
  static ProffieOSAudioStream * volatile stream_;
  static DMAChannel dma;
#if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
  static DMAChannel dma2;
#endif
#ifdef FILTER_CUTOFF_FREQUENCY
  static Filter::Biquad<
    Filter::Bilinear<
    Filter::BLT<
      Filter::ConvertToHighPass<
	Filter::ButterWorthProtoType<FILTER_ORDER>, FILTER_CUTOFF_FREQUENCY, AUDIO_RATE>>>> filter_;
#endif  
};

#ifdef TEENSYDUINO
DMAChannel LS_DAC::dma(false);
#else
DMAChannel LS_DAC::dma;
#if defined(ENABLE_I2S_OUT) || defined(ENABLE_SPDIF_OUT)
DMAChannel LS_DAC::dma2;
#endif

#endif
ProffieOSAudioStream * volatile LS_DAC::stream_ = nullptr;
DMAMEM __attribute__((aligned(32))) uint16_t LS_DAC::dac_dma_buffer[AUDIO_BUFFER_SIZE*2*CHANNELS];
#ifdef ENABLE_SPDIF_OUT
DMAMEM __attribute__((aligned(32))) uint32_t LS_DAC::dac_dma_buffer2[AUDIO_BUFFER_SIZE*2*2];
#endif
#ifdef ENABLE_I2S_OUT
DMAMEM __attribute__((aligned(32))) uint16_t LS_DAC::dac_dma_buffer2[AUDIO_BUFFER_SIZE*2*CHANNELS];
#endif
#ifdef FILTER_CUTOFF_FREQUENCY
Filter::Biquad<
  Filter::Bilinear<
  Filter::BLT<
    Filter::ConvertToHighPass<
      Filter::ButterWorthProtoType<FILTER_ORDER>, FILTER_CUTOFF_FREQUENCY, AUDIO_RATE>>>> LS_DAC::filter_;
#endif  

LS_DAC dac;

#endif
