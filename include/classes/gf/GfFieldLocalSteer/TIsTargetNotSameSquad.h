#ifndef CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H
#define CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H

#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/GmkSquad.h"
#include "classes/gmk/GmkSquadLeader.h"
#include "gf/GfObjAcc.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a template: 2 instances in the module. GfComBehaviorMob's constructor installs its table at 0x5320, right after
// its steering. Each owner's unit emits its operator (GfComBehaviorEnemy's through an explicit instantiation)
template <typename T>
class GfFieldLocalSteer::TIsTargetNotSameSquad {
public:
    // whether the target the steering considers is not of the steering object's squad
    virtual bool operator()(const gf::GfFieldLocalSteer& steer, gf::GF_OBJ_HANDLE* target) const;  // slot 0
};

// true unless the target is a T (GfComBehaviorMob, GfComBehaviorEnemy) of the steering object's squad and the
// squad's leader gimmick's data starts with 1 (T::getSquadNavi gives an owner's squad place)
template <typename T>
bool GfFieldLocalSteer::TIsTargetNotSameSquad<T>::operator()(const GfFieldLocalSteer& steer,
                                                           GF_OBJ_HANDLE* target) const {
    gmk::GmkSquad* squad;
    {
        GfObjAcc acc(steer.m_info.m_handle);
        GfObj* obj = acc.getObj();
        if (obj == nullptr) {
            return true;
        }
        T* owner = obj->getComponent<T>(6);
        if (owner == nullptr) {
            return true;
        }
        squad = owner->getSquadNavi().m_info.m_squad;
        if (squad == nullptr) {
            return true;
        }
    }
    gmk::GmkSquad* targetSquad = nullptr;
    {
        GfObjAcc acc(target);
        GfObj* obj = acc.getObj();
        T* other = obj != nullptr ? obj->getComponent<T>(6) : nullptr;
        if (other != nullptr) {
            targetSquad = other->getSquadNavi().m_info.m_squad;
        }
    }
    if (squad != targetSquad) {
        return true;
    }
    gmk::GmkSquadLeader* leader = squad->getBindedGmkSquadLeader();
    if (leader != nullptr && *reinterpret_cast<const unsigned int*>(leader->m_createInfo.m_data) == 1) {
        return false;
    }
    return true;
}
}  // namespace gf

#endif
