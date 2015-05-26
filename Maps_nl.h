/* Maps for Dutch language */
/* TiM board layout: 
TODO
*/
#ifndef MAPS_H
#define MAPS_H

#include <avr/pgmspace.h>

// struct WordMap 
// {
// //	uint8_t id;
	// uint8_t row;
	// uint16_t rowPos;
// }; 
// struct HourMap 
// {
// //	uint8_t id;
	// uint8_t row;
	// uint16_t rowPos;
// }; 
// struct MinuteMap 
// {
// //	uint8_t id;
	// uint8_t row;
	// uint16_t rowPos;
// }; 
struct Maps
{
	ClockMap words[10];
	ClockMap hours[12];
	ClockMap minutes[5];
};
Maps const clockMaps PROGMEM = {
	// words
	{ 
		{0,	0xe000}, // w0  1110000000000000 het
		{0,	0x0c00}, // w1  0000110000000000 is
		{0,	0x00f8}, // w2  0000000011111000 bijna
		{2,	0xf000}, // w3  1111000000000000 voor
		{2, 0x0f00}, // w4  0000111100000000 over
		{6,	0x0018}, // w5  0000000000011000 vm (am)
		{6,	0x0006}, // w6  0000000000000110 nm (pm)
		{7, 0x7f00}, // w7  0111111100000000 geweest
		{7,	0x0070}, // w8  0000000001110000 tik
		{7,	0x000e}  // w9  0000000000001110 tak
	},
	// hours
	{ 
		{6, 0xfc00}, // h0  1111110000000000 twaalf
		{3, 0xe000}, // h1  1110000000000000 een
		{3, 0x1e00}, // h2  0001111000000000 twee
		{3, 0x01e0}, // h3  0000000111100000 drie
		{3, 0x001e}, // h4  0000000000011110 vier
		{4, 0xf000}, // h5  1111000000000000 vijf
		{4, 0x0e00}, // h6  0000111000000000 zes
		{4, 0x01f0}, // h7  0000000111110000 zeven
		{4, 0x000f}, // h8  0000000000001111 acht
		{5, 0xf800}, // h9  1111100000000000 negen
		{5, 0x03c0}, // h10 0000001111000000 tien
		{5, 0x001c}  // h11 0000000000011100 elf
	},
	// minutes
	{ 
		{6, 0x01c0}, // m0  0000000111000000 uur   58->00->02
		{1, 0xf000}, // m1  1111000000000000 vijf  03->07, 23->27, 33->37, 53->57
		{1, 0x0f00}, // m2  0000111100000000 tien  08->12, 18->22, 38->42, 48->52
		{1, 0x00f8}, // m3  0000000011111000 kwart 13->17, 43->47
		{2, 0x0078}  // m4  0000000001111000 half  18->42
	}
};

ClockTime const clockTimes[21] PROGMEM = {
	{ 0,  2, 'm', 0}, // uur
	{ 3,  7, 'm', 1}, // vijf
	{23, 27, 'm', 1}, // vijf
	{33, 37, 'm', 1}, // vijf
	{53, 57, 'm', 1}, // vijf
	{ 8, 12, 'm', 2}, // tien
	{18, 22, 'm', 2}, // tien
	{38, 42, 'm', 2}, // tien
	{48, 52, 'm', 2}, // tien
	{13, 17, 'm', 3}, // kwart
	{43, 47, 'm', 3}, // kwart
	{18, 42, 'm', 4}, // half
	{58, 59, 'm', 0}, // uur
	{ 3, 17, 'w', 4}, // over
	{33, 37, 'w', 4}, // over
	{18, 27, 'w', 3}, // voor
	{38, 57, 'w', 3}, // voor
	{ 1,  2, 'w', 7}, // geweest
	{31, 32, 'w', 7}, // geweest
	{58, 59, 'w', 2}, // bijna
	{28, 29, 'w', 2}  // bijna
};

// max combinations of words than be made from clockTimes entries, e.g. 'vijf voor half' -> 3
uint8_t const maxNumberTimes PROGMEM = 4; // 3 is the real max now, but later on maybe we want to have 'bijna vijf voor half'

#endif