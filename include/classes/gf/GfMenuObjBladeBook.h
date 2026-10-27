#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"

namespace gf { class GfMenuBladeList; struct GAME_VOICE_HANDLE; }
namespace ui { class UICtrlCursorSelect; class UISelectObjList; }

namespace gf {
// blades unlocked so far, for the blade book (refreshBladeList greys a blade it says true for)
bool isUnuseBlade(unsigned int blade);

// table 0x7100B5FDB8
// The field names are not the original's (the layout is from the constructor, destructor and their users).
class GfMenuObjBladeBook : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    class PreviewListener;
    GfMenuObjBladeBook(unsigned int handle);
    virtual ~GfMenuObjBladeBook();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    void refreshBladeList();
    bool seqOpenImage();
    void getScreenOverSize(unsigned int handle, float scale, short& width, short& height);
    void setPreviewScale(unsigned int step);

    GfMenuBladeList* m_bladeList;        // 0x28: the book's blades (setupFromBook)
    ui::UISelectObjList* m_selectList;   // 0x30: LAY_list_bl@NN
    ui::UICtrlCursorSelect* m_cursor;    // 0x38: IMG_list_bl_cursor's
    GfMenuSequence<GfMenuObjBladeBook, 8> m_seq;  // 0x40
    bool m_unknownFlag;                  // 0x2D0: the constructor clears it; no 3.0.1 code reads it
    GAME_VOICE_HANDLE* m_voice;          // 0x2D8: the blade voice the preview plays
    mm::Pnt<short> m_pointerPos;         // 0x2E0: the preview's pointer position (setPreviewScale)
    int m_zoomStep;                      // 0x2E4: the preview's zoom step (0-4; setPreviewScale's argument)
    mm::Pnt<short> m_previewCenter;      // 0x2E8: IMG_prev_bl_img's centre at initialize
    unsigned char pad_2EC[4];
    mm::Vec2 m_baseScale;                // 0x2F0: IMG_prev_bl_img's scale at initialize (mm::Vec2 takes 0x10)
    mm::Pnt<short> m_scrollOrigin;       // 0x300: setPreviewScale's pointer selection origin
    mm::Pnt<short> m_overSize;           // 0x304: getScreenOverSize's for the current scale
    float m_previewScale;                // 0x308: the scale setPreviewScale last set
    unsigned char pad_30C[4];
};
}  // namespace gf

#endif
