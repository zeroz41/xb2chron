#ifndef CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H
#define CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B584C8
class GfPlayComWaitBattleEnd : public GfPlayCom {
public:
    static GfPlayComWaitBattleEnd* create(unsigned int wait);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComWaitBattleEnd();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many are running (GfPlayFactory's blade resets request the change directly while one is)
    static int s_activate;
};
}  // namespace gf

#endif
