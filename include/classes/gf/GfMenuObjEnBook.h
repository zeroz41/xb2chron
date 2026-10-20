#ifndef CLASSES_GF_GFMENUOBJENBOOK_H
#define CLASSES_GF_GFMENUOBJENBOOK_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61DD8
class GfMenuObjEnBook : public ::gf::GfMenuObject {
public:
    class DetailListener;
    class EnListListener;
    class FamilySelListener;
    class GenusSelListener;
    class IndexListener;
    class LocationSelListener;
    class MainListener;
    class TopListener;
    virtual ~GfMenuObjEnBook();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
