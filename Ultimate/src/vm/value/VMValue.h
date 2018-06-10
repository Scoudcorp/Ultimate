#pragma once
#include <cstdint>

namespace Vm {

enum class Type {
    Null,
    Void,
    Boolean,
    Integer,
    Float,
    String
};

struct Value {
    Type m_type;

    union value {
        uint8_t m_boolean;
        int32_t m_integer;
        uint32_t m_unsignedInteger;
        float m_float;
        uint32_t m_stringReference;
    } m_value;

    Value add(const Value& value) const;
    Value subtract(const Value& value) const;
    Value multiply(const Value& value) const;
    Value divide(const Value& value) const;
    Value less(const Value& value) const;
    Value lessEqual(const Value& value) const;
    Value greater(const Value& value) const;
    Value greaterEqual(const Value& value) const;
    Value equal(const Value& value) const;
    Value notEqual(const Value& value) const;
    Value and_(const Value& value) const;
    Value or_(const Value& value) const;
    Value negate() const;
    Value not_() const;

    const char* getTypeString() const;
    void draw();
    void printAll() const;

private:
    void sanityCheck(const Value& value) const;
};
}
