#ifndef CLASSES_GF_GFMENUOBJSTAFFROLL_H
#define CLASSES_GF_GFMENUOBJSTAFFROLL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/CreditReader.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"

namespace fw { class CommonResource; }
namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B64AD8
class GfMenuObjStaffroll : public ::gf::GfMenuObject {
public:
    class MainListener;
    // a laid-out row (Vector<RowInfo>::push_back by update; the field names are not the original's)
    struct RowInfo {
        unsigned int m_y;       // its offset from the top
        int m_height;           // its image's height (0 without one)
        unsigned int m_index;   // its row in the credit file
        unsigned short m_flag;  // cleared by update
        mm::mtl::FixedVector<unsigned int, 4> m_texts;  // createText's handles
    };
    GfMenuObjStaffroll(unsigned int handle);
    virtual ~GfMenuObjStaffroll();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // event::UIManager::startStaffrollUI/endStaffroll's (no this: they reach the menu object by its id)
    static void start(float speed, int type);
    static void fadeout();
    // a duplicate of the column's text part (TXT_left/center/right), set to its text; its handle, 0 if none
    unsigned int createText(unsigned int index, const CreditReader::Column& column);
    unsigned char pad_24[4];
    // the credit file's resource (initialize's fw::CommonResource::request, released by the destructor; the name is
    // not the original's)
    fw::CommonResource* m_resource;
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
    ui::UISelectObjList* m_list;          // the constructor's (the name is not the original's)
    mm::mtl::Vector<RowInfo> m_rows;      // update's (the name is not the original's)
};
}  // namespace gf

#endif
