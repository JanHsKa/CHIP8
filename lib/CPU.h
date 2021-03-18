#pragma once

#include <iostream>
#include "Macros.h"
#include "Keypad.h"



class CPU {
private:
	uint16_t opcode;
	uint16_t indexRegister;
	uint16_t programCounter;
	uint16_t stack[STACKSIZE];
	uint16_t stackPointer;
	uint8_t memory[MEMORYSIZE];
	uint8_t variablesRegister[VARIABLE_COUNT];
	uint8_t graphicInterface[COLUMNS][ROWS];
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t fontSet[80];
	Keypad* keyboard;
	bool drawFlag;
	int programSize;

	void decodeOPcode();
	void executeCaseF();
	void executeCase8();
	void drawSprite();
	void executeCase0();
	void clearDisplay();

public:
	CPU(Keypad* newKeyboard);
	void initialize();
	void processCommand();
	bool updateTimers();
	bool load(const char *filePath);

	void copyGraphicBuffer(uint32_t*);

	uint16_t getOpcode(int pc); 
	uint16_t getCurrentOpCode();
	int getProgramCounter();
	int getProgramSize();

	bool getDrawFlag();
	void setDrawFlag(bool);

	void debugOutput();
	void printGraficInterface();	
};