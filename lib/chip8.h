#pragma once

#include <iostream>



class chip8 {
private:
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char variablesRegister[16];
	unsigned short indexRegister;
	unsigned short programCounter;
	unsigned char graphicInterface[64 * 32];
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
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

	chip8();
	void initialize();
	void processCommand();
	bool load(const char *filePath);

	void copyGraphicBuffer(uint32_t*);

	int getKeyPad(int);
	void setKeyPad(int, int);

	bool getDrawFlag();
	void setDrawFlag(bool);

};