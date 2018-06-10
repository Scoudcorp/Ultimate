#pragma once
#include <cstdint>

namespace Opcode {

enum Instruction : uint8_t {
    End,
    Return,
    ReadByte,
    ReadByteNegate,
    ReadUnsignedShort,
    ReadUnsignedShortNegate,
    ReadInteger,
    ReadVm10,
    ReadVm11,
    ReadFloat,
    ReadStringReference,
    ReadUndefined,
    ReadZero,
    Vm13,
    CreateLocalVariable,
    Vm15,
    EvalLocal0,
    EvalLocal1,
    EvalLocal2,
    EvalLocal3,
    EvalLocal4,
    EvalLocal5,
    EvalLocalTop,
    NumOpcodes
};

constexpr size_t InstructionSize(const Instruction instruction)
{
    switch (instruction) {
    case End:
        return 1;
    case Return:
        return 1;
    case ReadByte:
        return 1;
    case ReadByteNegate:
        return 2;
    case ReadUnsignedShort:
        return 3;
    case ReadUnsignedShortNegate:
        return 3;
    case ReadInteger:
        return 5;
    case ReadVm10:
        return 3;
    case ReadVm11:
        return 3;
    case ReadFloat:
        return 5;
    case ReadStringReference:
        return 3;
    case ReadUndefined:
        return 1;
    case ReadZero:
        return 1;
    case Vm13:
		return 1;
    case CreateLocalVariable:
		return 3;
    case Vm15:
		return 2;
    case EvalLocal0:
		return 1;
    case EvalLocal1:
		return 1;
    case EvalLocal2:
		return 1;
    case EvalLocal3:
		return 1;
    case EvalLocal4:
		return 1;
    case EvalLocal5:
		return 1;
    case EvalLocalTop:
		return 2;
    case NumOpcodes:
    default:
        return 1;
    }
}
}
