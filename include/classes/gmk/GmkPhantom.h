#ifndef CLASSES_GMK_GMKPHANTOM_H
#define CLASSES_GMK_GMKPHANTOM_H

#include "mm/Vec3.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkPhantomManager.h"
#include "classes/fw/ColiObject.h"
namespace gmk { class AGmkBase; class IGmkPhantomEventListener; }
namespace gmk {
// table 0x7100B6BF68
// its node (a non-polymorphic base, so at 0x8 after the table) links it into GmkPhantomManager's list
// 16-aligned (size 0x90): every holder is alignas(16) with its phantom at a 16-aligned offset and 8 free bytes after
// it, and GmkElevator's destructor destroys four of them 0x90 apart as one array (the 16-aligned field is not typed yet)
class alignas(16) GmkPhantom : public mm::mtl::IntrusiveListNodeBase {
public:
    // 1.0.0 has it out of line (GmkPhantom(CreateInfo const*): these stores, create when given one, then the link);
    // 3.0.1 inlines it into the gimmicks that embed one (construct_n<GmkSe>)
    GmkPhantom() {
        pad_60 = nullptr;
        pad_68 = false;
        pad_58 = 0;
        pad_50 = nullptr;
        pad_80 = 0;
        m_coliObject = nullptr;
        pad_70 = nullptr;
        GmkPhantomManager::get()->m_phantoms.push_back(*this);
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GmkPhantom();  // slot 1
    void create(const AGmkBase& gmk, IGmkPhantomEventListener* listener, bool);
    // 1.0.0 has it out of line (gmk::GmkPhantom::dispose(), 0x94 bytes); 3.0.1 inlines it (the destructor, the
    // gimmicks' disposeGmkPhantom and dispose): the collision object released, the flags at 0x80 cleared
    void dispose() {
        if (m_coliObject != nullptr) {
            m_coliObject->setUserData(nullptr);
            // the original reads the pointer once for these two (an inlined helper's this)
            fw::ColiObject* coli = m_coliObject;
            coli->m_eventMask = 0;
            coli->m_listener = nullptr;
        }
        pad_83 = false;
        if (m_coliObject != nullptr) {
            m_coliObject->release();
            m_coliObject = nullptr;
        }
        pad_70 = nullptr;
    }
    static mm::mtl::RTTI m_rtti;
    // fields: 1.0.0's constructor clears each (0x50..0x80 in its body, in this order) (meaning unknown; the names are not the original's)
    // 0x20: 16-aligned (the copy constructors of its holders, copy_construct_n<gmk::GmkTrigger>, copy nothing at 0x18)
    alignas(16) int pad_20 = 0;
    // 0x30, 0x40: copied x, y and z each, as a Vec3 copies
    mm::Vec3 pad_30 = mm::Vec3(0.0f, 0.0f, 0.0f);
    mm::Vec3 pad_40 = mm::Vec3(0.0f, 0.0f, 0.0f);
    void* pad_50;
    int pad_58;
    void* pad_60;
    bool pad_68;
    // 0x69: a member the copy constructor copies nothing of, yet that is not copied bit for bit: the holders' copies
    // (copy_construct_n<gmk::GmkLandmark>, Vector<gmk::GmkAreaBgm>::expand) copy 0x50..0x69 and 0x70..0x84 as two
    // runs (the type and both names are not the original's)
    struct NoCopy {
        NoCopy() {}
        NoCopy(const NoCopy&) {}
    } pad_69;
    void* pad_70;
    // the collision object it listens to, referenced while held (the name is not the original's)
    fw::ColiObject* m_coliObject;
    // 0x80: the constructor clears these four bytes with one word store; dispose clears 0x83
    union {
        int pad_80;
        struct {
            unsigned char pad_80_0[3];
            bool pad_83;
        };
    };
};
}  // namespace gmk

#endif
