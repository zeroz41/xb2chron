#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61478
class GfMenuObjCommonText : public ::gf::GfMenuObject {
public:
    class DialogListener;
    class DrChangeListener;
    class ErrorListener;
    class GetItemListener;
    class KizunaListener;
    class MainListener;
    class MerListener;
    class NumSelectListener;
    class OwnerChangeListener;
    class SelectListener;
    virtual ~GfMenuObjCommonText();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // opens text `text` for a call context
    static void open(GfMenuCallContext* context, unsigned int text, unsigned int);
};
}  // namespace gf

#endif
