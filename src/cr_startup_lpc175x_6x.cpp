//*****************************************************************************
// LPC175x_6x Microcontroller Startup code for use with LPCXpresso IDE
//
// Version : 141204
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2014
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void HardFault_HandlerAsm(void);  // added JW
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER1_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER2_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER3_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI_IRQHandler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PLL0_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void EINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void EINT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void EINT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2S_IRQHandler(void) ALIAS(IntDefaultHandler);
#if defined (__USE_LPCOPEN)
void ETH_IRQHandler(void) ALIAS(IntDefaultHandler);
#else
void ENET_IRQHandler(void) ALIAS(IntDefaultHandler);
#endif
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCPWM_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);
void PLL1_IRQHandler(void) ALIAS(IntDefaultHandler);
void USBActivity_IRQHandler(void) ALIAS(IntDefaultHandler);
void CANActivity_IRQHandler(void) ALIAS(IntDefaultHandler);

void HardFault_HandlerC(unsigned long *hardfault_args);

//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM3
    &_vStackTop, // The initial stack pointer
    ResetISR,                               // The reset handler
    NMI_Handler,                            // The NMI handler
#ifdef USEDEFAULTHDHANLER
    HardFault_Handler,                      // The hard fault handler
#else
	HardFault_HandlerAsm,                   // JW, see http://support.code-red-tech.com/CodeRedWiki/DebugHardFault
#endif
    MemManage_Handler,                      // The MPU fault handler
    BusFault_Handler,                       // The bus fault handler
    UsageFault_Handler,                     // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    DebugMon_Handler,                       // Debug monitor handler
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    SysTick_Handler,                        // The SysTick handler

    // Chip Level - LPC17
    WDT_IRQHandler,                         // 16, 0x40 - WDT
    TIMER0_IRQHandler,                      // 17, 0x44 - TIMER0
    TIMER1_IRQHandler,                      // 18, 0x48 - TIMER1
    TIMER2_IRQHandler,                      // 19, 0x4c - TIMER2
    TIMER3_IRQHandler,                      // 20, 0x50 - TIMER3
    UART0_IRQHandler,                       // 21, 0x54 - UART0
    UART1_IRQHandler,                       // 22, 0x58 - UART1
    UART2_IRQHandler,                       // 23, 0x5c - UART2
    UART3_IRQHandler,                       // 24, 0x60 - UART3
    PWM1_IRQHandler,                        // 25, 0x64 - PWM1
    I2C0_IRQHandler,                        // 26, 0x68 - I2C0
    I2C1_IRQHandler,                        // 27, 0x6c - I2C1
    I2C2_IRQHandler,                        // 28, 0x70 - I2C2
    SPI_IRQHandler,                         // 29, 0x74 - SPI
    SSP0_IRQHandler,                        // 30, 0x78 - SSP0
    SSP1_IRQHandler,                        // 31, 0x7c - SSP1
    PLL0_IRQHandler,                        // 32, 0x80 - PLL0 (Main PLL)
    RTC_IRQHandler,                         // 33, 0x84 - RTC
    EINT0_IRQHandler,                       // 34, 0x88 - EINT0
    EINT1_IRQHandler,                       // 35, 0x8c - EINT1
    EINT2_IRQHandler,                       // 36, 0x90 - EINT2
    EINT3_IRQHandler,                       // 37, 0x94 - EINT3
    ADC_IRQHandler,                         // 38, 0x98 - ADC
    BOD_IRQHandler,                         // 39, 0x9c - BOD
    USB_IRQHandler,                         // 40, 0xA0 - USB
    CAN_IRQHandler,                         // 41, 0xa4 - CAN
    DMA_IRQHandler,                         // 42, 0xa8 - GP DMA
    I2S_IRQHandler,                         // 43, 0xac - I2S
#if defined (__USE_LPCOPEN)
    ETH_IRQHandler,                         // 44, 0xb0 - Ethernet
#else
    ENET_IRQHandler,                        // 44, 0xb0 - Ethernet
