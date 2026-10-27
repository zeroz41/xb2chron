#ifndef CLASSES_GF_TUNK_B5F9E8_H
#define CLASSES_GF_TUNK_B5F9E8_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuIDList; }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B5F9E8 (no RTTI, no 1.0.0 symbol): the menu object of gf_menu_obj_announce.cpp (the file name suggests
// an announce menu)
class TUnk_B5F9E8 : public ::gf::GfMenuObject {
public:
    TUnk_B5F9E8(unsigned int handle);
    virtual ~TUnk_B5F9E8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit and it takes no object. What it does: registers full-screen layer 0x47 with a GfMenuTypes::Param
    // whose m_menuId is 1 (GfMenuFullScreen::registLayerParam).
    static void fn_710038289C();

    unsigned int pad_24;
    unsigned long pad_28;
    GfMenuSequence<TUnk_B5F9E8, 4> m_seq;      // 0x30 (the name is not the original's)
    GfMenuSequence<TUnk_B5F9E8, 4> m_mainSeq;  // 0x190 (the name is not the original's)
    // 0x2F0-0x300: what initialize creates, the destructor releases (the names are not the original's)
    ui::UISelectObjList* m_selectList;
    ui::UICtrlCursorSelect* m_cursor;  // over m_selectList
    GfMenuIDList* m_idList;            // the constructor's create
    unsigned int pad_308;
    bool pad_30C;
    unsigned int pad_310;
    unsigned int pad_314;
};
}  // namespace gf

#endif
