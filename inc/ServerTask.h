/*
 * ServerTask.h
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

#ifndef SERVERTASK_H_
#define SERVERTASK_H_

#include "TaskBase.h"

class ServerTask : public RTOS::Task{


public:

	ServerTask(const char * const name,
    			uint16_t    stackDepth,
				osPriority  priority,
				bool        immidiateStart = true);

	~ServerTask();
/*Task Funktionalität*/
/*Inhrited from RTOS::Task*/
protected:

	void m_task();

};
#endif /* SERVERTASK_H_ */
