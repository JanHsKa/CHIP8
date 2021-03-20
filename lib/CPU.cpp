
#include <iostream>
#include "CPU.h"
#include <fstream>
#include "Macros.h"
#include <iomanip>



using namespace std;


CPU::CPU(Keypad* newKeyboard) :fontSet{ 
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
	0xF0, 0x80, 0xF0, 0x80, 0x80 },
	keypad(newKeyboard)
{
	initialize();
}

void CPU::initialize(){
	programSize = 0;
	programCounter = PROGRAM_START;  
	opcode = 0;      	
	indexRegister = 0;      
	stackPointer = 0;      
	drawFlag = false;

	clearDisplay();

	for (int i = 0; i < STACKSIZE; i++) {
		stack[i] = 0;
		variablesRegister[i] = 0;
	}

	for (int i = 0; i < MEMORYSIZE; i++) {
		memory[i] = 0;
	}
	
	for (int i = 0; i < 80; ++i)
		memory[i] = fontSet[i];

	delayTimer = 0;
	soundTimer = 0;
}

bool  CPU::load(const char *filePath) {
	FILE* file = fopen(filePath, "r");

	if (file == NULL) {
		cerr << "Failed to open ROM" <<endl;
		return false;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* fileBuffer = (char*)malloc(sizeof(char) * fileSize);

	size_t readSize = fread(fileBuffer, sizeof(char), (size_t)fileSize, file);

	if (readSize != fileSize) {
		cerr << "Failed to read ROM" <<endl;
		return false;
	}

	if (fileSize > (MEMORYSIZE - 512)) {
		cerr << "ROM is to large to read in to memory" <<endl;
		return false;
	} 
	else {
		programSize = readSize;
		for (int i = 0; i < fileSize; i++) {
			memory[i + PROGRAM_START] = (char)fileBuffer[i];
		}
	}

	fclose(file);
	free(fileBuffer);

	return true;
}

void CPU::processCommand(){
	opcode = getCurrentOpCode();
	//opcode = memory[programCounter] << 8 | memory[programCounter + 1];
	decodeOPcode();	
}

bool CPU::updateTimers(){
	if (delayTimer > 0)
		delayTimer--;

	if (soundTimer > 0){
		soundTimer--;
		return true;
	}

	return false;
}


void CPU::decodeOPcode(){
	unsigned short vx = (opcode & 0x0F00) >> 8;
	unsigned short nn = opcode & 0x00FF;
	unsigned short vy = (opcode & 0x00F0) >> 4;
	unsigned short index;

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
		if (variablesRegister[vx] == nn) {
			programCounter += 2;
		}
		programCounter += 2;
		break;

	case 0x4000:
		if (variablesRegister[vx] != nn){
			programCounter += 2;
		}
		programCounter += 2;
		break;

	case 0x5000:
		if (variablesRegister[vx] == variablesRegister[vy]){
			programCounter += 2;
		}
		programCounter += 2;
		break;

	case 0x6000:
		variablesRegister[vx] = nn;
		programCounter += 2;
		break;

	case 0x7000:
		variablesRegister[vx] += nn;
		programCounter += 2;
		break;

	case 0x8000:
		executeCase8();
		break;

	case 0x9000:
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
		uint8_t rndNumber;
		unsigned short startNumber;
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
			if (keypad->isKeypressed(variablesRegister[vx])) {
				keypad->resetKey(variablesRegister[vx]);
				programCounter += 2;
			}

			programCounter += 2;
			break;

		case 0x00A1:
			if (!keypad->isKeypressed(variablesRegister[vx])) {
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
		cerr<<"Unknown opcode: "<<hex<<opcode<<endl;
	}
}

void CPU::executeCaseF() {
	unsigned short vx = (opcode & 0x0F00) >> 8;
	bool keyPressed;

	switch (opcode & 0x00FF) {
	case 0x0007:
		variablesRegister[vx] = delayTimer;
		programCounter += 2;
		break;
		
	case 0x000A:
		keyPressed = false;
		if (keypad->isAnyKeypressed()) {
			keyPressed = true;
			variablesRegister[vx] = keypad->getPressedKey();
			keypad->resetKey(variablesRegister[vx]);
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
		if ( indexRegister < MEMORYSIZE - 3) {
			memory[indexRegister] = variablesRegister[vx] / 100;
			memory[indexRegister + 1] = (variablesRegister[vx] / 10) % 10;
			memory[indexRegister + 2] = variablesRegister[vx] % 10;

		} else {
			cerr<<"Failed to execute "<<hex<<opcode<<", indexRegister is out of bounds of Memory"<<endl;
		}
		programCounter += 2;
		break;

	case 0x0055:
		if (indexRegister + vx < MEMORYSIZE) {
			for (int i = 0; i < vx + 1; i++) {
				memory[indexRegister + i] = variablesRegister[i];
			}
		} else {
			cerr<<"Failed to execute "<<hex<<opcode<<", indexRegister is out of bounds of Memory"<<endl;
		}
		programCounter += 2;
		break;

	case 0x0065:
		if (indexRegister + vx < MEMORYSIZE) {
			for (int i = 0; i < vx + 1; i++) {
				variablesRegister[i] = memory[indexRegister + i];
			}
		} else {
			cerr<<"Failed to execute "<<hex<<opcode<<", indexRegister is out of bounds of Memory"<<endl;
		}

		programCounter += 2;
		break;

	default:
		cerr<<"Unknown opcode: "<<hex<<opcode<<endl;
	}
}

void CPU::executeCase8() {
	unsigned short x = (opcode & 0x0F00) >> 8;
	unsigned short y = (opcode & 0x00F0) >> 4;

	switch (opcode & 0x000F) {
	case 0x0000:
		variablesRegister[x] = variablesRegister[y];
		programCounter += 2;
		break;

	case 0x0001:
		variablesRegister[x] |= variablesRegister[y];
		programCounter += 2;
		break;

	case 0x0002:
		variablesRegister[x] &= variablesRegister[y];
		programCounter += 2;
		break;

	case 0x0003:
		variablesRegister[x] ^= variablesRegister[y];
		programCounter += 2;
		break;

	case 0x0004:
		if ((int(variablesRegister[x]) + int(variablesRegister[y])) > 0xFF) {
			variablesRegister[CARRY_FLAG_INDEX] = 1;
		}
		else {
			variablesRegister[CARRY_FLAG_INDEX] = 0;
		}
		variablesRegister[x] += variablesRegister[y];

		programCounter += 2;
		break;

	case 0x0005:
		if (variablesRegister[x] > variablesRegister[y]) {
			variablesRegister[CARRY_FLAG_INDEX] = 1;
		}
		else {
			variablesRegister[CARRY_FLAG_INDEX] = 0;
		}
		variablesRegister[x] -= variablesRegister[y];

		programCounter += 2;
		break;

	case 0x0006:
		variablesRegister[CARRY_FLAG_INDEX] = variablesRegister[x] & 0x1;
		variablesRegister[x] >>= 1;
		programCounter += 2;
		break;

	case 0x0007:
		if (variablesRegister[y] > variablesRegister[x]) {
			variablesRegister[CARRY_FLAG_INDEX] = 1;
		}
		else {
			variablesRegister[CARRY_FLAG_INDEX] = 0;
		}
		variablesRegister[x] = variablesRegister[y] - variablesRegister[x];

		programCounter += 2;
		break;

	case 0x000E:
		variablesRegister[CARRY_FLAG_INDEX] = variablesRegister[x] & 0b10000000;
		variablesRegister[x] <<= 1;
		programCounter += 2;
		break;

	default:
		cerr<<"Unknown opcode: "<<hex<<opcode<<endl;

	}
}

void CPU::executeCase0() {
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


void CPU::drawSprite() {
	unsigned short VX = variablesRegister[(opcode & 0x0F00) >> 8];
	unsigned short VY = variablesRegister[(opcode & 0x00F0) >> 4];
	unsigned short height = opcode & 0x000F;
	unsigned short sprite;
	unsigned short width = 8;
	unsigned short newX = 0;
	unsigned short newY = 0;
	unsigned short pixelPosition = 0;

	variablesRegister[0xF] = 0;
	for (int row = 0; row < height; row++) {
		newY = (VY + row) % ROWS;
		sprite = memory[indexRegister + row];

		for (int column = 0; column < width; column++) {
			newX = (VX + column) % COLUMNS;
			if ((sprite & (0x80 >> column)) != 0) {
				if (graphicInterface[newX][newY] == 1) {
					variablesRegister[0xF] = 1;
				}
				graphicInterface[newX][newY] ^= 1;
			}
		}
	}
	drawFlag = true;
	programCounter += 2;
}

void CPU::clearDisplay() {
	for (int i = 0; i < COLUMNS ; i++) {
		for (int j = 0; j < ROWS ; j++) {
			graphicInterface[i][j] = 0;
		}	
	}
}

bool CPU::getDrawFlag() {
	return drawFlag;
}

void CPU::setDrawFlag(bool flag) {
	drawFlag = flag;
}

void CPU::copyGraphicBuffer(uint32_t* pixelMap) {
	uint8_t sprite;
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			sprite = graphicInterface[i][j];
			pixelMap[i + j*COLUMNS] = (0x00FFFFFF * sprite) | 0xFF000000;
		}
	}
}

uint16_t CPU::getOpcode(uint16_t pc) {
	if (pc + 1 < MEMORYSIZE) {
		return memory[pc] << 8 | memory[pc + 1];
	}
	return 0;
}

uint16_t CPU::getCurrentOpCode() {
	return getOpcode(programCounter);
}


int CPU::getProgramSize() {
	return programSize;
}

int CPU::getProgramCounter() {
	return programCounter;
}


void CPU::debugOutput() {
	cout<< "Current Memory in decimal: " << endl<<endl;
	cout << "Opcode: "<< hex << getCurrentOpCode() << endl <<endl;
	cout << "Program Counter: " << dec << programCounter << endl <<endl;
	cout << "Index Register: " << dec << indexRegister << endl <<endl;
	cout << "Stack Pointer: " << dec << stackPointer << endl <<endl;
	cout << "Delay Timer: " << dec << unsigned(delayTimer) << endl <<endl;
	cout << "Sound Timer: " << dec << unsigned(soundTimer) << endl <<endl;
	cout << "Variables in Hex: " << endl; 

	for (int i = 0; i < VARIABLE_COUNT; i++) {
		cout << hex<< "[" << i << "] : "<<  unsigned(variablesRegister[i]) << endl;
	}

	cout<<endl;
	cout << "Stack in Hex: " << endl;
	
	for (int i = stackPointer; i >= 0; i--) {
		cout << "[" << i << "] : " << hex <<  stack[i] << endl;
	}

	cout<<endl;
}

