#ifndef TIMCLOCK_H
#define TIMCLOCK_H

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "TiM.h"

struct ClockMap 
{
//	uint8_t id;
	uint8_t row;
	uint16_t rowPos;
}; 

class TiMClock {
	public:
		TiMClock();
		void setup(TiM tim);
		ClockMap getWord(char* type, uint8_t index);
		void setWordPixels(uint8_t row, uint16_t pos, uint32_t color);
		void setTime(uint8_t hour, uint8_t minute, uint8_t second, uint32_t color);
		//char* timeString(uint8_t hour, uint8_t minute, uint8_t second);
		void show();
	private:
		TiM _tim;
		
};

#endif