#ifndef CLASSES_ML_DRMDOZSORTOBJ_H
#define CLASSES_ML_DRMDOZSORTOBJ_H

namespace ml {
// table 0x7100B7C668
class DrMdoZSortObj {
public:
    DrMdoZSortObj(void* owner);
    virtual ~DrMdoZSortObj() {}  // slot 0
    virtual void SetupRender() {}  // slot 2
    virtual void ZPrepassRender() {}  // slot 3
    virtual void ThicknessRenderFirst() {}  // slot 4
    virtual void ThicknessRenderSecond() {}  // slot 5
    virtual void render() {}  // slot 6
    virtual void GBuffRender() {}  // slot 7
    virtual void lightPrePassRender() {}  // slot 8
    virtual void alphaRender() {}  // slot 9
    virtual void spAlphaRender() {}  // slot 10
    virtual void refractionRender() {}  // slot 11

    // 1.0.0 has these four out of line (0x7100831500..); 3.0.1 inlines them
    void setNext(DrMdoZSortObj* next) { m_next = next; }
    void setParent(DrMdoZSortObj* parent) {
        if (this != parent) {
            m_parent = parent;
        }
    }
    DrMdoZSortObj* getNext() { return m_next; }
    DrMdoZSortObj* getParent() { return m_parent; }

    // 1.0.0's getNext() and getParent() return these; the field names are not the original's
    DrMdoZSortObj* m_next;  // 0x8
    DrMdoZSortObj* m_parent;  // 0x10
    // The constructor's argument: the controller every derived class forwards its render passes to
    // (DrMdoCtlNom, DrMdoCtlPos, DrMdoCtlMpf, DrMdoGrpObj, DrMdoCtlSeamAll, cloud::CloudMan).
    // The name is not the original's.
    void* m_owner;  // 0x18
};
}  // namespace ml

#endif
