#include "Disassembler.h"
#include "Opcode.h"
#include "iw4/iw_string.h"
#include <cstdio>

void Disassembler::read()
{
    auto i = 0;

    std::printf("========== BEGIN DUMP ==========\n");

    while (i < 100) {
        const auto currentInstruction = *m_instructionPointer;

        m_instructionPointer += 1;

        handleInstruction(currentInstruction);

        const auto instructionSize = Opcode::InstructionSize(currentInstruction);
        m_instructionPointer += instructionSize - 1;

        i += 1;
    }

    std::printf("========== END DUMP ==========\n");
}

void Disassembler::handleInstruction(const Opcode::Instruction instruction) const
{
    int32_t intValue;
    float floatValue;
    const char* actualStringValue;

    switch (instruction) {
    case Opcode::End: {
        std::printf("end\n");
        break;
    }
    case Opcode::Return: {
        std::printf("return\n");
        break;
    }
    case Opcode::ReadByte: {
        intValue = *m_instructionPointer;
        std::printf("byte %d\n", intValue);
        break;
    }
    case Opcode::ReadByteNegate: {
        intValue = *m_instructionPointer;
        std::printf("byte -%d\n", intValue);
        break;
    }
    case Opcode::ReadUnsignedShort: {
        intValue = *m_instructionPointer;
        std::printf("short %d\n", intValue);
        break;
    }
    case Opcode::ReadUnsignedShortNegate: {
        intValue = *m_instructionPointer;
        std::printf("short -%d\n", intValue);
        break;
    }
    case Opcode::ReadInteger: {
        intValue = *m_instructionPointer;
        std::printf("int %d\n", intValue);
        break;
    }
    case Opcode::ReadVm10: {
        intValue = *m_instructionPointer;
        std::printf("vm10 %d\n", intValue);
        break;
    }
    case Opcode::ReadVm11: {
        intValue = *m_instructionPointer;
        std::printf("vm11 %d\n", intValue);
        break;
    }
    case Opcode::ReadFloat: {
        floatValue = *m_instructionPointer;
        std::printf("float %g\n", floatValue);
        break;
    }
    case Opcode::ReadStringReference: {
        intValue = *m_instructionPointer;
        actualStringValue = String::ConvertToString(intValue);
        std::printf("string %d %s\n", intValue, actualStringValue);
        break;
    }
    case Opcode::ReadUndefined: {
        std::printf("undefined\n");
        break;
    }
    case Opcode::ReadZero: {
        std::printf("zero\n");
        break;
    }
    case Opcode::Vm13: {
		std::printf("vm13 (some stack stuff)\n");
        break;
    }
    case Opcode::CreateLocalVariable: {
		std::printf("create local variable\n");
        break;
    }
    case Opcode::Vm15: {
		std::printf("vm15\n");
        break;
    }
    case Opcode::EvalLocal0: {
		std::printf("eval local 0\n");
        break;
    }
    case Opcode::EvalLocal1: {
		std::printf("eval local 1\n");
        break;
    }
    case Opcode::EvalLocal2: {
		std::printf("eval local 2\n");
        break;
    }
    case Opcode::EvalLocal3: {
		std::printf("eval local 3\n");
        break;
    }
    case Opcode::EvalLocal4: {
		std::printf("eval local 4\n");
        break;
    }
    case Opcode::EvalLocal5: {
		std::printf("eval local 5\n");
        break;
    }
    case Opcode::EvalLocalTop: {
		std::printf("eval local top\n");
        break;
    }
    case Opcode::NumOpcodes: {
    default:
        std::printf("%p: %3d\n", m_instructionPointer - 1, instruction);
    }
    }
}
