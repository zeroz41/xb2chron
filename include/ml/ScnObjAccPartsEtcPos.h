#ifndef ML_SCNOBJACCPARTSETCPOS_H
#define ML_SCNOBJACCPARTSETCPOS_H

#include "classes/ml/DrMdoCtlSeam.h"

namespace mm { class Mat44; }

namespace ml {
// access to one of a seam's effect positions (returned by value through memory: not trivially copyable)
class ScnObjAccPartsEtcPos {
public:
    explicit ScnObjAccPartsEtcPos(DrMdoCtlSeam::EtcPos* entry) : m_entry(entry) {}
    ~ScnObjAccPartsEtcPos() {}
    const char* getObjName() const;
    const char* getEffName() const;
    float getRange() const;
    float getNearClip(unsigned int index) const;
    float getFarClip(unsigned int index) const;
    unsigned int getMatrixMax() const;
    const mm::Mat44& getMatrix(unsigned int index) const;
    bool isDisp(unsigned int index) const;

    DrMdoCtlSeam::EtcPos* m_entry;  // the name is not the original's
};
}  // namespace ml

#endif
