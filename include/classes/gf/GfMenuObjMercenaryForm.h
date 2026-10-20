#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63350
class GfMenuObjMercenaryForm : public ::gf::GfMenuObject {
public:
    class ApplyListener;
    class BlImgListener;
    class FormListener;
    class LeaderListener;
    class ListListener;
    class MainListener;
    class PresetListener;
    class StartListener;
    class UnitListener;
    virtual ~GfMenuObjMercenaryForm();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
