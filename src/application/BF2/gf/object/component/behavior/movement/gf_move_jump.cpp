#include "mm/mtl/IntrusiveList.h"
#include "fw/Reflection.h"
#include "classes/gf/GfMoveJumpControler.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf {

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
void GfMoveJumpControler::createReflection(fw::Reflection* reflection, const char* name, unsigned int index) {
#line 15
    fw::ReflectionValueStruct* value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::ReflectionValueStruct(name, sizeof(Param), __alignof__(Param));
#line 16
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("velocityMax", 0, 0.001f, 10000.0f, 7.8f));
#line 17
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("accel", 4, 0.0f, 10000.0f, 10.0f));
#line 18
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("angularVelMax", 8, 0.0f, 10000.0f, 10.0f));
#line 19
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("angularAccel", 12, 0.0f, 10000.0f, 10.0f));
    reflection->setReflectionStruct(index, value);
}

void GfMoveJumpControler::update(const fw::UpdateInfo& info, Packet& packet) {
    calcVelocity(info.m_deltaTime, packet);
    calcAngularVelocity(info.m_deltaTime, packet);
}

void GfMoveJumpControler::calcVelocity(float deltaTime, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    float target = param->m_maxSpeed * packet.m_inputRate;
    // the speed along the facing
    float speed = packet.m_velocity.dot(packet.m_direction);
    if (target > speed) {
        speed = speed + deltaTime * param->m_acceleration;
        speed = speed < target ? speed : target;
    } else if (target < speed) {
        speed = speed - deltaTime * param->m_acceleration;
        speed = speed > target ? speed : target;
    }
    packet.m_velocity = packet.m_direction * speed;
}

void GfMoveJumpControler::calcAngularVelocity(float deltaTime, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& target = packet.m_inputDirection;
    const mm::Vec3& direction = packet.m_direction;
    float cos = direction.dot(target);
    // within [-1, 1], and as good as parallel taken as parallel
    if (cos < -1.0f) {
        cos = -1.0f;
    } else if (cos > 1.0f || cos > 0.99f) {
        cos = 1.0f;
    }
    float angle = mm::acos(cos);
    mm::Vec3 axis = target.cross(direction);
    float speed = angle / deltaTime;
    float size = mm::fabs(speed);
    float sign = axis.dot(mm::Vec3::unitY) >= 0.0f ? -1.0f : 1.0f;
    float velocity = size * sign;
    if (velocity > packet.m_angularVelocity) {
        packet.m_angularVelocity = packet.m_angularVelocity + param->m_angularAcceleration * deltaTime;
    } else if (packet.m_angularVelocity > velocity) {
        packet.m_angularVelocity = packet.m_angularVelocity - param->m_angularAcceleration * deltaTime;
    }
    packet.m_angularVelocity = mm::clamp(packet.m_angularVelocity, -speed, speed);
    packet.m_angularVelocity =
        mm::clamp(packet.m_angularVelocity, -param->m_maxAngularVelocity, param->m_maxAngularVelocity);
}

}  // namespace gf
