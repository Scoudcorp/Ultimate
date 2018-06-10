#pragma once
#include <cstdint>

namespace Vm {

enum class Instruction : uint8_t {
    Abort,
    Return,
    Jump,
    JumpZero,
    JumpNotZero,
    PushPosition,
    PushStackIndex,
    Call,
    Stop,
    Wait,
    WaitUntil,
    Notify,
    Thread,
    Pop,
    ConstantNull,
    ConstantVoid,
    ConstantBoolean,
    ConstantInteger,
    ConstantFloat,
    ConstantString,
    Test,
    Add,
    Subtract,
    Multiply,
    Divide,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Equal,
    NotEqual,
    And,
    Or,
    Negate,
    Not,
    Set,
    Get
};
}
