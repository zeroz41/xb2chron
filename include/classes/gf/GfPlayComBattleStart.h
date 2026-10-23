#ifndef CLASSES_GF_GFPLAYCOMBATTLESTART_H
#define CLASSES_GF_GFPLAYCOMBATTLESTART_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfGameScene.h"
#include "gf/GfGameUtil.h"
#include "fw/UpdateInfo.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B58A08; GfSequentialPlay::addBattleStart makes it
class GfPlayComBattleStart : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComBattleStart> {
public:
    explicit GfPlayComBattleStart(bool flag) : GfPlayCom(37, false), m_flag(flag), m_time(0.0f), m_state(0) {}
    static GfPlayComBattleStart* create(bool flag);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComBattleStart";
        return func;
    }
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    bool m_flag;  // GfSequentialPlay::addBattleStart's name
    float m_time;  // the name is not the original's
    int m_state;  // the name is not the original's
};
}  // namespace gf

#endif
