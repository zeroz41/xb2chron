#ifndef ML_SCNOBJACCSEAMETCPOS_H
#define ML_SCNOBJACCSEAMETCPOS_H

#include "ml/ScnObjAccPartsEtcPos.h"

namespace ml { class ScnObjModel; }

namespace ml {
// access to a seam model's effect positions (DrMdoCtlSeam's)
class ScnObjAccSeamEtcPos {
public:
    explicit ScnObjAccSeamEtcPos(ScnObjModel* model);
    unsigned int getObjMax() const;
    ScnObjAccPartsEtcPos getObj(unsigned int index);

    DrMdoCtlSeam::EtcPosList* m_list;  // null for other models; the name is not the original's
};
}  // namespace ml

#endif
