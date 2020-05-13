/*
 * Application.cpp
 *
 *  Created on: 23.06.2016
 *      Author: Wuebbelmann
 */

#include "Application.h"

using GPIO = Platform::BSP::DigitalInOut;


Application::Application():
		SRV("Server",1024,osPriorityRealtime,true),
		C1("Client1",1024,osPriorityHigh,250,true,SRV.getTaskHandle(),CLIENT1_EVENT),
		C2("Client2",1024,osPriorityHigh,1000,true,SRV.getTaskHandle(),CLIENT2_EVENT),
		MNG("Manager",1024,osPriorityAboveNormal,2000,true),
		GOL(96,64, "GameOfLife", 1024, osPriorityNormal, true),
		SW2(JOYCPORT,JOYCPIN,GPIO::Direction::INPUT)
{
	//Define ISR

	Platform::BSP::DigitalInOut::InterruptHandler Button_Interrupt = [this](uint32_t i) { osSignalSet(this->SRV.getTaskHandle(),INT_EVENT); };
	SW2.onInterrupt(Button_Interrupt, GPIO::EdgeType::FALLING_EDGE);
}

Application::~Application() {

	SW2.disableInterrupt();
	GOL.deleteTask();
	MNG.deleteTask();
	C2.deleteTask();
	C1.deleteTask();
	SRV.deleteTask();
}




