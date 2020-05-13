/*
 * ServerTask.cpp
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

//#include <inttypes.h>
#include <cstdlib>
#include "cmsis_os.h"

#include "FreeRTOS.h"

#include "chip.h"
#include <Application.h>    // needed for events

#include "task.h"


#include <pca9532.h>        // port expander, LED
#include "i2cdevice.h"

#include "ServerTask.h"

using I2C=Platform::BSP::I2CDevice;
using LED= Platform::BSP::PCA9532;
static LED LEDS(LED::Interface::I2C2,0x60);

ServerTask::ServerTask(const char * const name,
						uint16_t    stackDepth,
						osPriority  priority,
						bool        immidiateStart):
						RTOS::Task(name, stackDepth, priority,immidiateStart){

	I2C::initialize(I2C::Interface::I2C2, I2C::Mode::POLLING, 100000);
	this->finalizeInit();
}

ServerTask::~ServerTask(){}

void ServerTask::m_task()
{
	bool led1On = true;
	bool led2On = true;
	bool ledint = true;

	//WHILE LOOP ADDED
	while(true)
	{

		osEvent result = osSignalWait(CLIENT1_EVENT | CLIENT2_EVENT | INT_EVENT , osWaitForever);


		if((result.value.signals & CLIENT1_EVENT) == CLIENT1_EVENT)
		{
			if(led1On)
			{
				LEDS.select(LED::Identifier::LED0, LED::Mode::ON);
				led1On = false;
			}

			else
			{
				LEDS.select(LED::Identifier::LED0, LED::Mode::OFF);
				led1On = true;
			}
		}

		//CLIENT2_EVENT
		 if((result.value.signals & CLIENT2_EVENT) == CLIENT2_EVENT )
		{
			if(led2On)
			{
				LEDS.select(LED::Identifier::LED2, LED::Mode::ON);

				led2On = false;
			}

			else
			{
				LEDS.select(LED::Identifier::LED2, LED::Mode::OFF);
				led2On = true;
			}
		}
		//INT_EVENT
		 if((result.value.signals & INT_EVENT) ==  INT_EVENT)
		{
			if(ledint)
			{
				LEDS.select(LED::Identifier::LED15, LED::Mode::ON);
				ledint = false;
			}

			else
			{
				LEDS.select(LED::Identifier::LED15, LED::Mode::OFF);
				ledint = true;
			}

		}

	}
}
