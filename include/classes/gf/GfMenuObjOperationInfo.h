#ifndef CLASSES_GF_GFMENUOBJOPERATIONINFO_H
#define CLASSES_GF_GFMENUOBJOPERATIONINFO_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B63C38
class GfMenuObjOperationInfo : public ::gf::GfMenuObject {
public:
    class MainListener;
    // a duplicated LAY_item of the guide's icon table (createIconTable, setupIconTable); the field names are not the
    // original's
    struct DupItem {
        unsigned int m_handle;      // 0x0: the LAY_item copy
        unsigned int m_key;         // 0x4: the button key (BDAT 0x186's "key")
        unsigned int m_text;        // 0x8: its text's message id
        unsigned short m_order;     // 0xC: BDAT 0x186's "order" (or "order2")
        bool m_used;                // 0xE: setupIconTable filled it
    };
    // an input handle's actions the guide lists (setupListSub); the field names are not the original's
    struct InputAction {
        unsigned int m_action;      // 0x0
        unsigned int m_kind;        // 0x4
    };
    struct InputObj {
        unsigned int m_handle;      // 0x0: the UI object whose input layer it reads
        unsigned int pad_4;
        mm::mtl::FixedVector<InputAction, 8> m_actions;  // 0x8
    };
    GfMenuObjOperationInfo(unsigned int handle);
    virtual ~GfMenuObjOperationInfo();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void close();
    static void setGuideDisp(bool disp);
    static void setDisp(bool disp);
    // a handle's operation guide, kept until remove (GfMenuObjSkipTime's while it is open)
    static void add(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void remove(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void setGuideText(unsigned int text, unsigned int);
    // enables or disables an action of the operation guide for the object of that handle (the parameter names are
    // not the original's: GfMenuObjDrEquip2 passes action 10)
    static void setActionEnable(unsigned int handle, unsigned int action, bool enable);
    // switches an action of the handle's operation guide between its two texts (the parameter names are not the
    // original's: GfMenuObjHanaPartsMake's parts list passes action 9 with its list mode)
    static void changeText(unsigned int handle, unsigned int action, bool alternate);
    // the same event (0x104) with a text index (GfMenuObjCharSelect, GfMenuObjQuestList's detail)
    static void changeText(unsigned int handle, unsigned int action, unsigned int text);
    static void createIconTable(ui::UIObjectAcc& acc, mm::mtl::FixedVector<DupItem, 16>& items);
    static void setupList(unsigned int handle, mm::mtl::FixedVector<InputObj, 16>& objs,
                          mm::mtl::FixedVector<DupItem, 16>& items);
    static void setupListSub(unsigned int handle, InputObj& obj, mm::mtl::FixedVector<DupItem, 16>& items,
                             unsigned int& count);
    static bool setupIconTable(mm::mtl::FixedVector<DupItem, 16>& items, unsigned int index, unsigned int key,
                               unsigned int text, unsigned int order2);

    mm::mtl::FixedVector<DupItem, 16> m_items;     // 0x28
    mm::mtl::FixedVector<InputObj, 16> m_inputs;   // 0x130
};
}  // namespace gf

#endif
