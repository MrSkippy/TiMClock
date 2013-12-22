#ifndef MAPS_H
#define MAPS_H

#include <avr/pgmspace.h>

typedef struct WordMap 
{
	char* name;
	uint8_t col;
	uint16_t rowPos;
} mapWords[];
typedef struct HourMap 
{
	uint8_t name;
	uint8_t col;
	uint16_t rowPos;
} mapHours[];
typedef struct MinuteMap 
{
	uint8_t name;
	uint8_t col;
	uint16_t rowPos;
} mapMinutes[];

static const PROGMEM mapWords words_nl = {
	{"het",		0,	0xe000}, // 1110000000000000
	{"is",		0,	0x0c00}, // 0000110000000000
	{"bijna",	0,	0x01f0}  // 0000000111110000
	
};
static const PROGMEM mapHours hours_nl = {
	{1, 3, 0xe000}  // 1110000000000000
};
static const PROGMEM mapMinutes minutes_nl = {
	
};

#endif