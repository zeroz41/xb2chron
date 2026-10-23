#ifndef CLASSES_GF_GFPLAYCOM_H
#define CLASSES_GF_GFPLAYCOM_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58DC0; a command of GfSequentialPlay's command list. Every slot is inline: the table has no key
// function, so each command's constructor emits it.
class GfPlayCom {
public:
    // the third field is the command's kind (1 GfPlayComPause, 2 GfPlayComState); the name is not the original's
    GfPlayCom(int kind, bool flag) : pad_08(true), pad_09(flag), m_kind(kind) {}
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayCom() {}  // slot 1
    virtual const char* getFuncName() const = 0;  // slot 3
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag) { return true; }  // slot 6
    static mm::mtl::RTTI m_rtti;

    bool pad_08;
    bool pad_09;
    int m_kind;
};
}  // namespace gf

#endif
