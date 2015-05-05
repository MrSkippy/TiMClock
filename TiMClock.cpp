#include "TiMClock.h"
//#ifdef MAPS
//	#include MAPS
//#else
	#include "Maps_nl.h" 
//#endif

TiMClock::TiMClock(){
 //char* test = words[0].name;
}
void TiMClock::setup(TiM tim) {
	_tim = tim;
}
ClockMap* TiMClock::getTimes(uint8_t minute) {
	ClockMap *maps;
	uint8_t index = 0;
	uint8_t from;
	uint8_t to;
	char type;
	uint8_t pos;
	uint8_t n = sizeof(clockTimes)/sizeof(clockTimes[0]);
	for (uint8_t i = 0; i < n; i++) {
		from = pgm_read_byte(&clockTimes[i].from);
		to = pgm_read_byte(&clockTimes[i].to);
		if (minute >= from && minute <= to) {
			type = pgm_read_byte(&clockTimes[i].type);
			pos = pgm_read_byte(&clockTimes[i].pos);
			maps[index] = getWord(type, pos);
			index++;
		}
	}
	return maps;
}
ClockMap TiMClock::getWord(char type, uint8_t index) {
	uint8_t row;
	uint16_t pos;
	if (type == 'w') 
	{
		row = pgm_read_byte(&clockMaps.words[index].row);
		pos = pgm_read_word(&clockMaps.words[index].rowPos);
	} 
	else if (type == 'h')
	{
		row = pgm_read_byte(&clockMaps.hours[index].row);
		pos = pgm_read_word(&clockMaps.hours[index].rowPos);
	}
	else if (type == 'm') 
	{
		row = pgm_read_byte(&clockMaps.minutes[index].row);
		pos = pgm_read_word(&clockMaps.minutes[index].rowPos);
	}
	ClockMap map = {row, pos};
	return map;
}
void TiMClock::setWordPixels(uint8_t row, uint16_t pos, uint32_t color) {
  uint16_t mask = 1; 
  uint8_t currPos = 16;
  for (mask = 0000000000000001; mask>0; mask <<= 1) { 
    currPos--;
    if (pos & mask){ 
      _tim.strips[row].setPixelColor(currPos, color);
    }
//    else{ //if bitwise and resolves to false
//      // do nothing?
//    }
//    //currPos++;
  }  
}
void TiMClock::setTime(uint8_t hour, uint8_t minute, uint8_t second, uint32_t color) {
	ClockMap wordMap;
	String sentence[10];
	
	_tim.setall(Color(0, 0, 0));
	// het is
	wordMap = getWord('w', 0); // het
	setWordPixels(wordMap.row, wordMap.rowPos, color);
	sentence[0] = "Het";
	wordMap = getWord('w', 1); // is
	setWordPixels(wordMap.row, wordMap.rowPos, color);
	sentence[1] = "is";

	// uur / vijf / tien / kwart / half
	// 0  0000000111000000 uur   58->00->02
	// 1  1111000000000000 vijf  03->07, 23->27, 33->37, 53->57
	// 2  0000111100000000 tien  08->12, 18->22, 38->42, 48->52
	// 3  0000000011111000 kwart 13->17, 43->47
	// 4  0000000001111000 half  18->42
	if ( // uur 58->00->02
			(minute < 2 || (minute == 2 && second <= 30)) ||
			((minute == 57 && second > 30) || minute > 57)
		)
	{
		wordMap = getWord('m', 0); // uur
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[7] = "uur";
		// bijna 
		if  (minute <= 59 && minute >= 58) 
		{
			wordMap = getWord('w', 2); // bijna
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[2] = "bijna";
		}
		// geweest
		if  (minute > 0 && minute <=  2) 
		{
			wordMap = getWord('w', 7); // geweest
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[9] = "geweest";
		}
	} 
	else if ( // vijf 03->07, 23->27, 33->37, 53->57
			(((minute ==  2 && second > 30) || minute >  2) && (minute <  7 || (minute ==  7 && second <= 30))) ||
			(((minute == 22 && second > 30) || minute > 22) && (minute < 27 || (minute == 27 && second <= 30))) ||
			(((minute == 32 && second > 30) || minute > 32) && (minute < 37 || (minute == 37 && second <= 30))) ||
			(((minute == 52 && second > 30) || minute > 52) && (minute < 57 || (minute == 57 && second <= 30)))
		)
	{
		wordMap = getWord('m', 1); // vijf
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[3] = "vijf";
		// bijna 
		if  ( 
				(minute <  5 && minute >=  2) || 
				(minute < 25 && minute >= 22) ||
				(minute < 35 && minute >= 32) ||
				(minute < 55 && minute >= 52)
			)
		{
			wordMap = getWord('w', 2); // bijna
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[2] = "bijna";
		}
		// geweest
		if  (
				(minute >  5 && minute <=  7) || 
				(minute > 25 && minute <= 27) ||
				(minute > 35 && minute <= 37) ||
				(minute > 55 && minute <= 57)
			)
		{
			wordMap = getWord('w', 7); // geweest
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[9] = "geweest";
		}
	}
	else if ( // tien 08->12, 18->22, 38->42, 48->52
			(((minute ==  7 && second > 30) || minute >  7) && (minute < 12 || (minute == 12 && second <= 30))) ||
			(((minute == 17 && second > 30) || minute > 17) && (minute < 22 || (minute == 22 && second <= 30))) ||
			(((minute == 37 && second > 30) || minute > 37) && (minute < 42 || (minute == 42 && second <= 30))) ||
			(((minute == 47 && second > 30) || minute > 47) && (minute < 52 || (minute == 52 && second <= 30)))
		)
	{
		wordMap = getWord('m', 2); // tien
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[3] = "tien";
		// bijna 
		if  ( 
				(minute < 10 && minute >=  7) || 
				(minute < 20 && minute >= 17) ||
				(minute < 40 && minute >= 37) ||
				(minute < 50 && minute >= 47)
			)
		{
			wordMap = getWord('w', 2); // bijna
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[2] = "bijna";
		}
		// geweest
		if  (
				(minute > 10 && minute <= 12) || 
				(minute > 20 && minute <= 22) ||
				(minute > 40 && minute <= 42) ||
				(minute > 50 && minute <= 52)
			)
		{
			wordMap = getWord('w', 7); // geweest
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[9] = "geweest";
		}
	}
	else if ( // kwart 13->17, 43->47
			(((minute == 12 && second > 30) || minute > 12) && (minute < 17 || (minute == 17 && second <= 30))) ||
			(((minute == 42 && second > 30) || minute > 42) && (minute < 47 || (minute == 47 && second <= 30)))
		)
	{
		wordMap = getWord('m', 3); // kwart
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[3] = "kwart";
		// bijna 
		if  ( 
				(minute < 15 && minute >= 12) || 
				(minute < 45 && minute >= 42) 
			)
		{
			wordMap = getWord('w', 2); // bijna
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[2] = "bijna";
		}
		// geweest
		if  (
				(minute > 15 && minute <= 17) || 
				(minute > 45 && minute <= 47) 
			)
		{
			wordMap = getWord('w', 7); // geweest
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[9] = "geweest";
		}
	}
	if ( // half  18->42
			((minute == 17 && second > 30) || minute > 17) && (minute < 42 || (minute == 42 && second <= 30))
		)
	{
		wordMap = getWord('m', 4); // half
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[5] = "half";
		// bijna 
		if 	(minute < 30 && minute >= 28) 
		{
			wordMap = getWord('w', 2); // bijna
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[2] = "bijna";
		}
		// geweest
		if  (minute > 30 && minute <= 32) 
		{
			wordMap = getWord('w', 7); // geweest
			setWordPixels(wordMap.row, wordMap.rowPos, color);
			sentence[9] = "geweest";
		}
	}
	// over / voor
	if ( // over 3->17, 33->47
			(((minute ==  2 && second > 30) || minute >  2) && (minute < 17 || (minute == 17 && second <= 30))) ||
			(((minute == 32 && second > 30) || minute > 32) && (minute < 47 || (minute == 47 && second <= 30)))
		)
	{
		wordMap = getWord('w', 4); // over
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[4] = "over";
	}
	else if ( // voor 18->27, 43->57
			(((minute == 17 && second > 30) || minute > 17) && (minute < 27 || (minute == 27 && second <= 30))) ||
			(((minute == 42 && second > 30) || minute > 42) && (minute < 57 || (minute == 57 && second <= 30)))
		) 
	{
		wordMap = getWord('w', 3); // voor
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[4] = "voor";
	}
	// vm/nm
	if (hour < 12)
	{
		wordMap = getWord('w', 5); // vm
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[8] = "vm";
	}
	else 
	{
		wordMap = getWord('w', 6); // nm
		setWordPixels(wordMap.row, wordMap.rowPos, color);
		sentence[8] = "nm";
	}
	// uren
	if (hour >= 12)
	{
		hour = hour-12;
	}
	// minute>18 => uur+1 
	if ((minute == 17 && second <= 30) || minute > 17)
	{
		hour++;
	}
	wordMap = getWord('h', hour); // twaalf, een, twee, ..., elf
	setWordPixels(wordMap.row, wordMap.rowPos, color);
	sentence[6] = String(hour);
	int i;
	for (i = 0; i < 10; i++) {
		Serial.print(sentence[i]);
		Serial.print(" ");
	}
	Serial.println();
}
void TiMClock::show() 
{
//	int r, c, on;
//	for (r = 0; r < 8; r++) {
//		for (c = 0; c < 16; c++) {
//			on = _tim.getPixel(r,c);
//			Serial.print(on > 0);
//		}
//		Serial.println();
//	}
	Serial.println();
	_tim.show();
}