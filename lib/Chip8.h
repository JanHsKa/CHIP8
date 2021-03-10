#pragma once

#include <iostream>
#include "Macros.h"
#include "Keypad.h"



class Chip8 {
private:
	unsigned short opcode;
	unsigned char memory[MEMORYSIZE];
	unsigned char variablesRegister[VARIABLECOUNT];
	uint8_t graphicInterface[COLUMNS][ROWS];
	unsigned short indexRegister;
	unsigned short programCounter;
	unsigned char delayTimer;
	unsigned char soundTimer;
	unsigned short stack[STACKSIZE];
	unsigned short stackPointer;
	unsigned char chip8_fontset[80];
	unsigned char keyPad[16];
	Keypad* keyboard;
	bool drawFlag;


	void decodeOPcode();
	void executeCaseF();
	void executeCase8();
	void drawSprite();
	void executeCase0();
	void clearDisplay();

public:
	Chip8(Keypad* newKeyboard);
	void initialize();
	void processCommand();
	bool updateTimers();
	bool load(const char *filePath);
	void debugOutput();

	void copyGraphicBuffer(uint32_t*);
	void updateKeyPad(uint8_t*);

	bool getDrawFlag();
	void setDrawFlag(bool);

};