#ifndef CLASSES_GMK_GMKPHANTOMSIMPLE_H
#define CLASSES_GMK_GMKPHANTOMSIMPLE_H

#include "classes/fw/ColiObject.h"
#include "mm/Vec3.h"

namespace gmk {
class AGmkBase;
// table 0x7100B6BF48
// layout from create (0x710057D160: keeps a copy of its CreateInfo at 0x10 and the phantom at 0x50) and from
// Vector<GmkDmgPhantom>'s element stores and copies (it is GmkDmgPhantom's member at 0x50)
class GmkPhantomSimple {
public:
    // create's parameter (the same 0x40-byte layout as GmkCollision::CreateInfo); the field names are not the
    // original's
    class CreateInfo {
    public:
        // the sizes in a loop: ~GmkPhantomSimple's reset stores rot.x, rot.y/z, size[2], size[0/1] so
        CreateInfo() : m_type(0), m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f) {
            for (int i = 0; i < 3; i++) {
                m_size[i] = 0.0f;
            }
        }
        // returns nothing: its code sets no result (create(gmk, listener, bool) has the same body)
        void validateByAGmkBase(const AGmkBase& gmk);
        unsigned int m_type;  // 1, 2 or 3: the phantom's shape
        mm::Vec3 m_pos;       // 0x10
        mm::Vec3 m_rot;       // 0x20: create's rotation angles (sin/cos of each)
        float m_size[3];      // 0x30: the shape's sizes
    };
    GmkPhantomSimple() : m_coliObject(nullptr) {}
    virtual ~GmkPhantomSimple();  // slot 0
    // 1.0.0 has it out of line (gmk::GmkPhantomSimple::dispose()); 3.0.1 inlines it (the destructor,
    // GmkDmgPhantom::dispose): the collision object released, the parameters reset
    void dispose() {
        if (m_coliObject != nullptr) {
            m_coliObject->setUserData(nullptr);
            // the original reads the pointer once for these two (an inlined helper's this)
            fw::ColiObject* coli = m_coliObject;
            coli->m_eventMask = 0;
            coli->m_listener = nullptr;
        }
        if (m_coliObject != nullptr) {
            m_coliObject->release();
            m_coliObject = nullptr;
        }
        m_info = CreateInfo();
    }
    void create(const CreateInfo& info);
    // 0x8: padding (CreateInfo is 16-aligned; neither stored nor copied)
    CreateInfo m_info;               // 0x10: create keeps a copy (the name is not the original's)
    fw::ColiObject* m_coliObject;    // 0x50: create's createColiPhantom result (the name is not the original's)
};
}  // namespace gmk

#endif
