#include "mm/mtl/Vector.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"

namespace ui {

// 1.0.0's constructor (3.0.1 has it only inlined into create)
UISelectObjList::UISelectObjList() {}

UISelectObjList::~UISelectObjList() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

UISelectObjList* UISelectObjList::create(const CreateParam& param) {
#line 38
    UISelectObjList* list = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UISelectObjList();
    UIListInfoBase::SetupParam setup;
    setup.m_pageRowSize = 0x20;
    list->setup(param.m_allocator, setup);
    list->addRef();
    return list;
}

void UISelectObjList::addObject(unsigned int handle) {
    for (unsigned int i = 0; i < (unsigned int)getSize(); i++) {
        if (getContents(i) == handle) {
            return;
        }
    }
    addContents(handle);
}

void UISelectObjList::delObject(unsigned int handle) {
    for (unsigned int i = 0; i < (unsigned int)getSize(); i++) {
        if (getContents(i) == handle) {
            m_list.erase(&m_list.begin()[i]);
            subSize(1);
            m_changed = true;
            return;
        }
    }
}

void UISelectObjList::pickupObject(unsigned int handle, const char* format, unsigned int start) {
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        mm::mtl::FixStr<32> name;
        name.format(format, start);
        unsigned int child = acc.searchChild(name.m_str);
        while (child != 0) {
            start++;
            addContents(child);
            name.format(format, start);
            child = acc.searchChild(name.m_str);
        }
    }
}

unsigned int UISelectObjList::getObject(unsigned int index) {
    return getContents(index);
}

unsigned int UISelectObjList::getSelectObject() {
    return getContents(getIndex(false));
}

}  // namespace ui
