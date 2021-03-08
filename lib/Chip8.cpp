﻿
#include <iostream>
#include "Chip8.h"
#include <fstream>
#include "Macros.h"


using namespace std;


Chip8::Chip8() :chip8_fontset{ 
	0xF0, 0x90, 0x90, 0x90, 0xF0, 
	0x20, 0x60, 0x20, 0x20, 0x70, 
	0xF0, 0x10, 0xF0, 0x80, 0xF0, 
	0xF0, 0x10, 0xF0, 0x10, 0xF0, 
	0x90, 0x90, 0xF0, 0x10, 0x10, 
	0xF0, 0x80, 0xF0, 0x10, 0xF0, 
	0xF0, 0x80, 0xF0, 0x90, 0xF0, 
	0xF0, 0x10, 0x20, 0x40, 0x40, 
	0xF0, 0x90, 0xF0, 0x90, 0xF0, 
	0xF0, 0x90, 0xF0, 0x10, 0xF0, 
	0xF0, 0x90, 0xF0, 0x90, 0x90, 
	0xE0, 0x90, 0xE0, 0x90, 0xE0, 
	0xF0, 0x80, 0x80, 0x80, 0xF0, 
	0xE0, 0x90, 0x90, 0x90, 0xE0, 
	0xF0, 0x80, 0xF0, 0x80, 0xF0, 
	0xF0, 0x80, 0xF0, 0x80, 0x80 }
{
	initialize();
}

void Chip8::initialize(){
	programCounter = 0x200;  
	opcode = 0;      	
	indexRegister = 0;      
	stackPointer = 0;      

	clearDisplay();

	for (int i = 0; i < STACKSIZE; i++) {
		stack[i] = 0;
		variablesRegister[i] = 0;
		keyPad[i] = 0;
	}

	for (int i = 0; i < MEMORYSIZE; i++) {
		memory[i] = 0;
	}
	
	// Load fontset
	for (int i = 0; i < 80; ++i)
		memory[i] = chip8_fontset[i];

	delayTimer = 0;
	soundTimer = 0;
}

