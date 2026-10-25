#ifndef ML_SCNOBJACCSEAMPOS_H
#define ML_SCNOBJACCSEAMPOS_H

#include "ml/ScnObjAccPartsPos.h"

namespace ml { class ScnObjModel; }
namespace ml { class DrResMdoInstAnmObj; }

namespace ml {
// access to a model's instanced parts (DrMdoCtlPos's or DrMdoCtlSeam's)
class ScnObjAccSeamPos {
public:
    explicit ScnObjAccSeamPos(ScnObjModel* model);
    unsigned int getMax() const;
    ScnObjAccPartsPos getObj(unsigned int index);

    DrResMdoInstAnmObj* m_anm;  // null for other models; the name is not the original's
};
}  // namespace ml

#endif
