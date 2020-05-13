/*
 * Application.h
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

/**
 *  \brief     Application.
 *  \details   starts all tasks.\n
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      23.06.2016
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <ServerTask.h>
#include <ClientTask.h>
#include <ConwayTask.h>
#include <DebugTask.h>

#include <digitalinout.h>

#define CLIENT1_EVENT  (0x01 << 4)
#define CLIENT2_EVENT  (0x01 << 5)
#define INT_EVENT      (0x01 << 6)

#define JOYCPORT  0
#define JOYCPIN  17


// forward declaration

class Application {
public:
    Application();
    ~Application();


private:

    ServerTask SRV;
    ClientTask C1;
    ClientTask C2;
    TaskManager MNG;
    GameOfLife GOL;

    Platform::BSP::DigitalInOut SW2;


};


#endif /* APPLICATION_H_ */
