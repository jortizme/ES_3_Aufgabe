/*
 * ClientTask.h
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

#ifndef CLIENTTASK_H_
#define CLIENTTASK_H_

#include <cstdlib>
#include "FreeRTOS.h"
#include "task.h"
#include "chip.h"
#include "PeriodicTaskBase.h"


class ClientTask : public RTOS::PeriodicTaskBase{

public:

	ClientTask(const char * const name,
    			uint16_t    stackDepth,
				osPriority  priority,
				uint32_t    period,
				bool        immidiateStart = true,
				osThreadId Server_Id = nullptr, uint8_t signalFlag = 0);

	~ClientTask();
private:

	osThreadId m_Server_id;
	uint8_t m_signalFlag;

/*Task Funktionalität*/
/*Inhrited from RTOS::Task*/

protected:

	void m_task();

};

#endif /* CLIENTTASK_H_ */
