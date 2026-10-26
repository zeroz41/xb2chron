#ifndef CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H
#define CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H

#include "classes/ml/ScnObjModelDrSys.h"
#include "ml/DrCreator.h"

namespace ml { class Scn; }

namespace ml {
// table 0x7100B7E828
class ScnObjModelDrSysStandard : public ::ml::ScnObjModelDrSys {
public:
    // inline: create's copy is the only one (no symbol of its own)
    ScnObjModelDrSysStandard(ml::Scn* scn, const void* res, const char* name, int view)
        : ScnObjModelDrSys(scn, res, name), pad_438(0) {
        if (m_pMdlObj == nullptr) {
            DrCreator creator;
            m_pMdlObj = creator.createMdl(m_pRes, m_mdlName, view);
            if (m_pMdlObj->m_mdlType == 3) {
                m_mdlType3 = 1;
            }
        }
    }
    static ScnObjModelDrSysStandard* create(ml::Scn* scn, const void* res, const char* name, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjModelDrSysStandard();  // slot 0
    virtual void update();  // slot 2
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5

    unsigned long pad_438;  // the constructor zeroes it
};
}  // namespace ml

#endif
