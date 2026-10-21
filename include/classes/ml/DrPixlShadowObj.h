#ifndef CLASSES_ML_DRPIXLSHADOWOBJ_H
#define CLASSES_ML_DRPIXLSHADOWOBJ_H

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7CE08
class DrPixlShadowObj {
public:
    virtual ~DrPixlShadowObj();  // slot 0
    virtual void update() {}  // slot 2
    virtual void afterUpdate() {}  // slot 3
    virtual void dispChk();  // slot 4
    virtual void clipChk(mm::Vec3 const&, float, bool);  // slot 5
    virtual void clipTypeChk(mm::Vec3 const&, float);  // slot 6
    virtual void setSptCalcPos(mm::Vec3 const&, float);  // slot 7
    virtual void renderLight() {}  // slot 8
    virtual void stockTile() {}  // slot 9
    virtual void debugInfo() {}  // slot 10
    virtual void getParmTbl() const;  // slot 11
};
}  // namespace ml

#endif
