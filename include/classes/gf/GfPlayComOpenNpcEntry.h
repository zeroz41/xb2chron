#ifndef CLASSES_GF_GFPLAYCOMOPENNPCENTRY_H
#define CLASSES_GF_GFPLAYCOMOPENNPCENTRY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B585E8 (secondary table at +0x58: the PtrSingleton base at 0x10, table 0x7100B58E08). The class name is
// its RTTI's and getFuncName's string. The destructor and getFuncName are inline (their bodies sit in the unit's tail
// with the table's thunks); start is the key function.
class GfPlayComOpenNpcEntry : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComOpenNpcEntry> {
public:
    explicit GfPlayComOpenNpcEntry(const mm::mtl::FixedVector<unsigned short, 256>& entries)
        : GfPlayCom(0x31, false), m_entries(entries), m_context(GfMenuCallContext::create()) {}
    // 2.0.0's symbols name it. What it does: copies the given FixedVector of 256 two-byte entries into the command at
    // 0x18 (count at 0x218) and stores GfMenuCallContext::create() at 0x220. Its one caller is
    // GfSequentialPlay::addOpenNpcEntry. The element type (2 bytes) is inferred, not the original's.
    static GfPlayComOpenNpcEntry* create(const mm::mtl::FixedVector<unsigned short, 256>& entries);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComOpenNpcEntry() {}  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComOpenNpcEntry";
        return func;
    }
    virtual void start();  // slot 4: opens GfMenuObjNpcTelop (NPC telop) with up to three of m_entries
    virtual void end();  // slot 5: releases m_context
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6: m_context->isTerm()
    static mm::mtl::RTTI m_rtti;

    // the names below are not the original's
    mm::mtl::FixedVector<unsigned short, 256> m_entries;  // 0x18: the ids GfMenuObjNpcTelop shows (count at 0x218)
    GfMenuCallContext* m_context;                          // 0x220: the create's GfMenuCallContext::create()
};
}  // namespace gf

#endif
