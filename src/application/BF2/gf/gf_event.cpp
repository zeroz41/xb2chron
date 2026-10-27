#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfEvent::~GfEvent() {}

void GfEvent::build(const GfSetupParam& param) {
#line 40
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfEvent;
}

void GfEvent::destroy() {
    GfEvent* event = get();
    event->m_initialized = false;
    delete event;
}

// addEventCallback and removeEventCallback are not written yet (see the worker notes)

void GfEvent::callChangeScenarioFlag(unsigned int flag, unsigned int prevFlag) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeScenarioFlag(flag, prevFlag);
    }
}

void GfEvent::fn_7100326D4C(unsigned int value) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FAB8(value);
    }
}

void GfEvent::callSalvageStateChange(unsigned int state) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevSalvageStateChange(state);
    }
}

void GfEvent::callBattleStart() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevBattleStart();
    }
}

void GfEvent::callBattleEnd() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevBattleEnd();
    }
}

void GfEvent::callGameMapModel(GF_OBJ_HANDLE*handle, bool flag) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevGameMapModel(handle, flag);
    }
}

void GfEvent::callTargetAccess(GF_OBJ_HANDLE*handle) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevAccessTarget(handle);
    }
}

void GfEvent::callTargetChange(GF_OBJ_HANDLE*handle) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeTarget(handle);
    }
}

void GfEvent::callCameraControl(int type) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevCameraControl(type);
    }
}

void GfEvent::callEventPlay(GEV gev, unsigned int id) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPlayEvent(gev, id);
    }
}

void GfEvent::callBladeChange(GF_OBJ_HANDLE*handle, int value1, int value2) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeBlade(handle, value1, value2);
    }
}

void GfEvent::callPartyChange() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeParty();
    }
}

void GfEvent::fn_71003274A8() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA20();
    }
}

void GfEvent::callGameObjEnter(GF_OBJ_HANDLE*handle) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevGameObjEnter(handle);
    }
}

void GfEvent::callGameObjLeave(GF_OBJ_HANDLE*handle) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevGameObjLeave(handle);
    }
}

void GfEvent::callAchievmentRelease(const GfAchievementRelease& release) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevReleaseAchievment(release);
    }
}

void GfEvent::callDriverActivate(unsigned int value, ActivateType type1, ActivateType type2) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevDriverActivate(value, type1, type2);
    }
}

void GfEvent::callBladeActivate(unsigned int blade, ActivateType from, ActivateType to) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevBladeActivate(blade, from, to);
    }
}

void GfEvent::callBladeUnselect(unsigned int blade, bool unselect) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevBladeUnselect(blade, unselect);
    }
}

void GfEvent::callBladeEnable(unsigned int value) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevBladeEnable(value);
    }
}

void GfEvent::callDriverLevel(unsigned int value0, unsigned int value1, unsigned int value2) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevDriverLevel(value0, value1, value2);
    }
}

void GfEvent::callExecState(EXEC_STATE state) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevExecState(state);
    }
}

void GfEvent::callMercenariesTeam(unsigned int value) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevMercenariesTeam(value);
    }
}

void GfEvent::callMercenariesMissionFlag(unsigned int mission, unsigned int flag, unsigned int old) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevMercenariesMissionFlag(mission, flag, old);
    }
}

void GfEvent::callItemAdd(unsigned int item, int count) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevItemAdd(item, count);
    }
}

void GfEvent::fn_7100327DC4(unsigned int value0, unsigned int value1) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA60(value0, value1);
    }
}

void GfEvent::fn_7100327E78(unsigned int value0, unsigned int value1) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA64(value0, value1);
    }
}

void GfEvent::callPartyMemberOK(bool ok) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPartyMemberOK(ok);
    }
}

void GfEvent::callPartyIDMemberOK(bool ok, unsigned int partyId) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPartyIDMemberOK(ok, partyId);
    }
}

void GfEvent::callChangeLeader(GF_OBJ_HANDLE*handle) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeLeader(handle);
    }
}

void GfEvent::callPartyDriver(GF_OBJ_HANDLE*handle, unsigned int value, bool flag) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPartyDriver(handle, value, flag);
    }
}

void GfEvent::callGameState(GF_STATE prev, GF_STATE next) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevGameState(prev, next);
    }
}

void GfEvent::callPartyReturnFieldState(unsigned int value) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPartyReturnFieldState(value);
    }
}

void GfEvent::callLoadGameTime(float time) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevLoadGameTime(time);
    }
}

void GfEvent::callPlayerControl(GEV gev) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPlayerControl(gev);
    }
}

void GfEvent::callPartyMover(GF_OBJ_HANDLE*handle, bool flag) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevPartyMover(handle, flag);
    }
}

void GfEvent::fn_7100328568() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA18();
    }
}

void GfEvent::fn_7100328604(unsigned int value) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA14(value);
    }
}

void GfEvent::fn_71003286B0(unsigned int hana, bool extend, unsigned int slot) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA68(hana, extend, slot);
    }
}

void GfEvent::fn_7100328774() {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->fn_710000FA1C();
    }
}

void GfEvent::callExecBuy(unsigned int value0, unsigned int value1, unsigned int value2) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevExecBuy(value0, value1, value2);
    }
}

void GfEvent::callGetArts(unsigned int value0, unsigned int value1, bool flag) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevGetArts(value0, value1, flag);
    }
}

void GfEvent::callHikariCurrent(bool hikari) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevSelectHikari(hikari);
    }
}

void GfEvent::callSwapFormation(unsigned int index0, unsigned int index1) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevSwapFormation(index0, index1);
    }
}

void GfEvent::callChangeTimeRange(unsigned int range) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeTimeRange(range);
    }
}

void GfEvent::callChangeWeather(unsigned int value0, unsigned int value1) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevChangeWeather(value0, value1);
    }
}

void GfEvent::callDebugChangeIdea(unsigned int value0, unsigned int value1, unsigned int value2, unsigned int value3) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevDebugChangeIdea(value0, value1, value2, value3);
    }
}

}  // namespace gf