#endif
    RIT_IRQHandler,                         // 45, 0xb4 - RITINT
    MCPWM_IRQHandler,                       // 46, 0xb8 - Motor Control PWM
    QEI_IRQHandler,                         // 47, 0xbc - Quadrature Encoder
    PLL1_IRQHandler,                        // 48, 0xc0 - PLL1 (USB PLL)
    USBActivity_IRQHandler,                 // 49, 0xc4 - USB Activity interrupt to wakeup
    CANActivity_IRQHandler,                 // 50, 0xc8 - CAN Activity interrupt to wakeup
};

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{ while(1) {}
}


/**
 * HardFault_HandlerAsm:
 * Alternative Hard Fault handler to help debug the reason for a fault.
 * To use, edit the vector table to reference this function in the HardFault vector
 * This code is suitable for Cortex-M3 and Cortex-M0 cores
 */


// JW, see http://support.code-red-tech.com/CodeRedWiki/DebugHardFault
// Use the 'naked' attribute so that C stacking is not used.
__attribute__((naked))
void HardFault_HandlerAsm(void){
        /*
         * Get the appropriate stack pointer, depending on our mode,
         * and use it as the parameter to the C handler. This function
         * will never return
         */
/* original
        __asm(  ".syntax unified\n"
                        "MOVS   R0, #4  \n"
                        "MOV    R1, LR  \n"
                        "TST    R0, R1  \n"
                        "BEQ    _MSP    \n"
                        "MRS    R0, PSP \n"
                        "B      HardFault_HandlerC      \n"
                "_MSP:  \n"
                        "MRS    R0, MSP \n"
                        "B      HardFault_HandlerC      \n"
                ".syntax divided\n") ;
*/
/* replacement:   */
    __asm(          "MOVS   R0, #4  \n"
                    "MOV    R1, LR  \n"
                    "TST    R0, R1  \n"
                    "BEQ    _MSP    \n"
                    "MRS    R0, PSP \n"
                    "B      HardFault_HandlerC      \n"
            "_MSP:  \n"
                    "MRS    R0, MSP \n"
                    "B      HardFault_HandlerC      \n") ;

}

/**
 * HardFaultHandler_C:
 * This is called from the HardFault_HandlerAsm with a pointer the Fault stack
 * as the parameter. We can then read the values from the stack and place them
 * into local variables for ease of reading.
 * We then read the various Fault Status and Address Registers to help decode
 * cause of the fault.
 * The function ends with a BKPT instruction to force control back into the debugger
 */

#ifdef __GNUC__
/* Ignore warnings about unused variables... they are for debugger purpose */
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
void HardFault_HandlerC(unsigned long *hardfault_args){
        volatile unsigned long stacked_r0 ;
        volatile unsigned long stacked_r1 ;
        volatile unsigned long stacked_r2 ;
        volatile unsigned long stacked_r3 ;
        volatile unsigned long stacked_r12 ;
        volatile unsigned long stacked_lr ;
        volatile unsigned long stacked_pc ;
        volatile unsigned long stacked_psr ;
        volatile unsigned long _CFSR ;
        volatile unsigned long _HFSR ;
        volatile unsigned long _DFSR ;
        volatile unsigned long _AFSR ;
        volatile unsigned long _BFAR ;
        volatile unsigned long _MMAR ;

        stacked_r0 = ((unsigned long)hardfault_args[0]) ;
        stacked_r1 = ((unsigned long)hardfault_args[1]) ;
        stacked_r2 = ((unsigned long)hardfault_args[2]) ;
        stacked_r3 = ((unsigned long)hardfault_args[3]) ;
        stacked_r12 = ((unsigned long)hardfault_args[4]) ;
        stacked_lr = ((unsigned long)hardfault_args[5]) ;
        stacked_pc = ((unsigned long)hardfault_args[6]) ;
        stacked_psr = ((unsigned long)hardfault_args[7]) ;

        // Configurable Fault Status Register
        // Consists of MMSR, BFSR and UFSR
        _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

        // Hard Fault Status Register
        _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

        // Debug Fault Status Register
        _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

        // Auxiliary Fault Status Register
        _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

        // Read the Fault Address Registers. These may not contain valid values.
        // Check BFARVALID/MMARVALID to see if they are valid values
        // MemManage Fault Address Register
        _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
        // Bus Fault Address Register
        _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;

        __asm("BKPT #0\n") ; // Break into the debugger

}
