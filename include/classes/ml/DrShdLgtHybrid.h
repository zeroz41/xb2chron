#ifndef CLASSES_ML_DRSHDLGTHYBRID_H
#define CLASSES_ML_DRSHDLGTHYBRID_H

namespace ml { class DrLightMan; }
namespace ml { class DrLightObjPnt; }
namespace ml { class DrLightObjSpt; }
namespace ml { class DrShdLgtMan; }
namespace ml { class DrShdLgtClustered; }
namespace ml { class DrShdLgtTileBasedDr; }

namespace ml {
// table 0x7100B7EEB8
class DrShdLgtHybrid {
public:
    virtual ~DrShdLgtHybrid();  // slot 0
    virtual void stockBegin();  // slot 2
    virtual void stockEnd();  // slot 3
    virtual void update();  // slot 4
    virtual void setupCate(int);  // slot 5
    virtual void addViewInfo(int);  // slot 6
    virtual void delViewInfo(int);  // slot 7
    virtual void stockPntList(ml::DrLightObjPnt*);  // slot 8
    virtual void stockSptList(ml::DrLightObjSpt*);  // slot 9
    virtual void render(ml::DrShdLgtMan*, ml::DrLightMan*);  // slot 10
    virtual void debugRender();  // slot 11

    // the constructor stores these; stockBegin/stockEnd forward to both (the names are not the original's)
    unsigned char pad_8[0x10];
    DrShdLgtClustered* m_pClustered;  // 0x18
    DrShdLgtTileBasedDr* m_pTileBasedDr;  // 0x20
};
}  // namespace ml

#endif
