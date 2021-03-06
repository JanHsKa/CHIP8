#pragma once

#include <iostream>
#include "Macros.h"



class Chip8 {
private:
	unsigned short opcode;
	unsigned char memory[MEMORYSIZE];
	unsigned char variablesRegister[VARIABLECOUNT];
	unsigned char graphicInterface[COLUMNS * ROWS];
	unsigned short indexRegister;
	unsigned short programCounter;
	unsigned char delayTimer;
	unsigned char soundTimer;
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
	unsigned int screen_state[ROWS*COLUMNS];

	Chip8();
	void initialize();
	void processCommand();
	bool load(const char *filePath);
	void debugOutput();

	void copyGraphicBuffer(uint32_t*);
	void copyGraphicBuffer();

	int getKeyPadAt(int);
	void setKeyPadAt(int, int);

	bool getDrawFlag();
	void setDrawFlag(bool);

};