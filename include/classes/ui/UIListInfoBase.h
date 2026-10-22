#ifndef CLASSES_UI_UILISTINFOBASE_H
#define CLASSES_UI_UILISTINFOBASE_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace ui {
// table 0x7100B74CD0; counted: GfMenu*List::create adds a reference, GfMenuReference::finalize releases it with
// reference_object.h's `m_RefCount > 0` assertion on the count at 0x8. A list of contents laid out in rows of
// m_columnSize, shown a page (m_pageRowSize rows of m_pageColumnSize) at a time from m_rowOffset/m_columnOffset.
class UIListInfoBase : public ::mm::mtl::ReferenceObject {
public:
    // how the list is laid out (0x14 bytes: setup copies all of it); the field names are not the original's
    class SetupParam {
    public:
        SetupParam() : m_index(0), m_columnSize(0), m_pageRowSize(1), m_pageColumnSize(1), m_pageScroll(false) {}
        unsigned int m_index;           // setup passes it to setIndex
        unsigned int m_columnSize;      // the contents in a row; setup makes 0 a page's columns
        unsigned int m_pageRowSize;     // the rows a page shows
        unsigned int m_pageColumnSize;  // the columns a page shows
        // setIndex: a move of a page or more scrolls the page by as much, keeping the selection's place on it
        bool m_pageScroll;
    };
    UIListInfoBase();
    virtual ~UIListInfoBase();  // slot 0
    virtual void clear();  // slot 2
    virtual void update();  // slot 3
    void setup(const SetupParam& param);
    void setIndex(unsigned int index);  // selects that content, scrolling the page to it
    bool isValid() const;  // true when a page shows something
    bool isEmpty() const;  // 1.0.0's (3.0.1's linker dropped it)
    int getSize() const;  // the contents' count
    unsigned int getColumnSize() const;
    unsigned int getPageRowSize() const;  // the rows a page shows
    unsigned int getPageColumnSize() const;
    void addSize(unsigned int count);  // UIListInfo::addContents adds 1
    void subSize(unsigned int count);  // keeps the page and the selection inside the contents left
    unsigned int getPageSize() const;  // the contents a page shows
    unsigned int getRowSize() const;
    unsigned int getIndex(bool page) const;  // the selected content's (on the page, when asked)
    unsigned int getPageIndex(unsigned int index) const;  // the content at that place on the page shown
    unsigned int getRowOffset() const;     // the first row shown
    unsigned int getColumnOffset() const;  // the first column shown (1.0.0's; 3.0.1's linker dropped it)

    SetupParam m_param;           // setup's
    unsigned int m_size;          // getSize()
    unsigned int m_index;         // the selected content (setIndex's)
    unsigned int m_rowOffset;     // getRowOffset()
    unsigned int m_columnOffset;  // getColumnOffset()
    bool m_changed;  // set as the selection scrolls the page, cleared by update and clear (the name is not the original's)
};
}  // namespace ui

#endif
