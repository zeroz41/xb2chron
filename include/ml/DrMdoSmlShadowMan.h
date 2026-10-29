#ifndef ML_DRMDOSMLSHADOWMAN_H
#define ML_DRMDOSMLSHADOWMAN_H

namespace ml {
class DrMan;
class DrMdoSmlShadowObj;

class DrMdoSmlShadowMan {
public:
    DrMdoSmlShadowMan(DrMan* man);
    void changeViewNum(DrMdoSmlShadowObj* obj, int viewNum);

    // sizeof 0x80 (DrMdlMan's constructor allocates that); the fields are not recovered
    unsigned char pad_0[0x80];
};
}  // namespace ml

#endif
