#ifndef CLASSES_GMK_TUNK_B6D528_H
#define CLASSES_GMK_TUNK_B6D528_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3B (table 0x7100B6D528), new in 3.0.1. Element (0x100 bytes) of the list
// TGmkList<TUnk_B6D528, ..., 'BTCL', ...> (table 0x7100B6F098) at 0x230 of GmkEnemyList's member at 0x470.
class TUnk_B6D528Gob;

class alignas(16) TUnk_B6D528 : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~TUnk_B6D528() { dispose(); }  // slot 0 (fn_71005BC0BC, dispose inlined; D0 fn_71005BC1C0)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (fn_71005BC2B4)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (fn_71005BC2BC)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B6F44, 0x234)
    virtual void dispose();  // slot 5 (fn_71005B726C, 0xD8)
    virtual void update(float);  // slot 6 (fn_71005B7374, 0x70)
    virtual void debugDraw() const;  // slot 7 (fn_71005B73E4, empty)
    class BdatInfo {};
    static const gmk::GmkType TYPE = gmk::GmkType(0x3b);
    unsigned char pad_48[0x8];
    GmkPhantom m_phantom;  // 0x50 (the name is not the original's)
    void (TUnk_B6D528::*m_seq)(float dt);  // 0xE0: create sets fn_71005B7178, dispose clears it (the name is not the original's)
    unsigned char pad_f0[0x10];  // 0xF8: create clears the byte; 0xF9: update skips m_seq when set
};
}  // namespace gmk

#endif
