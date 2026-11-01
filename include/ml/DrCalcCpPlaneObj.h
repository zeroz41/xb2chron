#ifndef ML_DRCALCCPPLANEOBJ_H
#define ML_DRCALCCPPLANEOBJ_H

#include "classes/ml/DrMan.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "mtl/MemManager.h"

namespace mm { class Vec3; }

namespace ml {
class DrCalcViewWork;
// a clip plane object of DrCalcClipMan's lists, linked through its Node base (field names are not the original's)
class DrCalcCpPlaneObj : public DrResChankList<DrCalcCpPlaneObj>::Node {
public:
    // DrCalcClipMan::createCpPlaneObj's (inline: the symbols have no copy)
    // takes the clip plane resource (offsets of its two data blocks, the plane count)
    DrCalcCpPlaneObj(const void* resource) : m_pPlaneWork(), m_planeNum(), m_relFlag() {
        const unsigned char* pRes = static_cast<const unsigned char*>(resource);
        const unsigned int* pWords = static_cast<const unsigned int*>(resource);
        m_planeIdx = pWords[2];
        m_pData0 = pRes + pWords[0];
        m_pData1 = pRes + pWords[1];
        m_pPlaneWork = mtl::MemManager::allocate(DrMan::get()->m_allocHandle, m_planeIdx * 0x20, 0x10, false, "no name", 0);
    }
    // DrCalcClipMan::release's delete frees the plane work first (inline: the symbols have no copy)
    ~DrCalcCpPlaneObj() {
        if (m_pPlaneWork != nullptr) {
            mtl::MemManager::deallocate(m_pPlaneWork, 0, false);
        }
    }
    bool testClip(const mm::Vec3& pos, float radius);
    // DrCalcClipMan::update's, for each object not released
    void update(DrCalcViewWork* viewWork);
    // marked released in the frame stocked (DrMan::s_nDblStockIdx), its plane index reset
    void release();

    const unsigned char* m_pData0;  // 0x10: createCpPlaneObj points it at the resource + its word 0
    const unsigned char* m_pData1;  // 0x18: the resource + its word 4
    unsigned char pad_20[0x10];
    void* m_pPlaneWork;             // 0x30: createCpPlaneObj allocates 0x20 bytes per m_planeIdx; the destructor frees it
    int m_planeNum;             // 0x38: update counts the planes into it
    int m_planeIdx;             // 0x3C: an index update reads; release zeroes it
    unsigned int m_relFlag;     // 0x40: release() sets 1 << DrMan::s_nDblStockIdx
    unsigned char pad_44[0xC];  // createCpPlaneObj news 0x50 bytes
};
}  // namespace ml

#endif
