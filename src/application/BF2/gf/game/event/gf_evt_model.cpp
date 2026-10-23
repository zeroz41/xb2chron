#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfGameManager.h"
#include "classes/event/Manager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfEvtModelDriver/StateIdleField.h"
#include "classes/gf/GfEvtModelDriver/StateIdleBattle.h"
#include "classes/gf/GfEvtModelDriver/StateStartBattle.h"
#include "classes/gf/GfEvtModelDriver/StateEndBattle.h"
#include "gf/GfObjFactory.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfEvtModelBlade/StateIdleField.h"
#include "classes/gf/GfEvtModelBlade/StateIdleBattle.h"
#include "classes/gf/GfEvtModelBlade/StateStartBattle.h"
#include "classes/gf/GfEvtModelBlade/StateEndBattle.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfEvtModelEnemy/StateIdleField.h"
#include "classes/gf/GfEvtModelEnemy/StateIdleBattle.h"
#include "classes/gf/GfEvtModelEnemy/StateStartBattle.h"
#include "classes/gf/GfEvtModelEnemy/StateEndBattle.h"
#include "ai/Fsm.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfObjFactory.h"

namespace gf {

GfEvtModelDriver::GfEvtModelDriver(GfInitParamDriver& param)
    : GfEvtModel(0, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    m_bladeId = param.m_bladeId;
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    m_handle = GfObjFactory::createDriver(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
    if (m_bladeId == 0) {
        DataParamAcc acc(3, param.m_objId, static_cast<GimmickType>(0));
        m_bladeId = acc.getBlade(-1, false);
    }
}

GfEvtModelBlade::GfEvtModelBlade(GfInitParamBlade& param)
    : GfEvtModel(1, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    if (param.getBladeID() == 0x451) {
        param.pad_a5 = true;
    }
    m_handle = GfObjFactory::createBlade(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
}

GfEvtModelEnemy::GfEvtModelEnemy(GfInitParamEnemy& param)
    : GfEvtModel(5, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    m_handle = GfObjFactory::createEnemy(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
}

}  // namespace gf
