#pragma once
#include "Opcode.h"


class Disassembler
{
	Opcode::Instruction *m_instructionPointer;

public:

	explicit Disassembler(Opcode::Instruction* entryPoint)
		: m_instructionPointer(entryPoint)
	{
	}

	void read();
	void handleInstruction(Opcode::Instruction instruction) const;

	void printInstruction(const char* format, ...);

};
