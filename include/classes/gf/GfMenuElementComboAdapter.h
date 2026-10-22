#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BAF0
class GfMenuElementComboAdapter {
public:
    class ReferenceRouteConverter;
    virtual ~GfMenuElementComboAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // an adapter showing a combo route's element on the object (GfMenuObjComboRoute::setupComboRoute's: kinds 1,
    // 2, 5 and 6, each with its route index)
    static GfMenuElementComboAdapter* createReferenceRoute(unsigned int handle, unsigned int kind, unsigned int route,
                                                           bool);
};
}  // namespace gf

#endif
