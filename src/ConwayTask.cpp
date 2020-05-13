#include "ConwayTask.h"

#include <cstdlib>

#include "ssd1305.h"


GameOfLife::GameOfLife(uint8_t w, uint8_t h,
		const char * const name,
		uint16_t usStackDepth,
		osPriority  uxPriority,
		bool immidiateStart ):
		RTOS::Task(name, usStackDepth, uxPriority,immidiateStart),
     width(w),
     height(h),
     gen0(0),
     gen1(0) {
    /* --Allocate two buffers. */
    gen0=new uint8_t[width*height];
    gen1=new uint8_t[width*height];

    this->finalizeInit();
}

GameOfLife::~GameOfLife() {
    /* --Free the memory. */
    delete [] gen0;
    delete [] gen1;
}

void GameOfLife::randomize() {
    /* --Just initialize the current generation. */
    for(uint32_t i=0;i<width*height;i++)
        gen0[i]=(rand()%20 < 3 ? 1 : 0);
}

void GameOfLife::clear() {
    /* --Initialize with zero. */
    for(uint32_t i=0;i<width*height;i++)
        gen0[i]=0;
}

void GameOfLife::setupGlider(uint8_t x, uint8_t y) {
    /* --Set up the glider. */
    if (x<width && y<height) {
        at(gen0,x, y==0 ? height-1 : y-1)=1;
        at(gen0,x==width-1 ? 0 : x+1,y)=1;
        at(gen0,x==0 ? width-1 : x-1, y==height-1 ? 0: y+1)=1;
        at(gen0,x, y==height-1 ? 0: y+1)=1;
        at(gen0,x==width-1 ? 0 : x+1, y==height-1 ? 0: y+1)=1;
    }
}

uint8_t& GameOfLife::at(uint8_t* base, uint8_t x, uint8_t y) const {
    /* --Jump the position. */
    return base[y*width+x];
}

bool GameOfLife::evolve() {
    bool isGameOver=false;

    for(int8_t x=0; x<width; x++)
        for(int8_t y=0; y<height; y++) {
            uint8_t counter=0;
            /* --Check the neighbors. */
            counter+=at(gen0, x==0 ? width-1 : x-1, y==0 ? height-1 : y-1);
            counter+=at(gen0, x,y==0 ? height-1 : y-1);
            counter+=at(gen0, x==width-1 ? 0 : x+1, y==0 ? height-1 : y-1);
            counter+=at(gen0, x==0 ? width-1 : x-1, y);
            counter+=at(gen0, x==width-1 ? 0 : x+1, y);
            counter+=at(gen0, x==0 ? width-1 : x-1, y==height-1 ? 0 : y+1);
            counter+=at(gen0, x, y==height-1 ? 0 : y+1);
            counter+=at(gen0, x==width-1 ? 0 : x+1, y==height-1 ? 0 : y+1);

            /* --Define next state. */
            bool isAlive=(at(gen0,x,y)==1);

            /* --Stay alive. */
            if (isAlive && (counter==2 || counter==3))
                at(gen1,x,y)=1;
            /* --Birth. */
            else if (!isAlive && counter==3)
                at(gen1,x,y)=1;
            /* --Death. */
            else
                at(gen1,x,y)=0;
        }

    /* --Switch the buffers. */
    uint8_t* tmp=gen0;
    gen0=gen1;
    gen1=tmp;

    return isGameOver;
}

void GameOfLife::run()
{
    using SSP=Platform::BSP::SSPDevice;
    SSP::initialize(SSP::Interface::SSP1);

    using GPIO=Platform::BSP::DigitalInOut;
    GPIO::initialize();

    /* --Initialize the display. */
    Platform::BSP::SSD1305 oled(Platform::BSP::SSPDevice::Interface::SSP1, 0,6);

    oled.initialize(width, height, 0x00);
    oled.showDemoPicture();
    oled.flush();

    clear();
    //randomize();
    setupGlider(1,1);
    setupGlider(10,10);
    setupGlider(20,20);

    oled.bitmap(get(),width,height);
    oled.flush();

    while (true) {
        /* --Next generation. */

    	/*uint8_t accumulator = 0;
    	bool pixelState;

    	for(int i = 0 ; i < height-1; i++)
    	{
    		for (int j = 0; j < width-1; j++)
    		{
    			if(gen0[j+accumulator] == 0)
    				pixelState = false;
    			else
    				pixelState= true;

    			oled.pixelLimit(i,gen0[j+accumulator],pixelState);
    		}

    		accumulator = width *(i+1);
    	}
*/
    	evolve();
    	oled.clrscr();
    	oled.bitmap(this->get(), width, height);

    	oled.flush();
    }
}

