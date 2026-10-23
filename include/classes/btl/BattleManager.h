#ifndef CLASSES_BTL_BATTLEMANAGER_H
#define CLASSES_BTL_BATTLEMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3A5A0; the base at 0x8 is gf::IGfEvent (its table at +0x48 holds IGfEvent's 63 slots, with
// gevMapjump, gevBattleStart and gevBattleEnd overridden by thunks; Initialize registers this with
// GfEvent::addEventCallback)
class BattleManager : public ::mm::mtl::PtrSingleton< ::btl::BattleManager>, public gf::IGfEvent {
public:
    BattleManager() : pad_10(0), m_initialized(false), pad_15(true), pad_16(0) {}
    static void build(const gf::GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void Initialize(const gf::GfSetupParam& param);
    void Finalize();
    void Update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    virtual ~BattleManager();  // slot 0
    virtual void gevBattleStart();  // slot 2
    virtual void gevBattleEnd();  // slot 3
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 4
    static bool isInitialized();
    static void NotifyQuestTask(unsigned int id);
    void QuestTaskProc(unsigned int id);
    unsigned int pad_10;
    bool m_initialized;
    bool pad_15;
    unsigned short pad_16;
};
}  // namespace btl

#endif
