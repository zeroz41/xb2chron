#ifndef CLASSES_GF_GFGAMEDEPOPMETERMANAGER_H
#define CLASSES_GF_GFGAMEDEPOPMETERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"
#include "gf/GfGameDepopMeter.h"

namespace gf { class GfGameDepopMeterManager; }

namespace gf {
// table 0x7100B56680; the depop meters, a few of them updated each frame (0x30 bytes, create's allocation). The
// field names are not the original's
class GfGameDepopMeterManager : public ::mm::mtl::PtrSingleton< ::gf::GfGameDepopMeterManager> {
public:
    explicit GfGameDepopMeterManager(unsigned int updateCount) : m_updateCount(updateCount), m_cursor(m_meters.end()) {}
    virtual ~GfGameDepopMeterManager();  // slot 0

    // replaces the instance with one updating `updateCount` meters a frame
    static void create(unsigned int updateCount);
    // deletes the instance
    static void dispose();
    // updates the next meters after the cursor, at most m_updateCount of them
    static void update(float deltaTime);

    unsigned int m_updateCount;  // create's
    mm::mtl::IntrusiveList<GfGameDepopMeter> m_meters;  // 0x10: GfGameDepopMeter::create links one
    mm::mtl::IntrusiveList<GfGameDepopMeter>::iterator m_cursor;  // 0x28: the meter update steps next
};
}  // namespace gf

#endif
