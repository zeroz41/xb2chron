#include "gf/FileStaticVec3.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gf/GfComBehaviorEvent.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "mm/mtl/Delegate.h"
#include "mm/Col4.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "fw/Message.h"
#include "fw/ColiDamage.h"
#include "gf/CallBackCache.h"
#include "gf/PluginManager.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComPropertyEvent.h"
#include "classes/gf/GfObj.h"
#include "fw/ColiCheck.h"
#include "algorithm"
#include <new>
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfComModel.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfFieldUndulator.h"
#include "gf/MsgPcGetLookPoint.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComTransform.h"
#include "fw/Transform.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/SpineIkSolver.h"

namespace gf {

void GfEnemySensor::update(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isGameTypeIra()) {
        updateIra(handle);
    } else {
        updateMain(handle);
    }
}

EnviromentSensor::GroundInfo::GroundInfo()
    : m_pos(mm::Vec3::zero), m_attr(0), m_obj(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_velocity(mm::Vec3::zero),
      pad_50(mm::Col4::white), pad_60(0) {
    new (&m_plane) mm::Plane(mm::Vec3::unitY, mm::Vec3::zero);
}

EnviromentSensor::EnviromentSensor() : m_checkFlags(0), m_flags(0) {
    pad_290 = 1.0f;
}

// searchVertical's std::sort order for the hits: nearest first along the search direction (the name is the
// original's, from the sort's template arguments; the member's is not)
struct ContactLess {
    bool operator()(const fw::ContactInfo& a, const fw::ContactInfo& b) const {
        return m_dir->dot(a.m_position) < m_dir->dot(b.m_position);
    }
    const mm::Vec3* m_dir;
};

GfComBehaviorEvent::GfComBehaviorEvent() : m_flags(0) {}

void GfComBehaviorEvent::setup() {
    if (GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2)) {
        evtAnim->m_asm.m_callbacks[0].name = "system";
        evtAnim->m_asm.m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this),
                                                   &GfComBehavior::callbackAnimForEvent);
    }
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(FootIkControllerPlugin::PLUGIN_ID, &FootIkControllerPlugin::create, true);
    m_pluginManager.endSetup();
    if (FootIkControllerPlugin* footIk = getPlugin<FootIkControllerPlugin>(FootIkControllerPlugin::PLUGIN_ID)) {
        footIk->setActivate(true);
    }
}

void GfComBehaviorEvent::cleanup() {
    m_pluginManager.cleanup();
}

void GfComBehaviorEvent::update(const fw::UpdateInfo& info) {
    m_pluginManager.update(info);
    if (!(m_flags & 1)) {
        setFootIK(true);
        m_flags |= 1;
    }
    m_turnCmd.update(info.m_deltaTime);
}

void GfComBehaviorEvent::setFootIK(bool enable) {
    if (m_owner->getComponent<GfComIK>(3) != nullptr) {
        GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2);
        if (evtAnim != nullptr && evtAnim->m_asm.m_control != nullptr) {
            if (FootIkControllerPlugin* footIk = getPlugin<FootIkControllerPlugin>(FootIkControllerPlugin::PLUGIN_ID)) {
                footIk->m_enableDownIK = enable;
            }
        }
    }
}

// turns the look IK toward its target (fades it in, or over to the new target once on) or fades it out; with
// lookOnly the spine is left alone. Bit 1 of m_flags: the look IK is on
void GfComBehaviorEvent::setTarget(bool enable, float time, bool lookOnly) {
    if (GfComIK* ik = m_owner->getComponent<GfComIK>(3)) {
        GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2);
        if (evtAnim != nullptr && evtAnim->m_asm.m_control != nullptr) {
            if (fw::LookIkSolver* look = ik->getSolver<fw::LookIkSolver>(3)) {
                fw::SpineIkSolver* spine = look->m_spine.get();
                fw::LookAtIkSolver* lookAt = look->m_lookAt.get();
                if (enable) {
                    if (m_flags & 2) {
                        if (lookAt != nullptr) {
                            lookAt->startTargetFade(time);
                        }
                        if (spine != nullptr && !lookOnly) {
                            spine->startTargetFade(time);
                        }
                    } else {
                        if (lookAt != nullptr) {
                            lookAt->fadeIn(time);
                        }
                        if (spine != nullptr && !lookOnly) {
                            spine->fadeIn(time);
                        }
                    }
                    m_flags |= 2;
                } else {
                    if (lookAt != nullptr) {
                        lookAt->fadeOut(time);
                    }
                    if (spine != nullptr && !lookOnly) {
                        spine->fadeOut(time);
                    }
                    m_flags &= ~2;
                }
            }
        }
    }
}

void GfComBehaviorEvent::setTargetPos(const mm::Vec3& pos) {
    if (GfComIK* ik = m_owner->getComponent<GfComIK>(3)) {
        GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2);
        if (evtAnim != nullptr && evtAnim->m_asm.m_control != nullptr) {
            if (fw::LookIkSolver* look = ik->getSolver<fw::LookIkSolver>(3)) {
                fw::SpineIkSolver* spine = look->m_spine.get();
                fw::LookAtIkSolver* lookAt = look->m_lookAt.get();
                if (lookAt != nullptr) {
                    lookAt->m_target = pos;
                }
                if (spine != nullptr) {
                    spine->m_target = pos;
                }
            }
        }
    }
}

void GfComBehaviorEvent::execTurnCmd(float rotY, float speed, float threshold, float delay) {
    TFieldExecCmdTurn<GfComEvtAnim>::CreateInfo info;
    info.handle = static_cast<GfObj*>(m_owner)->m_handle;
    info.pad_8 = rotY;
    info.pad_c = threshold;
    info.pad_14 = speed;
    info.pad_18 = delay;
    m_turnCmd.create(info);
}

GfComBehaviorEvent::~GfComBehaviorEvent() {}

template <typename T>
void TFieldExecCmd<T>::create(const CreateInfo& info) {
    m_executed = false;
    clear();
    m_info = info;
}

// TFieldExecCmdTurn<GfComEvtAnim>::create's (not written yet)
template void TFieldExecCmd<GfComEvtAnim>::create(const CreateInfo& info);

// whether the command's state is already the current one ("S_..." for "C_...") or the component executes it
template <typename T>
bool TFieldExecCmd<T>::execCmd(T& com, const char* name) const {
    if (com.getStateName() == nullptr) {
        return false;
    }
    mm::mtl::FixStr<32> state(com.getStateName());
    if (strcmp(name + 1, state.m_str + 1) == 0) {
        return true;
    }
    return com.execCmd(name);
}

// TFieldExecCmd<GfComEvtAnim>::update's (not written yet)
template bool TFieldExecCmd<GfComEvtAnim>::execCmd(GfComEvtAnim& com, const char* name) const;

mm::mtl::RTTI GfComBehaviorEvent::m_rtti("GfComBehaviorEvent", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf

// searchVertical's std::sort (not written yet) instantiates the libc++ sort core for the hits.
template void std::__sort<gf::ContactLess&, fw::ContactInfo*>(fw::ContactInfo*, fw::ContactInfo*, gf::ContactLess&);
