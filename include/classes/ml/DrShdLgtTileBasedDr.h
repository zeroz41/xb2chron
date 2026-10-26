#ifndef CLASSES_ML_DRSHDLGTTILEBASEDDR_H
#define CLASSES_ML_DRSHDLGTTILEBASEDDR_H

#include "classes/ml/DrShdLgtDynamic.h"

namespace ml { class DrLightMan; }
namespace ml { class DrMan; }
namespace ml { class DrLightObjPnt; }
namespace ml { class DrLightObjSpt; }
namespace ml { class DrShdLgtMan; }

namespace ml {
// table 0x7100B7E568
class DrShdLgtTileBasedDr : public ::ml::DrShdLgtDynamic {
public:
    explicit DrShdLgtTileBasedDr(DrMan* drMan);
    virtual ~DrShdLgtTileBasedDr();  // slot 0
    virtual void stockBegin();  // slot 2
    virtual void stockEnd() {}  // slot 3
    virtual void update();  // slot 4
    virtual void addViewInfo(int);  // slot 6
    virtual void delViewInfo(int);  // slot 7
    virtual void stockPntList(ml::DrLightObjPnt*);  // slot 8
    virtual void stockSptList(ml::DrLightObjSpt*);  // slot 9
    virtual void render(ml::DrShdLgtMan*, ml::DrLightMan*);  // slot 10
    virtual void debugRender();  // slot 11

    unsigned char pad_18[0x380];  // to 0x398, the size DrShdLgtHybrid's constructor allocates
};
}  // namespace ml

#endif
