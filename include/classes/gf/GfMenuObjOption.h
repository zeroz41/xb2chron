#ifndef CLASSES_GF_GFMENUOBJOPTION_H
#define CLASSES_GF_GFMENUOBJOPTION_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63CA8
class GfMenuObjOption : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class ItemSettingListener;
    class MainListener;
    class SubMenuListener;
    virtual ~GfMenuObjOption();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
