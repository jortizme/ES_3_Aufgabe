/*
 * ClientTask.cpp
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

#include "ClientTask.h"


ClientTask::ClientTask(const char * const name,
						uint16_t    stackDepth,
						osPriority  priority,
						uint32_t    period,
						bool        immidiateStart,
						osThreadId Server_Id,
						uint8_t signalFlag):
						RTOS::PeriodicTaskBase(name, stackDepth, priority,period,immidiateStart),
						m_Server_id(Server_Id), m_signalFlag(signalFlag)
{

	this->finalizeInit();
}

ClientTask::~ClientTask(){}

void ClientTask::m_task()
{
	int32_t error = 0x80000000;

	while(true)
	{
		osEvent result = osSignalWait(RTOS::TIMEREVENT, osWaitForever);

		if(result.value.signals & RTOS::TIMEREVENT)
		{

			if(error == osSignalSet(m_Server_id,m_signalFlag))
				printf("Incorrect parameteres osSingalSet\n");
		}

	}

}
