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
Maps clockMaps PROGMEM = {
	// words
	{ 
		{0,	0xe000}, // 0  1110000000000000 het
		{0,	0x0c00}, // 1  0000110000000000 is
		{0,	0x00f8}, // 2  0000000011111000 bijna
		{2,	0xf000}, // 3  1111000000000000 voor
		{2, 0x0f00}, // 4  0000111100000000 over
		{6,	0x0018}, // 5  0000000000011000 vm (am)
		{6,	0x0006}, // 6  0000000000000110 nm (pm)
		{7, 0x7f00}, // 7  0111111100000000 geweest
		{7,	0x0070}, // 8  0000000001110000 tik
		{7,	0x000e}  // 9  0000000000001110 tak
	},
	// hours
	{ 
		{6, 0xfc00}, // 0  1111110000000000 twaalf
		{3, 0xe000}, // 1  1110000000000000 een
		{3, 0x1e00}, // 2  0001111000000000 twee
		{3, 0x01e0}, // 3  0000000111100000 drie
		{3, 0x001e}, // 4  0000000000011110 vier
		{4, 0xf000}, // 5  1111000000000000 vijf
		{4, 0x0e00}, // 6  0000111000000000 zes
		{4, 0x01f0}, // 7  0000000111110000 zeven
		{4, 0x000f}, // 8  0000000000001111 acht
		{5, 0xf800}, // 9  1111100000000000 negen
		{5, 0x03c0}, // 10 0000001111000000 tien
		{5, 0x001c}  // 11 0000000000011100 elf
	},
	// minutes
	{ 
		{6, 0x01c0}, // 0  0000000111000000 uur   58->00->02
		{1, 0xf000}, // 1  1111000000000000 vijf  03->07, 23->27, 33->37, 53->57
		{1, 0x0f00}, // 2  0000111100000000 tien  08->12, 18->22, 38->42, 48->52
		{1, 0x0f80}, // 3  0000000011111000 kwart 13->17, 43->47
		{2, 0x0078}  // 4  0000000001111000 half  18->42
	}
};

#endif