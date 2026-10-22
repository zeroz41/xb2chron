#ifndef CLASSES_UI_UICTRLCURSORSELECT_H
#define CLASSES_UI_UICTRLCURSORSELECT_H

#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"
#include "ui/UIUtil.h"

namespace fw { class UpdateInfo; }
namespace ui { class UISelectObjList; }

namespace ui {
// table 0x7100B74448; a cursor object that follows the selected object of a list, moving to it over a time (the
// field names are not the original's). Counted through UICtrlObject's ReferenceObject (GfMenuObjAnnounce's destructor
// releases one with reference_object.h's assertion on the count at 0x8 and slot 1)
class UICtrlCursorSelect : public ::ui::UICtrlObject {
public:
    // create's (a user-provided constructor: create copies its 0x21 bytes of data, the size without the tail)
    struct CursorSetting {
        CursorSetting()
            : m_moveTime(0.0f), m_moveCurve(CURVE_LINEAR), m_waitAnim(nullptr), m_moveAnim(nullptr), m_dockType(1),
              m_offsetX(0), m_offsetY(0), m_fixX(false), m_fixY(false), m_outer(true) {}
        void setType(int type);  // 0: no move, 1: a linear move of 0.15 s, 2: a CURVE_SIN90 one
        float m_moveTime;        // the time a move to the selection takes (0: it jumps)
        CURVE_TYPE m_moveCurve;
        const char* m_waitAnim;  // the cursor's animation when it rests (create and a move's end start it)
        const char* m_moveAnim;  // the cursor's animation when it starts a move
        unsigned short m_dockType;  // 5: fit around the selection, 6: on its center, else UIUtil::setDockPos's side
        short m_offsetX;
        short m_offsetY;
        bool m_fixX;   // the cursor keeps its x
        bool m_fixY;   // the cursor keeps its y
        bool m_outer;  // UIUtil::setDockPos's last parameter
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006CBAC8, create holds its stores)
    UICtrlCursorSelect(unsigned int handle)
        : UICtrlObject(handle), m_setting(), m_list(nullptr), m_index(0), m_move(), m_cursor(0), m_pos(0, 0),
          m_disp(true) {}
    virtual ~UICtrlCursorSelect();  // slot 0
    virtual void update(const fw::UpdateInfo& info);  // slot 2
    // a cursor handle on the objects of list (it holds a reference to it); null without either
    static UICtrlCursorSelect* create(unsigned int handle, const CursorSetting& setting, UISelectObjList* list);
    // moves the cursor to the list's selection (index goes unused), over m_moveTime when anim
    void setSelIndex(unsigned int index, bool anim);
    void open(int index);
    void setIndex(unsigned int index);
    bool inputChange(unsigned int index);  // selects index (false for none or an empty list: the cursor hides)
    void setDisp(bool disp);
    void setAlpha(float alpha);
    void updateObjectPos(mm::Pnt<short> pos);
    // scales the cursor to the target's rectangle grown by the offsets (inline: 3.0.1 has no out-of-line copy,
    // 1.0.0's is at 0x71006CC658 and setSelIndex and updateObjectPos hold its code)
    void calcFit(UIObjectAcc& cursor, UIObjectAcc& target) {
        mm::Rect<short> rect;
        short width;
        short height;
        cursor.getSize(false, width, height);
        target.getRect(rect, 2);
        rect.x -= m_setting.m_offsetX;
        rect.y -= m_setting.m_offsetY;
        rect.w += m_setting.m_offsetX * 2;
        rect.h += m_setting.m_offsetY * 2;
        mm::Vec2 scale(rect.w / (float)width, rect.h / (float)height);
        cursor.setScale(scale);
    }

    CursorSetting m_setting;
    UISelectObjList* m_list;  // a reference held until the destructor
    unsigned int m_index;     // the list's selection as update last saw it
    UICtrlSimple<2> m_move;   // the cursor's x and y on a move
    unsigned int m_cursor;    // the cursor object
    mm::Pnt<short> m_pos;     // where the cursor is put
    bool m_disp;              // setDisp's
};
}  // namespace ui

#endif
