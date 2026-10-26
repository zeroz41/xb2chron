#ifndef CLASSES_ML_SCNOBJIBLDR_H
#define CLASSES_ML_SCNOBJIBLDR_H

#include "classes/ml/ScnObjIBL.h"

namespace ml { class WinProc; }
namespace mm { class Vec3; }

namespace ml { class Scn; }
namespace ml { class DrGlobalIBLPack; }

namespace ml {
// table 0x7100B7E6D8
class ScnObjIBLDr : public ::ml::ScnObjIBL {
public:
    // inline: create's copy is the only one (no symbol of its own); defined in ScnObjLightDrSys.cpp
    inline ScnObjIBLDr(ml::Scn* scn, const void* res, int view);
    static ScnObjIBLDr* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjIBLDr();  // slot 0
    virtual void apply();  // slot 4
    virtual const char* getName() const;  // slot 6
    virtual void setReferencePos(mm::Vec3 const&);  // slot 8
    virtual const mm::Vec3& getReferencePos() const;  // slot 9
    virtual void setFromCaptureTool();  // slot 10
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*);  // slot 11
    virtual void setName(char const*);  // slot 12
    DrGlobalIBLPack* m_pPack;  // 0x18, the view's DrGlobalIBLMan makes it (the name is not the original's)
    int m_view;  // 0x20, the view create passes (the name is not the original's)
};
}  // namespace ml

#endif
