#ifndef CLASSES_ML_SCN_H
#define CLASSES_ML_SCN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class ScnRenderDrSys; }

namespace ml {
// a base of ml::Scn no evidence names yet
class TUnk_B77B18 {
public:
    virtual ~TUnk_B77B18();
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of ml::Scn no evidence names yet
class TUnk_B77B38 {
public:
    virtual ~TUnk_B77B38();
};
// table 0x7100B77AC8; base at 0x8 unknown (TUnk_B77B18), base at 0x18 unknown (TUnk_B77B38)
class Scn : public ::ml::IWorkEvent, public TUnk_B77B18, public TUnk_B77B38 {
public:
    virtual ~Scn();  // slot 0
    unsigned char pad_20[0x18];
    ScnRenderDrSys* m_renderDrSys;  // what UIScreenObject gives ScnRenderDrSysParmAcc (the name is not the original's)
};
}  // namespace ml

#endif
