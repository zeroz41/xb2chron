#ifndef CLASSES_ML_DRMDLBASE_H
#define CLASSES_ML_DRMDLBASE_H

namespace ml { class DrMdlObj; }
namespace ml { class DrMdoSmlShadowMan; }
namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table none (its derived classes')
class DrMdlBase {
public:
    virtual ~DrMdlBase();  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void dispOffUpdate() {}  // slot 3
    virtual void noOffScreenUpdate() {}  // slot 4
    virtual void resourceInit() = 0;  // slot 5
    virtual void shadowRender() {}  // slot 6
    virtual void shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int) {}  // slot 8
    virtual void shadowCacheOnlyRender() {}  // slot 9
    virtual void shadowPartsRender(int) {}  // slot 10
    virtual void callShadowCacheUpdate(unsigned long) {}  // slot 11
    virtual void occRender() {}  // slot 12
    virtual bool cloneMdlObj(ml::DrMdlObj*) { return false; }  // slot 13
    virtual void chageShadowObject(ml::DrMdoSmlShadowMan*) {}  // slot 14
    virtual void setDisp(bool);  // slot 15
    virtual void setDeleteCall(int);  // slot 16
};
}  // namespace ml

#endif
