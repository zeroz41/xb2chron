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
    // the Kizuna dialog for a call context (GfPlayComMenuObjCommonText::start)
    static void openKizunaDialog(GfMenuCallContext* context, const OpenKizunaParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its address lies in
    // gf_menu_obj_common_text's unit. What it does: GfMenuManager::fn_7100359CD8 calls it in place of
    // open(context, text, 0), passing the reset call context, the window text id (as unsigned int) and its
    // own second argument (gf::GfFieldGrave::create's grave row argument) untouched as an unsigned short.
    static void fn_71003E1F60(GfMenuCallContext* context, unsigned int text, unsigned short arg);
};
// openKizunaDialog registers the text UIStr(m_bdat, m_id) and sends it with m_value (the field names are not
// the original's)
class GfMenuObjCommonText::OpenKizunaParam {
public:
    unsigned char* m_bdat;  // a message table
    unsigned int m_id;      // the text's id in it
    unsigned int m_value;   // the open event's third word
};
}  // namespace gf

#endif
