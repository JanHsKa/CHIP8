#pragma once

#include <iostream>
#include "Macros.h"



class Chip8 {
private:
	unsigned short opcode;
	unsigned char memory[MEMORYSIZE];
	unsigned char variablesRegister[VARIABLECOUNT];
	unsigned short indexRegister;
	unsigned short programCounter;
	unsigned char graphicInterface[COLUMNS * ROWS];
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[STACKSIZE];
	unsigned short stackPointer;
	unsigned char chip8_fontset[80];
	unsigned char keyPad[16];
	bool drawFlag;


	void decodeOPcode();
	void updateTimers();
	void executeCaseF();
	void executeCase8();
	void drawSprite();
	void executeCase0();
	void clearDisplay();

public:

	Chip8();
	void initialize();
	void processCommand();
	bool load(const char *filePath);
	void debugOutput();

	void copyGraphicBuffer(uint32_t*);

	int getKeyPadAt(int);
	void setKeyPadAt(int, int);

	bool getDrawFlag();
	void setDrawFlag(bool);

};