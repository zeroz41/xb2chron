#ifndef ML_DRIRRVOLMAN_H
#define ML_DRIRRVOLMAN_H

#include "classes/ml/irrvol/MemHandlebaseAllocator.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace ml {
class DrMan;
namespace irrvol {
struct SGlobalInfo;
class DrIrrVolCascade;
}  // namespace irrvol

// The irradiance volume manager. Only what its destructor uses is declared; the field names are not the original's.
class DrIrrVolMan {
public:
    DrIrrVolMan(DrMan* drMan);
    ~DrIrrVolMan();
    // deletes the cascades and forgets the settings (1.0.0 has it out of line; 3.0.1's destructor inlines it)
    void release();

    DrMan* m_drMan;  // 0x0, the constructor's
    const irrvol::SGlobalInfo* m_globalInfo;  // 0x8
    mm::mtl::FixStr<128> m_name;  // 0x10, 1.0.0 passes its text to each cascade's constructor
    irrvol::DrIrrVolCascade** m_cascades;  // 0x98, m_globalInfo->m_cascadeNum of them
    irrvol::MemHandlebaseAllocator m_allocator;  // 0xA0, on MlMem::getProductMem()
    float m_time;  // 0xB0, the constructor clears it
    int m_frameParity;  // 0xB4, toggled every frame; 1.0.0 update passes it to the cascades
    unsigned char pad_b8[0xD8];
    // current/previous pairs: each frame's end copies the first of each into the second
    mm::Vec3 m_pos;  // 0x190
    mm::Vec3 m_prevPos;  // 0x1A0
    float m_rate;  // 0x1B0
    float m_prevRate;  // 0x1B4
    int m_state;  // 0x1B8
    int m_prevState;  // 0x1BC
    unsigned int m_cascadeIdx;  // 0x1C0
    unsigned int m_prevCascadeIdx;  // 0x1C4, 1.0.0 update compares it with m_globalInfo->m_cascadeNum
    bool m_enable;  // 0x1C8, the constructor sets it
    bool m_debugDraw;  // 0x1C9, 1.0.0 update draws debug info when set
};
}  // namespace ml

#endif
