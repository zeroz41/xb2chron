#ifndef ML_DRPIXLPOSTOBJCUBEMAPMULTIIBL_H
#define ML_DRPIXLPOSTOBJCUBEMAPMULTIIBL_H

#include "mm/mtl/FixedQueue.h"
#include "ml/DrPixlPostObj.h"
#include "ml/DrRequetIBL.h"

namespace ml {

// the multi-IBL cube map post object (DrPixlPostMan::m_cubeMapMultiIBL). The field names are not the original's.
class DrPixlPostObjCubeMapMultiIBL : public DrPixlPostObj {
public:
    void render();
    unsigned int getPremMipCount() const;
    // marks every queued request whose m_id is id as cancelled (its state byte becomes 3)
    void cancelIBL(unsigned long id);

    // 0x18: requestIBL copies requests in; its count (0x5B8) and first index (0x5C0) end at 0x5C8
    mm::mtl::FixedQueue<DrRequetIBL, 30> m_requests;
    unsigned char pad_5C8[0x10];
    unsigned int m_premMipCount;  // 0x5D8, DrCalcViewWork::unistatic_specularIBL reads it through getPremMipCount
};

}  // namespace ml

#endif
