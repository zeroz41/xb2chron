#ifndef ML_SCNOBJACCETCPARAMS_H
#define ML_SCNOBJACCETCPARAMS_H

namespace ml { class ScnObjModel; }
#include "classes/ml/DrMdlObj.h"
namespace ml {
class ScnObjAccEtcParams {
public:
    explicit ScnObjAccEtcParams(ScnObjModel* model);
    unsigned int getMax() const;
    const char* getName(unsigned int index) const;
    int getIndex(const char* name) const;
    void setParams(unsigned int index, float value);
    void setPreParams(unsigned int index, float value);
    void setInitParams(unsigned int index, float value);
    void setRimBloom(bool on);

    DrMdlObj::EtcParamsTable* m_table;  // the model's (null for a non-DrMdoCtlNom model; the name is not the original's)
};
}  // namespace ml

#endif
