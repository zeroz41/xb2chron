#ifndef CLASSES_UI_UIOBJECTLIST_H
#define CLASSES_UI_UIOBJECTLIST_H

#include "mm/mtl/IntrusiveList.h"
#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B75770; a layout's children (UILayoutObject's constructor makes one), linked through their
// UIObjectBase nodes. The field names are not the original's.
class UIObjectList {
public:
    UIObjectList();
    virtual ~UIObjectList();  // slot 0
    void clear();  // releases every object (the destructor's)
    void update();
    unsigned int regist(UIObject* object, const char* name);  // the object's handle; 0 when it is null or listed
    void release(UIObject* object);
    void release(const char* name);  // the object listed under the name (UIGroup::updateObject's)
    void apply();
    unsigned int count(const char* name, unsigned int);
    unsigned int search(const char* name);
    unsigned int searchDuplicate(const char* name, unsigned short);
    void reloadText();
    mm::mtl::IntrusiveList<UIObject> m_list;
    bool m_allTerm;  // update's: every child is terminated (UILayoutObject::setInitialize clears it)
    bool m_changed;  // update's: a child changed or went (UILayoutObject::updateSize clears it)
};
}  // namespace ui

#endif
