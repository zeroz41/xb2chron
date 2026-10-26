#ifndef CLASSES_GF_GFPLAYCOMOPENNPCENTRY_H
#define CLASSES_GF_GFPLAYCOMOPENNPCENTRY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B585E8 (secondary table at +0x58: the PtrSingleton base at 0x10, table 0x7100B58E08)
class GfPlayComOpenNpcEntry : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComOpenNpcEntry> {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because it allocates this
    // class (0x228 bytes, kind 0x31, both tables of 0x7100B585E8 stored, PtrSingleton's get()==0 assert). What it
    // does: copies the given FixedVector of 256 two-byte entries into the command at 0x18 (count at 0x218) and
    // stores GfMenuCallContext::create() at 0x220. Its one caller is GfSequentialPlay::fn_7100322930. The element
    // type (2 bytes) is inferred, not the original's.
    static GfPlayComOpenNpcEntry* fn_7100319F34(const mm::mtl::FixedVector<unsigned short, 256>& entries);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComOpenNpcEntry();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
