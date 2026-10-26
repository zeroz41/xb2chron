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
    void releaseInstantPntLight(DrLightObjPnt* light);
    void releaseInstantSptLight(DrLightObjSpt* light);

    unsigned char pad_0[0x108];
    // instant lights in use: releaseInstant*Light count them down, never below 0 (the names are not the original's)
    int m_instantPntNum;  // 0x108
    int m_instantSptNum;  // 0x10C
};
}  // namespace ml

#endif
