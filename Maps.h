#ifndef MAPS_H
#define MAPS_H

#include <avr/pgmspace.h>

struct mapWords
{
	name: char[];
	col: uint8_t;
	rowPos: uint16_t;
}
struct mapHours
{
	name: uint8_t;
	col: uint8_t;
	rowPos: uint16_t;
}
struct mapMinutes
{
	name: uint8_t;
	col: uint8_t;
	rowPos: uint16_t;
}

static const mapWords PROGMEM WordMap[] = {
	{"het",		0,	B1110000000000000},
	{"is",		0,	B0000110000000000},
	{"bijna",	0,	B0000000111110000},
	
}
