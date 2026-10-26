#ifndef CLASSES_GF_GFMENUMODELVIEW_H
#define CLASSES_GF_GFMENUMODELVIEW_H

namespace gf {
// table 0x7100B5F8D0
class GfMenuModelView {
public:
    virtual ~GfMenuModelView();  // slot 0
    void update();
    bool isLoading() const;  // its models still load (GfMenuObjBladeCreate::seqWaitLoading waits for false)
};
}  // namespace gf

#endif
