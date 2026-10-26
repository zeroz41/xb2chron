#ifndef ML_DRCREATOR_H
#define ML_DRCREATOR_H

namespace ml {
class DrGpuCheckBase;
class DrStmReadCheck;
class DrMan;
class DrMdlObj;
class DrMdoGrpObj;
class DrEnvironmentObj;
class DrEnvColiObj;
class DrCalcClipObj;

// makes draw objects (used on the stack by ScnObjAccGpuCheck::create and ScnObjAccStmReadObj::create)
class DrCreator {
public:
    DrCreator();
    DrMdlObj* createMdl(const void* resource, const char* name, int arg);
    DrMdoGrpObj* createInstantGrp(int arg, unsigned int viewNum);
    // the view's DrEnvironmentMan makes it
    DrEnvironmentObj* createLgt(const void* resource, int view);
    DrEnvColiObj* createEnvColi(const void* resource, int view);
    DrCalcClipObj* createClipObj(const void* resource, int view);
    DrGpuCheckBase* createGpuCheckObj(int arg);
    DrStmReadCheck* createStmLoadObj(const char* name);
    DrMan* m_pDrMan;  // DrMan::s_pTop when made (the name is not the original's)
};
}  // namespace ml

#endif
