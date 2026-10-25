#ifndef CLASSES_ML_DRMDOCTLSEAM_H
#define CLASSES_ML_DRMDOCTLSEAM_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"

namespace ml {
// table 0x7100B7BA10
class DrMdoCtlSeam : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlSeam();  // slot 0

    // a placed effect position (0x10; ScnObjAccPartsEtcPos reads it). Type and field names are not the original's.
    struct EtcPos {
        // the record (offsets from the record itself)
        struct Data {
            unsigned int objNameOfs;  // 0x0
            unsigned int effNameOfs;  // 0x4
            float range;              // 0x8
            unsigned int matrixMax;   // 0xC
            unsigned int matrixOfs;   // 0x10: matrixMax Mat44s
            float nearClip[2];        // 0x14
            float farClip[2];         // 0x1C
            unsigned int dispIdxOfs;  // 0x24: a u16 DrMan display index per matrix (0 = always shown)
        };
        const Data* m_data;  // 0x0
        bool m_dispOn;       // 0x8: shown whatever the display bits say
    };
    // the seam's effect positions (ScnObjAccSeamEtcPos reads it; names are not the original's)
    struct EtcPosList {
        EtcPos* m_entries;   // 0x0
        unsigned int m_max;  // 0x8
    };

    // the names are not the original's
    unsigned char pad_182[0x516];
    DrResMdoInstAnmObj m_instAnm;  // 0x698: releaseSeam releases it; ScnObjAccSeamPos reads it (m_mdlType 3)
    EtcPosList m_etcPos;           // 0x6C8 (m_mdlType 3)
};
}  // namespace ml

#endif
