#ifndef CLOUD_CLOUDCALCPARAMS_H
#define CLOUD_CLOUDCALCPARAMS_H

#include "mm/Col3.h"

namespace cloud {
// the cloud parameters CloudObjMan allocates (0x4F0); only what CloudMan reads is named, and the names are not the
// original's
class CloudCalcParams {
public:
    CloudCalcParams();

    unsigned char pad_0[0x194];
    float m_height;              // 0x194, CloudMan::setHeight/getHeight
    unsigned char pad_198[0x4];
    unsigned int m_cldNum;       // 0x19C, CloudMan::setCldNum (0 or 1)/getCldNum
    unsigned char pad_1A0[0x18];
    mm::Col3 m_planeCol[2];      // 0x1B8, CloudMan::getPlaneCol (0 picks the first)
    unsigned char pad_1D0[0x320];
};
}  // namespace cloud

#endif
