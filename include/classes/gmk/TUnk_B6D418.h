#ifndef CLASSES_GMK_TUNK_B6D418_H
#define CLASSES_GMK_TUNK_B6D418_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkPhantom.h"
#include "mm/mtl/FixedVector.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3A (table 0x7100B6D418), new in 3.0.1. Element (0x4A0 bytes) of the list
// TGmkList<TUnk_B6D418, ..., 'ENEW', ...> (table 0x7100B6F140) that GmkEnemyList's member at 0x470 derives from.
// Inferred: the enemy wave gimmick gf_field_locator finds by "EnemyWaveID" (AGmkBase.h's fn_71005B38EC notes); the
// name is not proven, so it stays TUnk_.
class TUnk_B6D418Gob;

class alignas(16) TUnk_B6D418 : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~TUnk_B6D418() { dispose(); }  // slot 0 (fn_71005BC2DC; D0 fn_71005BC3D0)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (fn_71005BC3F4)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (fn_71005BC3FC)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B3A50, 0x314)
    virtual void dispose();  // slot 5 (fn_71005B3FB0, 0x128; the destructor calls it out of line)
    virtual void update(float);  // slot 6 (fn_71005B49A4, 0x254)
    virtual void debugDraw() const;  // slot 7 (fn_71005B4DF0, empty)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (fn_71005B514C, 0x188)
    class BdatInfo {};
    static const gmk::GmkType TYPE = gmk::GmkType(0x3a);
    // one entry of the array fn_71005B38EC walks (0x18 bytes; meaning unknown)
    struct Entry {
        unsigned char pad_0[0x18];
    };
    gf::GF_OBJ_HANDLE* m_gob;  // 0x48: dispose destroys it unless it is -1 (the name is not the original's)
    unsigned char pad_50[0x10];
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    GmkAcc m_acc;  // 0xF0 (the name is not the original's)
    void (TUnk_B6D418::*m_seq)(float dt);  // 0x130: dispose clears it (the name is not the original's)
    unsigned char pad_140;
    // 0x141..0x145: flags the battle challenge (TUnk_B6D528) reads and sets (the names are not the original's)
    bool m_isCleared;     // 0x141: fn_71005B77B8 counts the waves up to the last one set
    bool m_isChallenge;   // 0x142: TUnk_B6D528::create sets it
    bool m_isStarted;     // 0x143: TUnk_B6D528::fn_71005B76B4 sets it
    unsigned char pad_144;
    bool m_isPaused;      // 0x145: TUnk_B6D528::fn_71005B75AC sets it
    unsigned char pad_146[0x2];
    mm::mtl::FixedVector<Entry, 32> m_entries;  // 0x148, size at 0x448 (the name is not the original's)
    unsigned char pad_450[0x8];
    GmkAcc m_secondAcc;  // 0x458 (the name is not the original's)
};
}  // namespace gmk

#endif
