#ifndef CLASSES_UI_UILISTINFOBASE_H
#define CLASSES_UI_UILISTINFOBASE_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace ui {
// table 0x7100B74CD0; counted: GfMenu*List::create adds a reference, GfMenuReference::finalize releases it with
// reference_object.h's `m_RefCount > 0` assertion on the count at 0x8
class UIListInfoBase : public ::mm::mtl::ReferenceObject {
public:
    // what setup copies into the list (0x14 bytes: setup copies 0x0-0xF as two words and the byte at 0x10)
    class SetupParam {
    public:
        unsigned int m_index;  // setup passes it to setIndex
        unsigned char pad_04[0xD];
    };
    UIListInfoBase();
    virtual ~UIListInfoBase();  // slot 0
    virtual void clear();  // slot 2
    virtual void update();  // slot 3
    void setup(const SetupParam& param);
    bool isValid() const;
    int getSize() const;  // the contents' count
    void addSize(unsigned int count);  // UIListInfo::addContents adds 1
    unsigned int getIndex(bool page) const;  // the selected content's (on the page, when asked)
    unsigned int getPageIndex(unsigned int index) const;  // the content at that place on the page shown
    unsigned int getRowSize() const;
    unsigned int getPageRowSize() const;  // the rows a page shows
    unsigned int getPageColumnSize() const;
    unsigned int getRowOffset() const;    // the first row shown
    unsigned char pad_0C[0x2C];  // from 0xC, in ReferenceObject's tail padding (the constructor zeroes 0x8-0xF as one)
};
}  // namespace ui

#endif
