#include "VMValue.h"
#include <algorithm>
#include <imgui/imgui.h>

Vm::Value Vm::Value::add(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_integer = m_value.m_integer + value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_float = m_value.m_float + value.m_value.m_float;
        break;
    default:
        std::printf("Unable to add type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::subtract(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_integer = m_value.m_integer - value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_float = m_value.m_float - value.m_value.m_float;
        break;
    default:
        std::printf("Unable to subtract type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::multiply(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_integer = m_value.m_integer * value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_float = m_value.m_float * value.m_value.m_float;
        break;
    default:
        std::printf("Unable to multiply type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::divide(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_integer = m_value.m_integer / value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_float = m_value.m_float / value.m_value.m_float;
        break;
    default:
        std::printf("Unable to divide type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::less(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer < value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float < value.m_value.m_float;
        break;
    default:
        std::printf("Unable to less type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::lessEqual(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer <= value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float <= value.m_value.m_float;
        break;
    default:
        std::printf("Unable to less equal type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::greater(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer > value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float > value.m_value.m_float;
        break;
    default:
        std::printf("Unable to greater type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::greaterEqual(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer > value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float > value.m_value.m_float;
        break;
    default:
        std::printf("Unable to greater equal type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::equal(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer == value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float == value.m_value.m_float;
        break;
    case Type::Boolean:
        result.m_value.m_boolean = m_value.m_boolean == value.m_value.m_boolean;
        break;
    default:
        std::printf("Unable to equal type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::notEqual(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_boolean = m_value.m_integer != value.m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_boolean = m_value.m_float != value.m_value.m_float;
        break;
    case Type::Boolean:
        result.m_value.m_boolean = m_value.m_boolean != value.m_value.m_boolean;
        break;
    default:
        std::printf("Unable to not equal type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::and_(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Boolean:
        result.m_value.m_boolean = m_value.m_integer && value.m_value.m_integer;
        break;
    default:
        std::printf("Unable to and type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::or_(const Value& value) const
{
    sanityCheck(value);

    Value result{};
    result.m_type = Type::Boolean;

    switch (m_type) {
    case Type::Boolean:
        result.m_value.m_boolean = m_value.m_integer || value.m_value.m_integer;
        break;
    default:
        std::printf("Unable to or type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::negate() const
{
    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Integer:
        result.m_value.m_integer = -m_value.m_integer;
        break;
    case Type::Float:
        result.m_value.m_float = -m_value.m_float;
        break;
    default:
        std::printf("Unable to negate type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

Vm::Value Vm::Value::not_() const
{
    Value result{};
    result.m_type = m_type;

    switch (m_type) {
    case Type::Boolean:
        result.m_value.m_boolean = !m_value.m_integer;
        break;
    default:
        std::printf("Unable to not type %d\n", m_type);
        printAll();
        std::abort();
    }

    return result;
}

const char* Vm::Value::getTypeString() const
{
    switch (m_type) {
    case Type::Null:
        return "Null";
    case Type::Void:
        return "Void";
    case Type::Boolean:
        return "Boolean";
    case Type::Integer:
        return "Integer";
    case Type::Float:
        return "Float";
    case Type::String:
        return "String";
    default:
        return "ERROR_TYPE";
    }
}

void Vm::Value::draw()
{
    ImGui::Text(getTypeString());
    switch (m_type) {
    case Type::Boolean:
        ImGui::Text("Boolean: %s", m_value.m_boolean ? "true" : "false");
        break;
    case Type::Integer:
        ImGui::Text("Integer: %d", m_value.m_integer);
        ImGui::Text("Unsigned integer: %d", m_value.m_unsignedInteger);
        break;
    case Type::Float:
        ImGui::Text("Float: %g", m_value.m_float);
        break;
    case Type::String:
        ImGui::Text("String: %d", m_value.m_stringReference);
        break;
    case Type::Null:
    case Type::Void:
    default:;
    }
}

void Vm::Value::printAll() const
{
    std::printf(
        "Value(\n  %s\n  %s\n  %d\n  %d\n  %g\n  %d\n)\n",
        getTypeString(),
        m_value.m_boolean ? "true" : "false",
        m_value.m_integer,
        m_value.m_unsignedInteger,
        m_value.m_float,
        m_value.m_stringReference);
}

void Vm::Value::sanityCheck(const Value& value) const
{
    if (m_type != value.m_type) {
        abort();
    }
}
