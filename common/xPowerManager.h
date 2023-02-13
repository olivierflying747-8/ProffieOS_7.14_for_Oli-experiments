#ifndef XPOWER_MANAHER_H
#define XPOWER_MANAHER_H


    
    #if defined(ULTRA_PROFFIE) && defined(OSx) && defined(X_POWER_MAN)

        // Stop entry type 
        #define PWR_STOPENTRY_WFI               ((uint8_t)0x01)       //Wait For Interruption instruction to enter Stop mode
        #define PWR_STOPENTRY_WFE               ((uint8_t)0x02)       //Wait For Event instruction to enter Stop mode

        // enum describing the resource we are controlling power 
        enum xPowerType { 
            xPower_LightString = 0b00000001,    
            xPower_Audio       = 0b00000010,
            xPower_SDCard      = 0b00000100,
            xPower_CPU         = 0b00001000,
            xPower_Motion      = 0b00010000,
        };
        
        class xPowerManager;
        xPowerManager* xPowerManagers = NULL;

        class xPowerManager
        {   
        private: 
            static uint32_t powerManagerState;  // hold the state 
            static uint8_t wakeUpSource;
            uint32_t lastRequest;
            uint32_t scheduled_timeout;
            uint32_t powerType;
            xPowerManager* next_xPowerManagers;
            const char* nameFunction;

            /*  @brief  : Link list the obj
            *   @param  : void  
            *   @retval : void
            */
            void xLink() 
            {
                scheduled_timeout = 200;  // default timeout in milis
                next_xPowerManagers = xPowerManagers;
                xPowerManagers = this;
            }

            /*  @brief  : UnLink list the obj
            *   @param  : void
            *   @retval : void
            */
            void xUnlink()
            {
                scheduled_timeout = 0;
                for (xPowerManager** i = &xPowerManagers; *i; i = &(*i)->next_xPowerManagers) 
                {
                    if (*i == this) {
                        *i = next_xPowerManagers;
                        return;
                    }
                }
            }

        protected:
            virtual void xKillPower() {}
            virtual void xRestablishPower() {}

        public:
            /*  @brief  : public constructor 
            *   @param  : type
            *   @retval : void 
            */
            explicit xPowerManager(xPowerType type) 
            { 
                xLink(); 
                powerManagerState |= type; 
                powerType = type;
                nameFunction = NULL;
                lastRequest = 0;
            }

            /*  @brief  : public constructor 
            *   @param  : type 
            *             timeout
            *   @retval :
            */
            explicit xPowerManager(xPowerType type, uint32_t timeout)
            {
                xLink();
                scheduled_timeout = timeout;    // default timeout in milis
                powerManagerState |= type;
                powerType = type;
                nameFunction = NULL;
                lastRequest = 0;
            }
            /*  @brief  : public constructor 
            *   @param  : type 
            *             timeout
            *   @retval :
            */
             explicit xPowerManager(xPowerType type, uint32_t timeout, const char* name)
             {
                xLink();
                scheduled_timeout = timeout;    // default timeout in milis
                powerManagerState |= type;
                powerType = type;
                nameFunction = name;
                lastRequest = 0;
             }

            ~xPowerManager() { xUnlink(); }

            /*  @brief  : Print last time request 
            *   @param  : void 
            *   @retval : void 
            */
            static void PrintRequestedTime()
            {
                for (xPowerManager *l = xPowerManagers; l; l = l->next_xPowerManagers) {
                    l->printTime();  
                }
            }
            /*  @brief  : call all restablish power func
            *   @param  : void 
            *   @retval : void 
            */
            static void DoRestablishPower()
            {
                for (xPowerManager *l = xPowerManagers; l; l = l->next_xPowerManagers) {
                    l->xRestablishPower();  
                }
            }

            /*  @brief  : call all kill power func
            *   @param  : void 
            *   @retval : void 
            */
            static void DoKillPower()
            {
                for (xPowerManager *l = xPowerManagers; l; l = l->next_xPowerManagers) {
                    l->xKillPower();  
                }
            }

            /*  @brief  : Timestamp the time we need the power 
            *   @param  : void 
            *   @retval : void 
            */
            void requestPower() 
            { 
                lastRequest = millis();
                powerManagerState |= powerType; 
            }
            /*  @brief  : Set shehulde time to off  
            *   @param  : void 
            *   @retval : void 
            */
            void setSHTime(uint32_t timeout)
            {
                scheduled_timeout = timeout;
            }
            /*  @brief  : clear 
            *   @param  : void 
            *   @retval : void 
            */
            void reset()
            {
                powerManagerState &= ~powerType;
            }

            /*  @brief  : Print time now in milles and last request power time 
            *   @param  : void 
            *   @retval : void 
            */
            void printTime()
            {
                char toPrint[20];
                if(nameFunction != NULL)
                    STDOUT.print(" Subscriber ");  STDOUT.print(nameFunction);
                switch(powerType)
                {
                    case xPower_LightString: strcpy(toPrint , "xPower_LightString\0"); break;
                    case xPower_Audio: strcpy(toPrint , "xPower_Audio\0"); break;
                    case xPower_SDCard: strcpy(toPrint , "xPower_SDCard\0"); break;
                    case xPower_CPU: strcpy(toPrint , "xPower_CPU\0"); break;
                    case xPower_Motion: strcpy(toPrint , "xPower_Motion\0"); break;
                    default: strcpy(toPrint , "default\0"); break;
                }
                STDOUT.print(" Resource ");  STDOUT.print(toPrint);
                STDOUT.print(" Time now is  ");  STDOUT.print(millis());
                STDOUT.print(" last Request is ");  STDOUT.print(lastRequest);
                STDOUT.print(" Programmed timeOUT "); STDOUT.println(scheduled_timeout);
            }

            /*  @brief  : Check timeout 
            *   @param  : void 
            *   @retval : true - timeout reached 
            *             false - timeout reached 
            */
            bool checkTimeout() 
            {
                if(millis() - lastRequest >= scheduled_timeout)
                    return true;

                return false;
            }

            /* @brief  :
            *  @param  :
            *  @retval : 
            */
            static void loop()
            {
                for (xPowerManager *l = xPowerManagers; l; l = l->next_xPowerManagers) {
                    if(!l->checkTimeout())
                        return;             // it's not all on timeout   
                }
                
                STDOUT.flushTx();

                #if defined(BOARDTYPE_LITE)     
                PublishContent(OFFLINE_FILE); 
                #endif

                // everybody is in timeout so we can enter timeout 
                #ifdef DIAGNOSE_POWER
                    STDOUT.println("Everybody is sleeping , go in STOPMOD...");
                    PrintRequestedTime();
                    STDOUT.println("Killing clocks...");
                #endif
                // kill                     
                DoKillPower();
                // entering stop mode 
                STDOUT.println("Entering STOPMODE...");
                STDOUT.flushTx();

                //Serial.end();

                cpu_EnterSTOP0Mode(PWR_STOPENTRY_WFI);   // entering StOP MODE

                DoRestablishPower();

                //Serial.begin(SERIAL_ASCII_BAUD);
    
                #ifdef DIAGNOSE_POWER
                    STDOUT.print("Wake up Source ");
                    if(wakeUpSource == 1)
                        STDOUT.println("BTN ");
                    else if(wakeUpSource == 2)
                    {
                        STDOUT.flushRx();
                        STDOUT.println("Serial ");
                    }
                #endif
                STDOUT.println("Exit STOPMODE , Restablishing power ");
                STDOUT.println("= command disregarded = ");
   
                // leab=ving stop mode 
                // restablish power 
            }

            /* @brief  :
            *  @param  :
            *  @retval : 
            */
            static void cpu_EnterSTOP0Mode(uint8_t STOPEntry) __attribute__((optimize("O0")))
            {

                wakeUpSource = 0;                       // reset wake up source 
                armv7m_systick_disable();               // disable systick 

                // set btn and uart RX pin for for wakeup 
                stm32l4_exti_notify(&stm32l4_exti, g_APinDescription[powerButtonPin].pin,
			      EXTI_CONTROL_FALLING_EDGE, &powerBtn_Wakeup, NULL);    // EXTI_CONTROL_RISING_EDGE
                stm32l4_exti_notify(&stm32l4_exti, GPIO_PIN_PA10,
			      EXTI_CONTROL_RISING_EDGE, &serial_Wakeup, NULL);

                MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_STOP0); // Stop 0 mode with Main Regulator
                SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));   // Set SLEEPDEEP bit of Cortex System Control Register

                if(STOPEntry == PWR_STOPENTRY_WFI)      // Select Stop mode entry 
                    __WFI();    // Request Wait For Interrupt
                else {
                    __SEV();    // Request Wait For Event
                    __WFE();
                    __WFE();
                }
                // WAKE up haved occured
                CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); // Reset SLEEPDEEP bit of Cortex System Control Register
                
                stm32l4_exti_notify(&stm32l4_exti, g_APinDescription[powerButtonPin].pin,
			      EXTI_CONTROL_DISABLE, NULL, NULL);
                stm32l4_exti_notify(&stm32l4_exti, GPIO_PIN_PA10,
			      EXTI_CONTROL_DISABLE, NULL, NULL);

                stm32l4_system_initialize(_SYSTEM_CORE_CLOCK_, _SYSTEM_CORE_CLOCK_/2, _SYSTEM_CORE_CLOCK_/2, 0, STM32L4_CONFIG_HSECLK, STM32L4_CONFIG_SYSOPT);
                armv7m_systick_enable(); 

            }

            /* @brief  :
            *  @param  :
            *  @retval : 
            */
            static void powerBtn_Wakeup(void* context)
            {
                noInterrupts();         // no make sure that we are not bombarded with noise from btn 
                wakeUpSource = 1;
                stm32l4_exti_notify(&stm32l4_exti, g_APinDescription[powerButtonPin].pin,
			      EXTI_CONTROL_DISABLE, NULL, NULL);
                stm32l4_exti_notify(&stm32l4_exti, GPIO_PIN_PA10,
			      EXTI_CONTROL_DISABLE, NULL, NULL);
                interrupts();           // restore int 
            }

            /* @brief  :
            *  @param  :
            *  @retval : 
            */
            static void serial_Wakeup(void* context)
            {
                wakeUpSource = 2;
            }

        };
        
        class xPowerManagerLooper: Looper
        {
            public: 
            xPowerManagerLooper() : Looper(200) {}
            const char* name() {return "PowerManager";}
            void Loop() override {
                xPowerManager::loop();
            }
        };
        uint32_t xPowerManager::powerManagerState = 0;
        uint8_t xPowerManager::wakeUpSource = 0;
        xPowerManagerLooper xpowerManLooperObj;
    #endif

#endif