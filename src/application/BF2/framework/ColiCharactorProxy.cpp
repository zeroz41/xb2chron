#include "classes/fw/ColiCharactorProxy.h"
#include "classes/fw/ColiObject.h"
#include "idcoli/IDColiMove.h"

namespace fw {

ColiCharactorProxy::ColiCharactorProxy() : m_object(nullptr), m_floor(0.4f) {}

void ColiCharactorProxy::integrate(mm::Vec3 const& position, mm::Vec3 const& move, mm::Vec3* result) {
    mm::Vec3 target = position + move;
    idcoli::IDColiMove coliMove;
    coliMove.setFloor(m_floor);
    coliMove.setAccuracy(true);
    coliMove.moveColi(m_object->m_coliObj, target);
    *result = coliMove.m_result;
}

}  // namespace fw
