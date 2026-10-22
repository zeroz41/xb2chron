#include "classes/gf/GfComAsm.h"
#include "classes/fw/PlacementGroundSolver.h"
#include "classes/fw/SlopeGroundSolver.h"
#include "classes/fw/TwoCharaGroundSolver.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComBehavior.h"

namespace gf {

FootIkControllerPlugin::FootIkControllerPlugin()
    : m_behavior(nullptr), m_mode(MODE_NONE), m_switcher(false), m_groundPlacement(false), m_enableDownIK(false),
      m_enableGroundPlacement(true), m_syncDown(false) {}

bool FootIkControllerPlugin::setup(gf::GfComBehavior& behavior) {
    m_behavior = &behavior;
    if (GfComIK* ik = behavior.m_owner->getComponent<GfComIK>(3)) {
        fw::PlacementGroundSolver* placement = ik->getSolver<fw::PlacementGroundSolver>(2);
        if (ik->getSolver<fw::SlopeGroundSolver>(0) != nullptr) {
            m_mode = MODE_SLOPE;
            if (placement != nullptr) {
                m_switcher = true;
            }
        } else if (placement != nullptr) {
            m_mode = MODE_PLACEMENT;
        }
        if (ik->getSolver<fw::TwoCharaGroundSolver>(2) != nullptr) {
            m_mode = MODE_TWO_CHARA;
        }
    }
    setGroundPlacement((getASMStateAttribute(behavior) & 1) != 0 && m_enableGroundPlacement);
    return true;
}

// 1.0.0 has it out of line; 3.0.1 keeps no copy (inline)
inline unsigned long FootIkControllerPlugin::getASMStateAttribute(gf::GfComBehavior& behavior) const {
    GfComAsm* asmCom = behavior.m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return 0;
    }
    return asmCom->getAttribute(AsmCategory(0), AnimLayer(0));
}

void FootIkControllerPlugin::setGroundPlacement(bool enable) {
    if (m_behavior == nullptr) {
        return;
    }
    if (GfComIK* ik = m_behavior->m_owner->getComponent<GfComIK>(3)) {
        switch (m_mode) {
        case MODE_PLACEMENT:
            if (fw::PlacementGroundSolver* solver = ik->getSolver<fw::PlacementGroundSolver>(2)) {
                solver->setEnablePlacement(enable);
            }
            break;
        case MODE_SLOPE:
            if (fw::SlopeGroundSolver* solver = ik->getSolver<fw::SlopeGroundSolver>(0)) {
                solver->setEnablePlacement(enable);
                solver->m_enableSlope = enable;
            }
            break;
        case MODE_TWO_CHARA:
            if (fw::TwoCharaGroundSolver* solver = ik->getSolver<fw::TwoCharaGroundSolver>(2)) {
                solver->setEnablePlacement(enable);
            }
            break;
        default:
            break;
        }
    }
    m_groundPlacement = enable;
}

void FootIkControllerPlugin::cleanup(gf::GfComBehavior&) {
    m_behavior = nullptr;
}

void FootIkControllerPlugin::onActivate() {}

void FootIkControllerPlugin::onDeactivate() {}

void FootIkControllerPlugin::update(gf::GfComBehavior& behavior, const fw::UpdateInfo&) {
    unsigned long attribute = getASMStateAttribute(behavior);
    setGroundPlacement((attribute & 1) != 0 && m_enableGroundPlacement);
    bool down = false;
    if (m_groundPlacement) {
        bool mode = m_mode == MODE_PLACEMENT || m_mode == MODE_TWO_CHARA;
        bool enable = m_enableDownIK || (attribute & 8) != 0;
        down = mode && enable;
    }
    if (GfComIK* ik = behavior.m_owner->getComponent<GfComIK>(3)) {
        if (fw::PlacementGroundSolver* solver = ik->getSolver<fw::PlacementGroundSolver>(2)) {
            solver->m_enableDown = down;
        }
        if (fw::TwoCharaGroundSolver* solver = ik->getSolver<fw::TwoCharaGroundSolver>(2)) {
            solver->m_enableDown = down;
        }
    }
    if (m_mode == MODE_TWO_CHARA) {
        if (GfComIK* ik = behavior.m_owner->getComponent<GfComIK>(3)) {
            if (fw::TwoCharaGroundSolver* solver = ik->getSolver<fw::TwoCharaGroundSolver>(2)) {
                if ((attribute & 2) != 0 || m_syncDown) {
                    solver->m_syncDown = 1;
                } else {
                    solver->m_syncDown = 0;
                }
            }
        }
    }
}

void FootIkControllerPlugin::switchMode(Mode mode) {
    if (m_switcher && m_mode != mode) {
        m_enableDownIK = false;
        setGroundPlacement(false);
        m_mode = mode;
    }
}

mm::mtl::RTTI FootIkControllerPlugin::m_rtti("FootIkControllerPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
