#ifndef CLASSES_UI_UICTRLFRAME_H
#define CLASSES_UI_UICTRLFRAME_H

#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlSimple.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"
#include "mm/mtl/Vector.h"
#include "ui/UIUtil.h"

namespace fw { class UpdateInfo; }
namespace ui { class UISelectObjList; }

namespace ui {
// table 0x7100B74470; a frame (a viewport object) over a content object that it scrolls to a point (movePoint) and
// scales (setScale), each over a time; a list's objects keep their places in the content as it scales. The field
// names are not the original's (update and create show what each does)
class UICtrlFrame : public ::ui::UICtrlObject {
public:
    // an object of the list and its center from the content's corner (update records each object it has not seen)
    struct ObjPosInfo {
        unsigned int m_handle;
        mm::Pnt<short> m_pos;
    };
    // create's: the children of the control's object it looks up by name (none when null), and the times
    struct Setting {
        // every field cleared (GfMenuObjWorldMap::seqNext keeps the cleared curves: the zero stores of 0x28-0x33
        // that its own stores partly overwrite, not 0x34-0x37, which is padding)
        Setting()
            : m_viewName(nullptr), m_contentName(nullptr), m_centerName(nullptr), m_offsName(nullptr), m_distance(-1),
              m_moveTime(0.0f), m_moveCurve(CURVE_LINEAR), m_scaleTime(0.0f), m_scaleCurve(CURVE_LINEAR),
              m_list(nullptr) {}
        const char* m_viewName;     // the frame: its rectangle becomes the control object's layout viewport
        const char* m_contentName;  // the object scaled and moved
        const char* m_centerName;   // an object update centers on the clamped point
        const char* m_offsName;     // an object kept at its place over the content
        int m_distance;             // movePoint: a move farther than this animates (-1: only when asked)
        float m_moveTime;
        // the move's and the scale's curves: create does not read them (the names are not the original's)
        CURVE_TYPE m_moveCurve;
        float m_scaleTime;
        CURVE_TYPE m_scaleCurve;
        UISelectObjList* m_list;  // objects placed in the content (a reference held until the destructor)
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006CC728, create holds its stores)
    UICtrlFrame(unsigned int handle)
        : UICtrlObject(handle), m_view(0), m_content(0), m_offsObj(0), m_centerObj(0), m_list(nullptr), m_scale(1.0f),
          m_move(), m_moveTime(0.0f), m_moveCurve(CURVE_LINEAR), m_scaleMove(), m_scaleTime(0.0f),
          m_scaleCurve(CURVE_LINEAR), m_distance(-1), m_objPos() {}
    virtual ~UICtrlFrame();  // slot 0
    virtual void update(const fw::UpdateInfo& info);  // slot 2
    static UICtrlFrame* create(unsigned int handle, const Setting& setting);
    // scales the content to scale, over m_scaleTime when anim (event 2 with the time and both scales)
    void setScale(float scale, bool anim);
    // moves the point the content follows to pos, over m_moveTime when anim or the move is farther than
    // m_distance (event 2 with a time and both points)
    void movePoint(mm::Pnt<short> pos, bool anim);

    mm::Pnt<short> m_point;    // where the content's point is (movePoint's target, or where its move is)
    mm::Pnt<short> m_clamped;  // m_point kept inside the content as update last placed it
    unsigned int m_view;       // Setting::m_viewName's
    unsigned int m_content;    // Setting::m_contentName's
    unsigned int m_offsObj;    // Setting::m_offsName's
    unsigned int m_centerObj;  // Setting::m_centerName's
    UISelectObjList* m_list;
    float m_scale;                // the content's scale over m_baseScale
    mm::Rect<short> m_rect;       // the content's rectangle at create
    unsigned char pad_0x5C[4];
    mm::Vec2 m_baseScale;         // the content's scale at create
    mm::Pnt<short> m_offsPos;     // m_offsObj's corner from the content's at create; nothing in 3.0.1 reads it
    unsigned char pad_0x74[4];
    UICtrlSimple<2> m_move;       // m_point's x and y on a move
    float m_moveTime;
    CURVE_TYPE m_moveCurve;       // nothing in 3.0.1 sets it
    UICtrlSimple<1> m_scaleMove;  // m_scale on a scaling
    float m_scaleTime;
    CURVE_TYPE m_scaleCurve;      // nothing in 3.0.1 sets it
    int m_distance;
    mm::mtl::Vector<ObjPosInfo> m_objPos;
};
}  // namespace ui

#endif
