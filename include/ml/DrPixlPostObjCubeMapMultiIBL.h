#ifndef ML_DRPIXLPOSTOBJCUBEMAPMULTIIBL_H
#define ML_DRPIXLPOSTOBJCUBEMAPMULTIIBL_H

#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibVtxStmOut.h"
#include "grlib/CGLibVtxVertex.h"
#include "mm/mtl/FixedQueue.h"
#include "ml/DrPixlPostObj.h"
#include "ml/DrRequetIBL.h"

namespace ml { class DrPixlRenderCubeMapMipMap; class DrShdCubeCapFilter; }

namespace ml {

// the multi-IBL cube map post object (DrPixlPostMan::m_cubeMapMultiIBL). The field names are not the original's.
class DrPixlPostObjCubeMapMultiIBL : public DrPixlPostObj {
public:
    DrPixlPostObjCubeMapMultiIBL(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjCubeMapMultiIBL();
    void render();
    unsigned int getPremMipCount() const;
    // queues a copy of request (its state byte becomes 1); false when multi-IBL is off, the ring is full, the same
    // id is already being processed (state 1) or queued four times
    bool requestIBL(DrRequetIBL& request);
    // marks every queued request whose m_id is id as cancelled (its state byte becomes 3)
    void cancelIBL(unsigned long id);

    // 0x18: requestIBL copies requests in; its count (0x5B8) and first index (0x5C0) end at 0x5C8
    mm::mtl::FixedQueue<DrRequetIBL, 30> m_requests;
    DrPixlRenderCubeMapMipMap* m_cubeMap[2];  // 0x5C8
    unsigned int m_premMipCount;  // 0x5D8, DrCalcViewWork::unistatic_specularIBL reads it through getPremMipCount
    unsigned char pad_5dc[0x74];
    grlib::CGLibVtxVertex m_vertex;  // 0x650
    grlib::CGLibVtxStmOut m_stmOut[2];  // 0x678
    grlib::CGLibVtxFetch m_fetch;  // 0x6C8
    unsigned char pad_6d8[0x10];
    DrShdCubeCapFilter* m_capFilter;  // 0x6E8
};

}  // namespace ml

#endif
