#include "mm/mtl/IntrusiveList.h"
#include "fw/Reflection.h"
#include "gf/GfParamPcColi.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "fw/Allocator.h"

namespace gf {

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
void PcColiParam::createReflection(fw::Reflection* reflection, const char* name, unsigned int index) {
#line 18
    fw::ReflectionValueStruct* value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::ReflectionValueStruct(name, sizeof(PcColiParam), __alignof__(PcColiParam));
#line 19
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("radiusCapsule", 0, 0.01f, 1000.0f, 0.5f));
#line 20
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("heightCapsule", 4, 0.01f, 1000.0f, 2.0f));
#line 21
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("radiusShpere", 8, 0.01f, 1000.0f, 1.5f));
#line 22
    fw::ReflectionValueEnum* type = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::ReflectionValueEnum("type", 12);
#line 23
    type->addElem(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                      fw::ReflectionValueEnumElem("capsule", 0));
#line 24
    type->addElem(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                      fw::ReflectionValueEnumElem("sphere", 1));
    value->addValue(type);
#line 26
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("bakkyoHeadDist", 16, 0.0f, 10.0f, 0.9f));
    reflection->setReflectionStruct(index, value);
}

const PcColiParam* getPcColiParameter() {
    return fw::ParamManager::get()->m_paramLists[17]->getAdapter(0).get<PcColiParam>();
}

}  // namespace gf
