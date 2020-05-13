/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/



#include <cr_section_macros.h>

#include <cstdint>
#include <memory>     // for placement new


/* --Platform includes. */
#include "chip.h"
#include "board_api.h"
#include "cmsis_os.h"
#include "DigitalInOut.h"

using GPIO = Platform::BSP::DigitalInOut;

// appliaction includes
#include "Application.h"

static char appMem[sizeof(Application)];
static Application* app = nullptr;




int main(void) {

    osStatus xcode = osOK;
    /* --Initialize the underlying hardware. */
	SystemCoreClockUpdate();
	Board_Init();

	GPIO::initialize();

    app = new(appMem) Application;  // RTOS reuses main stack, therefore  placement new!


    // initialize the Kernel
    xcode = osKernelInitialize();



    // Start the RTOS Kernel.
    // The scheduler will be started, never return back
    if (osOK == xcode)
    {
        osKernelStart();   // There should never be a return!
    }
    app->~Application();   // destroy application, should never happen.


	// Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
