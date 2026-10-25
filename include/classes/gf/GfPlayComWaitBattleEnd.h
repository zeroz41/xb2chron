#ifndef CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H
#define CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B584C8; slot 1 is GfPlayCom's destructor (this one's is implicit)
class GfPlayComWaitBattleEnd : public GfPlayCom {
public:
    explicit GfPlayComWaitBattleEnd(unsigned int eventId) : GfPlayCom(6, true), pad_10(false), m_eventId(eventId) {}
    static GfPlayComWaitBattleEnd* create(unsigned int eventId);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComWaitBattleEnd";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many are running (GfPlayFactory's blade resets request the change directly while one is)
    static int s_activate;

    bool pad_10;
    float m_time;  // seconds update has waited for the event (gives up past 15); the name is not the original's
    // the event to start after the battle (GfDataEvent::getEventType's argument); the name is not the original's
    unsigned int m_eventId;
};
}  // namespace gf

#endif
