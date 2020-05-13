#ifndef CONWAY_H
#define CONWAY_H

#include <cstdint>
#include "TaskBase.h"


class GameOfLife: public RTOS::Task {
public:

	GameOfLife(uint8_t w, uint8_t h,
					const char * const name,
					uint16_t usStackDepth,
					osPriority  uxPriority,
					bool immidiateStart = true);
	~GameOfLife();

	/* --Randomize the buffer. */
	void randomize();

	void m_task() { run(); }

	/* --Clear the buffer. */
	void clear();

	/* --Initialize with glider at position. */
	void setupGlider(uint8_t x, uint8_t y);

	/* --Get the current generation. */
	const uint8_t* get() const { return gen0; }

	/* --Calculate the next generation. Returns false if dead. */
	bool evolve();

	void run();

private:

	uint8_t width;
	uint8_t height;

	uint8_t* gen0;
	uint8_t* gen1;

	uint8_t& at(uint8_t* base, uint8_t x, uint8_t y) const;

};




#endif
