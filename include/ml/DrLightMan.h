#ifndef ML_DRLIGHTMAN_H
#define ML_DRLIGHTMAN_H

namespace ml {
class DrLightObjPnt;
class DrLightObjSpt;

// DrMan's light manager (DrMan::m_lightMan). Only what DrResMdoLight calls is declared.
class DrLightMan {
public:
    DrLightObjPnt* createInstantPntLight();
    void releasePntLight(DrLightObjPnt* light);
    void releaseSptLight(DrLightObjSpt* light);
};
}  // namespace ml

#endif
