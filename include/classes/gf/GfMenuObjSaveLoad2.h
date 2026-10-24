#ifndef CLASSES_GF_GFMENUOBJSAVELOAD2_H
#define CLASSES_GF_GFMENUOBJSAVELOAD2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B646C8
class GfMenuObjSaveLoad2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what GfMenuManager::openSave passes registOpenParam (the field name is not the original's)
    struct OpenParam {
        unsigned short m_mode;  // 1 from openSave
    };
    static void registOpenParam(const OpenParam& param);
    virtual ~GfMenuObjSaveLoad2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
