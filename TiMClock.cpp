#include "TiMClock.h"
//#ifdef MAPS
//	#include MAPS
//#else
	#include "Maps_nl.h" 
//#endif

TiMClock::TiMClock(){
}
void TiMClock::setup(TiM tim) {
	_tim = tim;
	
	uint8_t maxWords = pgm_read_byte(&maxNumberTimes);
	_wordMaps.maps = (ClockMap *)malloc(maxWords * sizeof(ClockMap));
	_wordMaps.size = maxWords;
}
void TiMClock::getTimes(uint8_t minute) {
	uint8_t index = 0;
	uint8_t from;
	uint8_t to;
	char type;
	uint8_t pos;
	uint8_t n = sizeof(clockTimes)/sizeof(clockTimes[0]);
	
	_wordMaps.used = 0;
	
	for (uint8_t i = 0; i < n; i++) {
		from = pgm_read_byte(&clockTimes[i].from);
		to = pgm_read_byte(&clockTimes[i].to);
		
		if (minute >= from && minute <= to) {
			type = pgm_read_byte(&clockTimes[i].type);
			pos = pgm_read_byte(&clockTimes[i].pos);

			_wordMaps.maps[index] = getWord(type, pos);
			index++;
			_wordMaps.used = index;
		}
	}
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
//Serial.print(type);
//Serial.print(index);
//Serial.print(" -> ");
//Serial.print(row);
//Serial.print(':');
//Serial.println(pos, HEX);
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
  }  
}
void TiMClock::setTime(uint8_t hour, uint8_t minute, uint8_t second, uint32_t color) {
	ClockMap wordMap;
	
	_tim.setall(Color(0, 0, 0));
	// het is
	wordMap = getWord('w', 0); // het
	setWordPixels(wordMap.row, wordMap.rowPos, color);
	wordMap = getWord('w', 1); // is
	setWordPixels(wordMap.row, wordMap.rowPos, color);
	
	// vijf, tien, kwart, half, uur, over, voor, geweest, bijna 
	getTimes(minute); 
	uint8_t n = _wordMaps.used;
	for (uint8_t i = 0; i < n; i++) {
		wordMap = _wordMaps.maps[i];
		setWordPixels(wordMap.row, wordMap.rowPos, color);
	}
	
	// vm/nm
	if (hour < 12)
	{
		wordMap = getWord('w', 5); // vm
		setWordPixels(wordMap.row, wordMap.rowPos, color);
	}
	else 
	{
		wordMap = getWord('w', 6); // nm
		setWordPixels(wordMap.row, wordMap.rowPos, color);
	}
	
	// uren
	// minute>=18 => uur+1 
	if (minute >= 18)
	{
		hour++;
	}
	if (hour >= 12)
	{
		hour = hour-12;
	}
	if (hour == 12)
	{
		hour = 0;
	}
	wordMap = getWord('h', hour); // twaalf, een, twee, ..., elf
	setWordPixels(wordMap.row, wordMap.rowPos, color);
}
void TiMClock::show() 
{
	_tim.show();
	//Serial.print(F("Free RAM: "));
	//Serial.println(_freeRam());
	//Serial.println();
}
int TiMClock::_freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}