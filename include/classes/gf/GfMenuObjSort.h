#ifndef CLASSES_GF_GFMENUOBJSORT_H
#define CLASSES_GF_GFMENUOBJSORT_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B649F8 (no RTTI; 1.0.0's symbols name the class): the sort menu (attached as external call 0x83)
class GfMenuObjSort : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjSort(unsigned int handle);
    virtual ~GfMenuObjSort();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // shows the list's page: each LAY_list_item@NN with its sort id's label, the selected one's TXT_list_name
    // faded out and TXT_list_select in (the parameters are not used)
    void refreshItem(unsigned int, unsigned int);
    // sends the sort menu (external call 0x83) its close event (0x22): 1.0.0's symbol; 3.0.1 only inlines it
    static void close();
    // 1.0.0 symbols (the parameter names are not the original's): GfMenuObjPouch2 sorts its stock list (menu 0x10)
    // by the sort id of its sort index, and opens the sort menu with that index
    static unsigned short getSortID(unsigned short menu, unsigned short index);
    static void open(unsigned int handle, unsigned int caller, unsigned short menu, unsigned short index);
    // sets the object of that handle's text to the sort id's label (ids below 100: BDAT 0x14E's message, else a
    // field skill's name; the parameter names are not the original's)
    static void setSortLabelText(unsigned short sortId, unsigned int handle);
    // the open event's (0x21) handle: the object the result event (0x148) goes to, its UI object kept alive while
    // the menu is open (the name is not the original's)
    unsigned int m_resultHandle;  // 0x24
    // the open event's caller: shown again when the menu closes (the name is not the original's)
    unsigned int m_callerHandle;  // 0x28
    unsigned int m_menu;  // 0x2C: the open event's menu, the BDAT 0x16D row of the sort types (the name is not the original's)
    GfMenuIDList* m_idList;  // 0x30: the constructor's create, the destructor releases it
};
}  // namespace gf

#endif
