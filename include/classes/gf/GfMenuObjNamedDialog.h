#ifndef CLASSES_GF_TUNK_B63860_H
#define CLASSES_GF_TUNK_B63860_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuIDList; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63860: the menu object of gf_menu_obj_named_dialog.cpp (new in 3.0.1; nothing names the class yet).
// Its listener shows an enemy's name, level, record time and difficulty (TXT_en_name, TXT_en_lv_num,
// TXT_en_record_time, TXT_en_diff)
class GfMenuObjNamedDialog : public ::gf::GfMenuObject {
public:
    GfMenuObjNamedDialog(unsigned int handle);
    virtual ~GfMenuObjNamedDialog();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(3) holds,
    // GfGameManager::isClearGame(), else GfGameManager::isEnableNamedRecord(); then, if object 0x8A exists and
    // GfGameUtil::getNamedListIndex(row) is nonzero, GfMenuObject::sendOpenEvent(0x8A's handle, that value).
    // GfMenuObjCommonText::openWithNamed passes its third argument (gf::GfFieldGrave::create's grave row)
    static void open(unsigned int row);
    // 2.0.0's symbols name it. What it does: the same game test, then GfMenuObject::sendCloseEvent(0x8A's handle, 0)
    // when object 0x8A exists. GfMenuObjCommonText's MainListener calls it on its close event (0x22) when
    // GfMenuObjCommonText::s_isNamedDialogOpen is set
    static void close();
    unsigned char pad_24[4];
    GfMenuIDList* m_list;  // the enemy shown, as a one-entry list for the adapters (the name is not the original's)
};

// table 0x7100B638A8: GfMenuObjNamedDialog's listener (nothing names the class yet)
class TUnk_B638A8 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B638A8(GfMenuObjNamedDialog* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B638A8() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjNamedDialog* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
