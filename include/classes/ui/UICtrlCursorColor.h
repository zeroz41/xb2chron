#ifndef CLASSES_UI_UICTRLCURSORCOLOR_H
#define CLASSES_UI_UICTRLCURSORCOLOR_H

#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UISelectObjList.h"

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74420; marks the selected object of a list: shows each object's child named by the setting's
// display format for the selected one only, and colors the child of its color format with the select or normal
// color's "%s_mul"/"%s_add" (the field names are not the original's)
class UICtrlCursorColor : public ::ui::UICtrlObject {
public:
    struct CursorSetting {
        CursorSetting()
            : m_dispName(nullptr), m_colorName(nullptr), m_normalColor("txt_normal2"), m_selectColor("txt_normal2") {}
        const char* m_dispName;     // a format of the object's number from 1: the child shown when selected
        const char* m_colorName;    // a format of the object's number from 1: the child colored
        const char* m_normalColor;  // the color of an object not selected
        const char* m_selectColor;  // the color of the selected object
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006CB640, create holds its stores)
    UICtrlCursorColor(unsigned int handle) : UICtrlObject(handle), m_setting(), m_list(nullptr), m_index(0), m_objHandle(0) {}
    virtual ~UICtrlCursorColor();  // slot 0
    virtual void update(const fw::UpdateInfo& info);  // slot 2
    // a control on the objects of list (it holds a reference to it); null without one
    static UICtrlCursorColor* create(unsigned int handle, const CursorSetting& setting, UISelectObjList* list);
    void open(int index);
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006CB880)
    void setIndex(unsigned int index) {
        if (m_list != nullptr) {
            m_list->setIndex(index);
        }
    }
    bool inputChange(unsigned int index);  // selects index and recolors (false for none or an empty list)
    void setDisp(bool disp);  // hidden: no object is selected

    CursorSetting m_setting;
    UISelectObjList* m_list;  // a reference held until the destructor
    unsigned int m_index;     // the list's selection as update last saw it
    unsigned int m_objHandle;  // create's handle; nothing in 3.0.1 reads it
};
}  // namespace ui

#endif
