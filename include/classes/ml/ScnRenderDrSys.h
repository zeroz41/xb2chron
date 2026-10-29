#ifndef CLASSES_ML_SCNRENDERDRSYS_H
#define CLASSES_ML_SCNRENDERDRSYS_H

#include "classes/ml/ScnRender.h"

namespace ml { class DrMan; }
namespace ml { class IDrDrawCallback; }
namespace ml { class Scn; }
namespace ml { class ScnObj; }
namespace ml { class ScnObjIBL; }
namespace ml { class ScnObjModel; }
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
    virtual bool applyLoopCnt();  // slot 13
    virtual void applyUpdate(int);  // slot 14
    virtual void applyRender(int);  // slot 15
    virtual void tail();  // slot 16
    virtual void setMdlDblPause(bool);  // slot 17
    virtual void setGlbSpd(float);  // slot 18
    virtual void setup(ml::ScnSetup const*);  // slot 20
    virtual void openPixelDebugWindow(ml::WinProc*);  // slot 21
    virtual void openHisgtramDebugWindow(ml::WinProc*);  // slot 22
    virtual ml::ScnObjModel* createMdl(ml::Scn*, void const*, char const*, int);  // slot 23
    virtual ml::ScnObj* createLgt(ml::Scn*, void const*, int);  // slot 24
    virtual void createClip(ml::Scn*, void const*, int);  // slot 25
    virtual ml::ScnObjIBL* createIBL(ml::Scn*, void const*, int);  // slot 26
    virtual void createEnvColi(ml::Scn*, void const*, int);  // slot 27

    void setCallBack(IDrDrawCallback* callback);
    void releaseCallBack(IDrDrawCallback* callback);

    DrMan* m_drMan;  // ScnRenderDrSys::thDrSysInitialize makes it; the renderer's calls go to it
};
}  // namespace ml

#endif
