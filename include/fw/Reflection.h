#ifndef FW_REFLECTION_H
#define FW_REFLECTION_H

#include <stddef.h>
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Vector.h"

// The framework's parameter reflection: what a parameter block holds, value by value, so a param list's binary
// can be read into it (fw::ParamBuilder::importBinary takes a Reflection). Each block's createReflection (1.0.0's
// symbols name them: gf::GfMoveJumpControler::createReflection, gf::PcColiParam::createReflection, ...) builds a
// ReflectionValueStruct of its values and sets it into a Reflection. 3.0.1 keeps none of it: its linker dropped the
// createReflection functions and with them every table here, so these classes are laid out from 1.0.0's code (the
// tables, ReflectionValuePod<float, (fw::ValueType)6> and the destructors are 1.0.0's names). Member names, the
// enumerators and the helpers' names are not the original's.

namespace fw {
// a value's kind (1.0.0's ReflectionValuePod<float, (fw::ValueType)6>, <int, 5>, <unsigned int, 2>)
enum ValueType {
    VALUE_TYPE_U32 = 2,
    VALUE_TYPE_S32 = 5,
    VALUE_TYPE_F32 = 6,
    VALUE_TYPE_STRUCT = 9,
    VALUE_TYPE_ENUM = 10,
    VALUE_TYPE_ENUM_ELEM = 11,
};

// table _ZTVN2fw15ReflectionValueE (1.0.0); counted, and linked into its struct's list by its node base (the node
// base is constructed first: 1.0.0's code links the node before it clears the count). Its virtual functions, and
// those of the classes below, are inline: 1.0.0 has weak copies of them where a file first constructs one.
class ReflectionValue : public mm::mtl::IntrusiveListNodeBase, public mm::mtl::ReferenceObject {
public:
    // sized by the derived class's constructor (each stores its size after this one's 0)
    ReflectionValue(const char* name, ValueType type, size_t offset)
        : m_name(name), m_type(type), m_size(0), m_offset(offset) {}
    virtual ~ReflectionValue() {}  // slot 0
    virtual void writeDefault(unsigned char* data) const {}  // slot 2: its default into data at its offset

    mm::mtl::FixStr<64> m_name;  // the name the param list's binary knows it by
    ValueType m_type;
    size_t m_size;    // in the block
    size_t m_offset;  // in the block; the writeDefaults store at it
};

// a value of a plain type: its range and its default (writeDefault stores the default)
template <typename T, ValueType TYPE>
class ReflectionValuePod : public ReflectionValue {
public:
    ReflectionValuePod(const char* name, size_t offset, T min, T max, T def)
        : ReflectionValue(name, TYPE, offset), m_min(min), m_max(max), m_default(def) {
        m_size = sizeof(T);
    }
    virtual void writeDefault(unsigned char* data) const {  // slot 2
        T* value = reinterpret_cast<T*>(data + m_offset);
        *value = m_default;
    }

    T m_min;
    T m_max;
    T m_default;
};

// table _ZTVN2fw18ReflectionValueF32E (1.0.0)
class ReflectionValueF32 : public ReflectionValuePod<float, VALUE_TYPE_F32> {
public:
    ReflectionValueF32(const char* name, size_t offset, float min, float max, float def)
        : ReflectionValuePod<float, VALUE_TYPE_F32>(name, offset, min, max, def) {}
    virtual ~ReflectionValueF32() {}  // slot 0
};

// table _ZTVN2fw21ReflectionValueStructE (1.0.0): a block of values, which it holds a reference to each of
class ReflectionValueStruct : public ReflectionValue {
public:
    ReflectionValueStruct(const char* name, size_t size, size_t alignment)
        : ReflectionValue(name, VALUE_TYPE_STRUCT, 0), m_alignment(alignment) {
        m_size = size;
    }
    virtual ~ReflectionValueStruct() {  // slot 0
        while (!m_values.empty()) {
            m_values.pop_front()->release();
        }
    }
    virtual void writeDefault(unsigned char* data) const {  // slot 2: each value's
        for (mm::mtl::IntrusiveList<ReflectionValue>::iterator it = m_values.begin(); it != m_values.end(); ++it) {
            it->writeDefault(data);
        }
    }

    void addValue(ReflectionValue* value) {
        value->addRef();
        m_values.push_back(value);
    }

    mm::mtl::IntrusiveList<ReflectionValue> m_values;
    size_t m_alignment;  // the block's
};

// one choice of an enum value: its name and the number it stands for
class ReflectionValueEnumElem : public ReflectionValue {
public:
    ReflectionValueEnumElem(const char* name, int value)
        : ReflectionValue(name, VALUE_TYPE_ENUM_ELEM, 0), m_value(value) {}
    virtual ~ReflectionValueEnumElem() {}  // slot 0 (table _ZTVN2fw23ReflectionValueEnumElemE, 1.0.0)

    int m_value;
};

// table _ZTVN2fw19ReflectionValueEnumE (1.0.0): an int that takes one of its elements' values
class ReflectionValueEnum : public ReflectionValue {
public:
    ReflectionValueEnum(const char* name, size_t offset)
        : ReflectionValue(name, VALUE_TYPE_ENUM, offset), m_default(0) {
        m_size = sizeof(int);
    }
    virtual ~ReflectionValueEnum() {  // slot 0
        while (!m_elems.empty()) {
            m_elems.pop_front()->release();
        }
    }
    virtual void writeDefault(unsigned char* data) const {  // slot 2
        int* value = reinterpret_cast<int*>(data + m_offset);
        *value = m_default;
    }

    void addElem(ReflectionValueEnumElem* elem) {
        elem->addRef();
        m_elems.push_back(elem);
    }

    mm::mtl::IntrusiveList<ReflectionValueEnumElem> m_elems;
    int m_default;
};

// table _ZTVN2fw10ReflectionE (1.0.0): the parameter blocks of a param list, one per index
class Reflection : public mm::mtl::ReferenceObject {
public:
    // 1.0.0's GfGameTarget::createReflection builds one so (inline: the original has no copy)
    explicit Reflection(mm::mtl::IAllocator* allocator) : m_structs(allocator) {}
    virtual ~Reflection();  // slot 0

    // value referenced at index, the one there before released (1.0.0's out-of-line copy is this)
    void setReflectionStruct(unsigned int index, ReflectionValueStruct* value) {
        if (m_structs[index] != nullptr) {
            m_structs[index]->release();
            m_structs[index] = nullptr;
        }
        m_structs[index] = value;
        value->addRef();
    }

    mm::mtl::Vector<ReflectionValueStruct*> m_structs;
};
}  // namespace fw

#endif
