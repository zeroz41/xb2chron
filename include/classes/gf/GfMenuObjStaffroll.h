#ifndef CLASSES_GF_GFMENUOBJSTAFFROLL_H
#define CLASSES_GF_GFMENUOBJSTAFFROLL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/CreditReader.h"

namespace gf {
// table 0x7100B64AD8
class GfMenuObjStaffroll : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjStaffroll();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // event::UIManager::startStaffrollUI/endStaffroll's (no this: they reach the menu object by its id)
    static void start(float speed, int type);
    static void fadeout();
    unsigned char pad_24[4];
    // 0x28: the credit file's resource (initialize's fw::CommonResource::request, released by the destructor)
    unsigned char pad_28[8];
    CreditReader m_reader;  // the credit file, as read (the name is not the original's)
    // update's state: 1 once the rows are laid out, 2 scrolling (MainListener's open), 4 at the end (the name is not
    // the original's)
    int m_state;
    // how far it scrolls: the rows' height plus 720 (the screen's); MainListener's open divides it by the scroll time
    // (the name is not the original's)
    unsigned int m_scrollLength;
    unsigned int m_row;      // the next row update lays out (the name is not the original's)
    float m_scroll;          // how far it has scrolled (the name is not the original's)
    float m_scrollSpeed;     // how far it scrolls per frame (the name is not the original's)
    bool m_end;              // update's: the last row is out (the name is not the original's)
    // 0x70: the constructor's ui::UISelectObjList, 0x78: the rows (mm::mtl::Vector<RowInfo>, its allocator at 0x98)
    unsigned char pad_6D[0x33];
};
}  // namespace gf

#endif
