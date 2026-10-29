#ifndef CLASSES_GMK_TUNK_B6E340_H
#define CLASSES_GMK_TUNK_B6E340_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/TUnk_B6D6C8.h"
#include "mm/mtl/Vector.h"

namespace gmk {
// table 0x7100B6E340; base TGmkList<TUnk_B6D6C8, ...> (table 0x7100B6EFD8, magic 'SLDS'). Placeholder name: the
// list of kind 0x3F, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the destructors (fn_71005C41F0, fn_71005C4224), create (slot 9, fn_71005BA900), dispose
// (slot 10, fn_71005BABD8) and update (slot 11, fn_71005BAE34).
class TUnk_B6E340 : public ::gmk::TGmkList< ::gmk::TUnk_B6D6C8, ::gmk::TUnk_B6D6C8::BdatInfo, 1396984915u, 1u, ::gmk::TUnk_B6D6C8Gob> {
public:
    explicit TUnk_B6E340(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame), pad_2a8(nullptr), pad_2b0(nullptr), pad_2b8(0),
          m_effects(nullptr) {}
    // a class with no table, 0x30 bytes (TUnk_B6E340::create's `new`, cited from gmk_sealed_stone_impl.h): a vector of
    // 0x60-byte entries, each holding an fw::EffectManager handle at 0x40. The names are not the original's.
    class EffectList {
    public:
        struct Entry {
            unsigned char pad_0[0x40];
            unsigned int m_effectHandle;  // 0x40: fn_71005BAC78 kills it
            unsigned char pad_44[0x1c];
        };
        // the original's constructor stores only the vector (nothing at 0x0)
        EffectList() {}
        ~EffectList() { fn_71005BAC78(); }
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because TUnk_B6E340::dispose and this
        // destructor call it with the object. What it does: when the vector holds entries, kills each entry's effect
        // (fw::EffectManager::kill) and frees the vector (Vector::destroy, inline).
        void fn_71005BAC78();
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because TUnk_B6E340::create
        // (fn_71005BA900) tail-calls it with the object it has just allocated. What it does: fills the entries from the
        // field's effect pack (gf::GfFieldManager::getEffectPack, fw::EffectManager::search; asserts; calls
        // fn_71005BAC78 and fn_71005D8100).
        void fn_71005BAA98();
        void* pad_0;
        mm::mtl::Vector<Entry> m_entries;  // 0x8
    };
    virtual ~TUnk_B6E340();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const& info);  // slot 9 (fn_71005BA900)
    virtual void dispose();  // slot 10 (fn_71005BABD8)
    virtual void update(float dt);  // slot 11 (fn_71005BAE34)
    unsigned char pad_228[0x80];  // fields: size from createGmkLists' `new` (0x2d0)
    // Placeholder members (nothing names them): createGmkLists' inline constructor zeroes all four (8-, 8-, 4- and
    // 8-byte stores). Its dispose (fn_71005BABD8) frees m_effects and zeroes it, and zeroes pad_2a8, pad_2b0 and pad_2b8 again.
    void* pad_2a8;
    void* pad_2b0;
    int pad_2b8;
    // 0x2c0: create allocates it and fills it (fn_71005BAA98); dispose deletes it (the name is not the original's)
    EffectList* m_effects;
};
}  // namespace gmk

#endif
