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
    class MainListener;
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
    // GfMenuObjCommonText::s_OpenNamedDialog is set
    static void close();
    unsigned char pad_24[4];
    GfMenuIDList* m_list;  // the enemy shown, as a one-entry list for the adapters (the name is not the original's)
};

// table 0x7100B638A8: GfMenuObjNamedDialog's listener (2.0.0's symbols name it)
class GfMenuObjNamedDialog::MainListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    MainListener(GfMenuObjNamedDialog* owner) : m_state(), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its D1 slot is the base's destructor
    // slot 2. 1 hides the object; 3 with parameter 2 clears the owner's list; 0x21 (open's open, the event's
    // first parameter the named row) shows that enemy, the difficulty and its record and fades in; 0x22 fades out
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    int m_state;  // 1 while shown (set by the open event, cleared by close); the name is not the original's
    unsigned char pad_10[0xC];
    GfMenuObjNamedDialog* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
