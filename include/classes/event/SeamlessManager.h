#ifndef CLASSES_EVENT_SEAMLESSMANAGER_H
#define CLASSES_EVENT_SEAMLESSMANAGER_H

#include "classes/event/PosAxis.h"
#include "classes/event/IManager.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D470; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SeamlessManager>
class SeamlessManager : public IManager, public mm::mtl::Singleton<SeamlessManager> {
public:
    virtual ~SeamlessManager();  // slot 0
    SeamlessManager();  // out of line (Singleton<SeamlessManager>::getPtr calls it)
    void addFirstSeamPoint(const char* name, const PosAxis& pos);
    void addSeamPoint(float frame, const PosAxis& pos);  // the parameter name is not the original's
    // 1.0.0 has these out of line under these names
    void update();
    void render();
    void readFirstSeamPoint(const char* name);
    void readNextSeamPoint(const char* name);
    // 1.0.0 has it out of line (event::SeamlessManager::clear); 3.0.1 keeps only OnEventProc's inlined copy
    inline void clear();
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // fields the constructor initializes; what they hold is not known yet
    // 1.0.0's FirstKey (its constructor is symbol-named): a FixStr<16> name, a PosAxis, a Vec3
    class FirstKey {
    public:
        FirstKey(const char* name, const PosAxis& pos, const mm::Vec3& value);  // the parameter names are not the original's
        mm::mtl::FixStr<16> m_name;  // 0x0; the field names are not the original's
        PosAxis m_pos;  // 0x20
        mm::Vec3 m_value;  // 0x40
    };
    // addSeamPoint's element: the frame and the position DataManager::axis2pos gives (the names are not the original's)
    struct Key {
        float m_frame;  // 0x0
        mm::Vec3 m_pos;  // 0x10
    };

    // bit 0: a first seam point is read (m_firstPos), bit 1: m_pos follows m_keys, bit 2: the renderer's seam map
    // add-position mode is on; clear() zeroes it (the name is not the original's)
    unsigned int m_flags;  // 0x10
    unsigned int m_dispFlags;  // 0x14 bit 0: 1.0.0's setDisp(bool), render needs it (the name is not the original's)
    unsigned char pad_18[0x8];
    // addFirstSeamPoint's entries; the name is not the original's
    mm::mtl::FixedVector<FirstKey, 16> m_firstKeys;  // 0x20 (count at 0x520)
    // (the 16-aligned vector ends at 0x530)
    // the position read*SeamPoint passes to the renderer's seam map (the name is not the original's)
    mm::Vec3 m_firstPos;  // 0x530
    // addSeamPoint's entries, kept in frame order; the name is not the original's
    mm::mtl::FixedVector<Key, 256> m_keys;  // 0x540 (count at 0x2540)
    // (the 16-aligned vector ends at 0x2550)
    // the first key's position update passes to the renderer's seam map (the name is not the original's)
    mm::Vec3 m_pos;  // 0x2550
};
}  // namespace event

#endif
