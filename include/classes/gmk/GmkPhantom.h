#ifndef CLASSES_GMK_GMKPHANTOM_H
#define CLASSES_GMK_GMKPHANTOM_H

#include "mm/Vec3.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkPhantomManager.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiUserData.h"
namespace gmk { class AGmkBase; class IGmkPhantomEventListener; }
namespace gmk {
// table 0x7100B6BF68
// its node (a non-polymorphic base, so at 0x8 after the table) links it into GmkPhantomManager's list
// 16-aligned (size 0x90): every holder is alignas(16) with its phantom at a 16-aligned offset and 8 free bytes after
// it, and GmkElevator's destructor destroys four of them 0x90 apart as one array (the 16-aligned field is not typed yet)
// a fw::ColiUserData (m_rtti's base; create hands the collision object `this` as its user data), the table's base at
// 0; declared after the node so its holders' copies store no ColiUserData table (the original has none)
class alignas(16) GmkPhantom : public mm::mtl::IntrusiveListNodeBase, public fw::ColiUserData {
public:
    // create's parameter: GmkPhantomSimple::CreateInfo's 0x40-byte layout plus the listener and a flag (create(gmk,
    // listener, bool) builds one on its stack); the field names are not the original's
    class CreateInfo {
    public:
        // the constructor stores the listener and the flag before the sizes (create(gmk, listener, bool), and the
        // phantom's constructor clears 0x60, 0x68, 0x58, 0x50 in that order)
        CreateInfo()
            : m_type(0), m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f), m_listener(nullptr), m_flag(false) {
            for (int i = 0; i < 3; i++) {
                m_size[i] = 0.0f;
            }
        }
        unsigned int m_type;                    // 1, 2 or 3: the phantom's shape
        mm::Vec3 m_pos;                         // 0x10
        mm::Vec3 m_rot;                         // 0x20: create's rotation angles (sin/cos of each)
        float m_size[3];                        // 0x30: the shape's sizes
        IGmkPhantomEventListener* m_listener;   // 0x40: create(gmk, listener, bool)'s listener
        bool m_flag;                            // 0x48: create(gmk, listener, bool)'s bool
    };
    // 1.0.0 has it out of line (GmkPhantom(CreateInfo const*): these stores, create when given one, then the link);
    // 3.0.1 inlines it into the gimmicks that embed one (construct_n<GmkSe>)
    GmkPhantom() {
        pad_80 = 0;
        m_coliObject = nullptr;
        m_name = nullptr;
        GmkPhantomManager::get()->m_phantoms.push_back(*this);
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GmkPhantom();  // slot 1
    void create(const CreateInfo& info);
    void create(const AGmkBase& gmk, IGmkPhantomEventListener* listener, bool);
    // GmkPhantomManager::update hands it the three party positions' phantom test results
    void update(const mm::mtl::FixedArray<fw::TColiCheckResult<256>, 3>& results);
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
        m_name = nullptr;
    }
    static mm::mtl::RTTI m_rtti;
    // 0x20: create keeps a copy (16-aligned; the name is not the original's). Its implicit copy explains the holders'
    // copies (copy_construct_n<gmk::GmkTrigger>, <gmk::GmkLandmark>, Vector<gmk::GmkAreaBgm>::expand): nothing at
    // 0x18, the type, the two Vec3s x, y and z each, then 0x50..0x69 as one run (the CreateInfo's tail padding is
    // not copied), then 0x70..0x84
    CreateInfo m_info;
    // 0x70: the gimmick's INFO name (create(gmk, listener, bool) takes LvlbInfo::m_name; dispose clears it; the name is
    // not the original's)
    const char* m_name;
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
