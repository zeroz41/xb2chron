#ifndef CLASSES_GF_GFPLAYCOMSTARTCHALLENGEBATTLE_H
#define CLASSES_GF_GFPLAYCOMSTARTCHALLENGEBATTLE_H

#include "classes/gf/GfPlayCom.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/MsgUnk_1000034.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58B48: GfPlayCom's slots, then gevMapjump (slot 7: the override of IGfEvent's slot 42); the
// PtrSingleton<GfPlayComStartChallengeBattle> table at +0x60, the IGfEvent one at +0x80 (destructor implicit)
class GfPlayComStartChallengeBattle : public GfPlayCom,
                                      public ::mm::mtl::PtrSingleton<GfPlayComStartChallengeBattle>,
                                      public ::gf::IGfEvent {
public:
    explicit GfPlayComStartChallengeBattle(const MsgUnk_1000034::Param& param)
        : GfPlayCom(51, false), m_param(param), m_mapjumped(false) {}
    static GfPlayComStartChallengeBattle* create(const MsgUnk_1000034::Param& param);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComStartChallengeBattle";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    virtual void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);  // slot 7 (IGfEvent slot 42)
    static mm::mtl::RTTI m_rtti;

    MsgUnk_1000034::Param m_param;  // what start sends the arena manager (message type 13); the name is not the original's
    bool m_mapjumped;  // gevMapjump sets it on GEV 2; update returns it (the name is not the original's)
};
}  // namespace gf

#endif
