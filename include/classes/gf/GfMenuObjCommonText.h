#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class MenuCommonWindowParam; }

namespace gf {
// table 0x7100B61478
class GfMenuObjCommonText : public ::gf::GfMenuObject {
public:
    // what GfPlayFactory::createMenuObjCommonText hands GfSequentialPlay::addMenuObjCommonText
    class OpenKizunaParam;
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
    static void open(GfMenuCallContext* context, const MenuCommonWindowParam& param);
    // an item's text (GfMenuManager::openPreciousWindow passes kind 11 and the item id)
    static void openItem(GfMenuCallContext* context, unsigned int kind, unsigned int item);
    static void close();
};
}  // namespace gf

#endif