bool  Chip8::load(const char *filePath) {
	FILE* file = fopen(filePath, "r");

	if (file == NULL) {
		cerr << "Failed to open ROM" << std::endl;
		return false;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* fileBuffer = (char*)malloc(sizeof(char) * fileSize);

	size_t readSize = fread(fileBuffer, sizeof(char), (size_t)fileSize, file);

	if (readSize != fileSize) {
		cerr << "Failed to read ROM" << std::endl;
		return false;
	}

	if (fileSize > (MEMORYSIZE - 512)) {
		cerr << "ROM is to large to read in to memory" << std::endl;
		return false;
	} 
	else {
		for (int i = 0; i < fileSize; i++) {
			memory[i + 512] = (char)fileBuffer[i];
		}
	}

	fclose(file);
	free(fileBuffer);

	return true;
}

void Chip8::processCommand(){

	opcode = memory[programCounter] << 8 | memory[programCounter + 1];
	cout<<"normal    ";
	cout  << std::hex<< opcode<<endl;
	cout<<"converted    ";
	cout  << std::hex<< (opcode & 0xF000) <<endl;
	cout<<"converted  reverse   ";
	cout  << std::hex<< (opcode & 0x00FF) <<endl;
	cout << "program counter  " << programCounter <<endl;
	cout<<endl;

	decodeOPcode();	
}

bool Chip8::updateTimers(){
	if (delayTimer > 0)
		delayTimer--;

	if (soundTimer > 0){
		soundTimer--;
		return true;
	}

	return false;
}


void Chip8::decodeOPcode(){
	cout<<"starting decode"<<endl;
	unsigned short vx;
	unsigned short nn;
	unsigned short vy;
	unsigned short index;
	unsigned short startNumber;
	unsigned rndNumber;

	if (programCounter % 2 != 0) {
		cout<<"Program Counter: "<<programCounter<<endl;
	}

	switch (opcode & 0xF000){
	case 0x0000:
		executeCase0();
		break;

	case 0x1000:
		programCounter = opcode & 0x0FFF;
		break;

	case 0x2000:
		programCounter += 2;
		stack[stackPointer] = programCounter;
		stackPointer++;
		programCounter = opcode & 0x0FFF;
		break;

	case 0x3000:
		vx = (opcode & 0x0F00) >> 8;
		nn = opcode & 0x00FF;
		if (variablesRegister[vx] == nn) {
			programCounter += 2;
		}

		programCounter += 2;
		break;

	case 0x4000:
		vx = (opcode & 0x0F00) >> 8;
		nn = opcode & 0x00FF;
		if (variablesRegister[vx] != nn){
			programCounter += 2;
		}

		programCounter += 2;
		break;

	case 0x5000:
		vx = (opcode & 0x0F00) >> 8;
		vy = (opcode & 0x00F0) >> 4;
		if (variablesRegister[vx] == variablesRegister[vy]){
			programCounter += 2;
		}

		programCounter += 2;
		break;

	case 0x6000:
		vx = (opcode & 0x0F00) >> 8;
		nn = opcode & 0x00FF;
		variablesRegister[vx] = nn;
		programCounter += 2;
		break;

	case 0x7000:
		vx = (opcode & 0x0F00) >> 8;
		nn = opcode & 0x00FF;
		variablesRegister[vx] += nn;
		programCounter += 2;
		break;

	case 0x8000:
		executeCase8();
		break;

	case 0x9000:
		vx = (opcode & 0x0F00) >> 8;
		vy = (opcode & 0x00F0) >> 4;
		if (variablesRegister[vx] != variablesRegister[vy]){
			programCounter += 2;
		}

		programCounter += 2;
		break;

	case 0xA000:
		indexRegister = opcode & 0x0FFF;
		programCounter += 2;
		break;

	case 0xB000:
		programCounter = (opcode & 0x0FFF) + variablesRegister[0]; 
		break;

	case 0xC000:
		index = (opcode & 0x0F00) >> 8;
		startNumber = opcode & 0x00FF;
		rndNumber = (rand() % 0xFF + 1) & startNumber;
		variablesRegister[index] = rndNumber;
		programCounter += 2;
		break;

	case 0xD000:
		drawSprite();
		break;

	case 0xE000:
		switch (opcode & 0x00FF){
		case 0x009E:
			vx = (opcode & 0x0F00) >> 8;
			if (keyPad[variablesRegister[vx]] != 0) {
				programCounter += 2;
			}

			programCounter += 2;
			break;

		case 0x00A1:
			vx = (opcode & 0x0F00) >> 8;
			if (keyPad[variablesRegister[vx]] == 0) {
				programCounter += 2;
			}

			programCounter += 2;
			break;
		}
		break;
			
	case 0xF000:
		executeCaseF();
		break;


	default:
		printf("Unknown test opcode: 0x%X\n\n", opcode);
	}
}

void Chip8::executeCaseF() {
	unsigned short vx = (opcode & 0x0F00) >> 8;
	bool keyPressed;

	switch (opcode & 0x00FF) {
	case 0x0007:
		variablesRegister[vx] = delayTimer;
		programCounter += 2;
		break;
		
	case 0x000A:
		keyPressed = false;
		for (int i = 0; i < KEYCOUNT; i++) {
			if (keyPad[i] != 0) {
				variablesRegister[vx] = i; 
				keyPressed = true;
			}
		}

		if (keyPressed) {
			programCounter += 2;	
		}

		break;

	case 0x0015:
		delayTimer = variablesRegister[vx];
		programCounter += 2;
		break;

	case 0x0018:
		soundTimer = variablesRegister[vx];
		programCounter += 2;
		break;
		
	case 0x001E:
		indexRegister += variablesRegister[vx];
		programCounter += 2;
		break;

	case 0x0029:
		indexRegister = variablesRegister[vx] * 0x5;
		programCounter += 2;
		break;

	case 0x0033:
		memory[indexRegister] = variablesRegister[vx] / 100;
		memory[indexRegister + 1] = (variablesRegister[vx] / 10) % 10;
		memory[indexRegister + 2] = variablesRegister[vx] % 10;
		programCounter += 2;
		break;

	case 0x0055:
		for (int i = 0; i < vx + 1; i++) {
			memory[indexRegister + i] = variablesRegister[i];
		}
		programCounter += 2;
		break;

	case 0x0065:
		for (int i = 0; i < vx + 1; i++) {
			variablesRegister[i] = memory[indexRegister + i];
		}
		programCounter += 2;
		break;

	default:
		printf("Unknown test2 opcode: 0x%X\n", opcode);
	}
}

void Chip8::executeCase8() {
	unsigned short vx = (opcode & 0x0F00) >> 8;
	unsigned short vy = (opcode & 0x00F0) >> 4;

	switch (opcode & 0x000F) {
	case 0x0000:
		variablesRegister[vx] = variablesRegister[vy];
		programCounter += 2;
		break;

	case 0x0001:
		variablesRegister[vx] = variablesRegister[vx] | variablesRegister[vy];
		programCounter += 2;
		break;

	case 0x0002:
		variablesRegister[vx] = variablesRegister[vx] & variablesRegister[vy];
		programCounter += 2;
		break;

	case 0x0003:
		variablesRegister[vx] = variablesRegister[vx] ^ variablesRegister[vy];
		programCounter += 2;
		break;

	case 0x0004:
		variablesRegister[vx] = variablesRegister[vx] + variablesRegister[vy];
		if ((variablesRegister[vx] + variablesRegister[vy]) > 0xFF) {
			variablesRegister[CARRYFLAGINDEX] = 1;
		}
		else {
			variablesRegister[CARRYFLAGINDEX] = 0;
		}

		programCounter += 2;
		break;

	case 0x0005:
		variablesRegister[vx] = variablesRegister[vx] - variablesRegister[vy];
		if (variablesRegister[vx] < variablesRegister[vy]) {
			variablesRegister[CARRYFLAGINDEX] = 0;
		}
		else {
			variablesRegister[CARRYFLAGINDEX] = 1;
		}

		programCounter += 2;
		break;

	case 0x0006:
		variablesRegister[CARRYFLAGINDEX] = variablesRegister[vx] & 0x1;
		variablesRegister[vx] = variablesRegister[vx] >> 1;
		programCounter += 2;
		break;

	case 0x0007:
		variablesRegister[vx] = variablesRegister[vy] - variablesRegister[vx];
		if (variablesRegister[vy] < variablesRegister[vx]) {
			variablesRegister[CARRYFLAGINDEX] = 0;
		}
		else {
			variablesRegister[CARRYFLAGINDEX] = 1;
		}

		programCounter += 2;
		break;

	case 0x000E:
		variablesRegister[CARRYFLAGINDEX] = variablesRegister[vx] & 0b10000000;
		variablesRegister[vx] = variablesRegister[vx] << 1;
		programCounter += 2;
		break;

	default:
		printf("Unknown test3 opcode: 0x%X\n", opcode);
	}
}

void Chip8::executeCase0() {
	switch (opcode & 0x000F) {
	case 0x0000:
		clearDisplay();
		drawFlag = true;
		programCounter += 2;
		break;

	case 0x000E:
		stackPointer--;
		programCounter = stack[stackPointer];
		break;

	//default:
		//programCounter += 2;
	}
}


void Chip8::drawSprite() {
	unsigned short VX = variablesRegister[(opcode & 0x0F00) >> 8];
	unsigned short VY = variablesRegister[(opcode & 0x00F0) >> 4];
	unsigned short height = opcode & 0x000F;
	unsigned short sprite;
	unsigned short width = 8;
	unsigned short newX = 0;
	unsigned short newY = 0;
	unsigned short pixelPosition = 0;

	if (VX == COLUMNS) {
		cout<<"vx == 0"<<endl;
	}

	if (VY == ROWS) {
		cout<<"vy == 0"<<endl;
	}
	variablesRegister[0xF] = 0;
	for (int row = 0; row < height; row++)
	{
		newY = (VY + row) % ROWS;
		sprite = memory[indexRegister + row];
		for (int column = 0; column < width; column++)
		{
			newX = (VX + column) % COLUMNS;
			if ((sprite & (0x80 >> column)) != 0)
			{
				if (VX + column >= COLUMNS) {
					cout<<"x = -"<<endl;
				}
				if (VY + row >= ROWS) {
					cout<<"y = -"<<endl;
				}

				if (graphicInterface[newX][newY] == 1)
					variablesRegister[0xF] = 1;

				graphicInterface[newX][newY] ^= 1;
			}
		}
	}
	drawFlag = true;
	programCounter += 2;
}

void Chip8::clearDisplay() {
	for (int i = 0; i < COLUMNS ; i++) {
		for (int j = 0; j < ROWS ; j++) {
			graphicInterface[i][j] = 0;
		}	
	}
}

bool Chip8::getDrawFlag() {
	return drawFlag;
}

void Chip8::setDrawFlag(bool flag) {
	drawFlag = flag;
}

void Chip8::updateKeyPad(uint8_t* newKeyPad) {
	for (int i = 0; i < KEYCOUNT; i++) {
		keyPad[i] = newKeyPad[i];
	}
}

void Chip8::copyGraphicBuffer(uint32_t* pixelMap) {
	uint8_t sprite;
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			sprite = graphicInterface[i][j];
			pixelMap[i + j*COLUMNS] = (0x00FFFFFF * sprite) | 0xFF000000;
		}
	}
}


void Chip8::debugOutput() {
	cout<< "Current Memory: " << endl;
	cout << "Opcode: "<< hex << opcode << endl;
	cout << "Program Counter: " << dec << programCounter << endl;
	cout << "Index Register: " << dec << indexRegister << endl;
	cout << "Stack Pointer: " << dec << stackPointer << endl;
	cout << "Delay Timer: " << dec << delayTimer << endl;
	cout << "Sound Timer: " << dec << soundTimer << endl;
	cout << "Variables: " << dec << programCounter << endl;

	for (int i = 0; i < VARIABLECOUNT; i++) {
		cout << "[" << i << "] : " <<  variablesRegister[i] << endl;
	}

	cout << "Stack: " << endl;
	
	for (int i = STACKSIZE - 1; i >= 0; i--) {
		cout << "[" << i << "] : " << hex <<  stack[i] << dec << endl;
	}
}
