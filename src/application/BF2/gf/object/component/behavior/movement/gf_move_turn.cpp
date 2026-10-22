#include "mm/mtl/IntrusiveList.h"
#include "fw/Reflection.h"
#include "classes/gf/GfMoveTurnControler.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf {

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its file string in this file's
// .rodata.
void GfMoveTurnControler::createReflection(fw::Reflection* reflection, const char* name, unsigned int index) {
#line 14
    fw::ReflectionValueStruct* value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::ReflectionValueStruct(name, sizeof(Param), __alignof__(Param));
#line 15
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("angularVelMin", 0, 0.0f, 10000.0f, 10.0f));
#line 16
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("angularVelMax", 4, 0.0f, 10000.0f, 10.0f));
    reflection->setReflectionStruct(index, value);
}

void GfMoveTurnControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& target = packet.m_target;
    const mm::Vec3& direction = packet.m_direction;
    float cos = direction.dot(target);
    // within [-1, 1], and as good as parallel taken as parallel
    if (cos < -1.0f) {
        cos = -1.0f;
    } else if (cos > 1.0f || cos > 0.9999f) {
        cos = 1.0f;
    }
    float angle = mm::acos(cos);
    float limit = param->m_minAngularSpeed + angle / 3.14159265f * (param->m_maxAngularSpeed - param->m_minAngularSpeed);
    mm::Vec3 axis = target.cross(direction);
    float speed = mm::fabs(angle / info.m_deltaTime);
    float sign = axis.dot(mm::Vec3::unitY) >= 0.0f ? -1.0f : 1.0f;
    packet.m_angularSpeed = (limit < speed ? limit : speed) * sign;
}

}  // namespace gf
