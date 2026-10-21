#ifndef CLASSES_GF_GFMENUOBJMAINROOT_H
#define CLASSES_GF_GFMENUOBJMAINROOT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63248
class GfMenuObjMainRoot : public ::gf::GfMenuObject {
public:
    class MainListener;
    struct OpenParam {
        unsigned int m_menuId;  // registOpenParam passes it on as the screen layer's menu
    };
    GfMenuObjMainRoot(unsigned int handle);
    virtual ~GfMenuObjMainRoot();  // slot 0
    static void registOpenParam(const OpenParam& param);
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
