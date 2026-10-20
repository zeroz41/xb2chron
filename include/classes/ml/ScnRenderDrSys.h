#ifndef CLASSES_ML_SCNRENDERDRSYS_H
#define CLASSES_ML_SCNRENDERDRSYS_H

#include "classes/ml/ScnRender.h"

namespace ml { class Scn; }
namespace ml { class ScnObjCam; }
namespace ml { class ScnSetup; }
namespace ml { class WinProc; }

namespace ml {
// table 0x7100B7A000
class ScnRenderDrSys : public ::ml::ScnRender {
public:
    virtual ~ScnRenderDrSys();  // slot 0
    virtual void setDefaultEvn();  // slot 8
    virtual void applyCamera(ml::ScnObjCam*);  // slot 9
    virtual void update();  // slot 10
    virtual void applyBegin();  // slot 11
    virtual void applyEnd();  // slot 12
    virtual void applyLoopCnt();  // slot 13
    virtual void applyUpdate(int);  // slot 14
    virtual void applyRender(int);  // slot 15
    virtual void tail();  // slot 16
    virtual void setMdlDblPause(bool);  // slot 17
    virtual void setGlbSpd(float);  // slot 18
    virtual void setup(ml::ScnSetup const*);  // slot 20
    virtual void openPixelDebugWindow(ml::WinProc*);  // slot 21
    virtual void openHisgtramDebugWindow(ml::WinProc*);  // slot 22
    virtual void createMdl(ml::Scn*, void const*, char const*, int);  // slot 23
    virtual void createLgt(ml::Scn*, void const*, int);  // slot 24
    virtual void createClip(ml::Scn*, void const*, int);  // slot 25
    virtual void createIBL(ml::Scn*, void const*, int);  // slot 26
    virtual void createEnvColi(ml::Scn*, void const*, int);  // slot 27
};
}  // namespace ml

#endif
