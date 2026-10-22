#ifndef CLASSES_UI_UISELECTOBJLIST_H
#define CLASSES_UI_UISELECTOBJLIST_H

#include "classes/ui/UIListInfo.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// table 0x7100B74D00: a list of UI objects' handles
class UISelectObjList : public ::ui::UIListInfo<unsigned int> {
public:
    // what create takes (callers zero it and set the allocator); the field name is not the original's
    class CreateParam {
    public:
        CreateParam() : m_allocator(nullptr) {}
        mm::mtl::IAllocator* m_allocator;  // the list's buffer comes from it
    };
    UISelectObjList();
    virtual ~UISelectObjList();  // slot 0
    static UISelectObjList* create(const CreateParam& param);  // referenced once, set up for 0x20 rows
    void addObject(unsigned int handle);  // unless the list has it
    void delObject(unsigned int handle);
    // the children of the object handle names format formats with start, start + 1 ... while it has them
    void pickupObject(unsigned int handle, const char* format, unsigned int start);
    unsigned int getObject(unsigned int index);
    unsigned int getSelectObject();
};
}  // namespace ui

#endif
