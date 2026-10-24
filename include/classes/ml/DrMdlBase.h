#ifndef CLASSES_ML_DRMDLBASE_H
#define CLASSES_ML_DRMDLBASE_H

namespace ml { class DrMdlObj; }
namespace ml { class DrMdoSmlShadowMan; }
namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table none (its derived classes')
class DrMdlBase {
public:
    virtual ~DrMdlBase() {}  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void dispOffUpdate() {}  // slot 3
    virtual void noOffScreenUpdate() {}  // slot 4
    virtual void resourceInit() = 0;  // slot 5
    virtual void shadowRender() {}  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int) {}  // slot 8
    virtual void shadowCacheOnlyRender() {}  // slot 9
    virtual void shadowPartsRender(int) {}  // slot 10
    virtual void callShadowCacheUpdate(unsigned long) {}  // slot 11
    virtual void occRender() {}  // slot 12
    virtual bool cloneMdlObj(ml::DrMdlObj*) { return false; }  // slot 13
    virtual void chageShadowObject(ml::DrMdoSmlShadowMan*) {}  // slot 14
    virtual void setDisp(bool);  // slot 15
    virtual void setDeleteCall(int);  // slot 16

    // DrMdoGrpObj's constructor and DrMdoMat's chain share these fields (the names are not the original's)
    unsigned char pad_8[0x8];
    DrMdlBase* m_pNext;  // 0x10, the next object of the list DrMdoGrpObj's render passes walk
    // DrMdlObj's getGroups/setGroups read it
    short m_groups;  // 0x18
    short m_viewNum;  // 0x1A, DrMdoGrpObj's constructor argument; chageShadowObject passes it as the view number
    // the model's kind: 0 is a DrMdoCtlNom (the ScnObjAcc* accessors then use its data), ScnObjAccSeamPos takes
    // data at different offsets for 1 and 3 (the name is not the original's)
    unsigned char m_mdlType;  // 0x1C
    unsigned char pad_1D[0x3];
    unsigned int m_dispFlags;  // 0x20: setDisp sets bit 0, setDeleteCall sets bit 3 + its argument
    unsigned char pad_24[0x4];
};
}  // namespace ml

#endif
