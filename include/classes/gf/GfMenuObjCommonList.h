#ifndef CLASSES_GF_GFMENUOBJCOMMONLIST_H
#define CLASSES_GF_GFMENUOBJCOMMONLIST_H

namespace gf {
// table none (its derived classes')
class GfMenuObjCommonList {
public:
    class ListListener;
    virtual void vf0();  // slot 0
    virtual void vf1();  // slot 1
    virtual void initialize() = 0;  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
