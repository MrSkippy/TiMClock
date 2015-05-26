#ifndef TIMCLOCK_H
#define TIMCLOCK_H

#include <Arduino.h>
#include "Adafruit_NeoPixel_TiM.h"
#include "TiM.h"

struct ClockMap 
{
	uint8_t row;
	uint16_t rowPos;
};

struct ClockMaps
{
	ClockMap *maps;
	uint8_t size;
	uint8_t used;
};

struct ClockTime
{
	uint8_t from;
	uint8_t to;
	char type;
	uint8_t pos;
};

class TiMClock {
	public:
		TiMClock();
		void setup(TiM tim);
		void getTimes(uint8_t minute);
		ClockMap getWord(char type, uint8_t index);
		void setWordPixels(uint8_t row, uint16_t pos, uint32_t color);
		void setTime(uint8_t hour, uint8_t minute, uint8_t second, uint32_t color);
		void show();
	private:
		TiM _tim;
		ClockMaps _wordMaps;
		int _freeRam();
};

#endif