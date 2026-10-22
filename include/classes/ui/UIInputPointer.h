#ifndef CLASSES_UI_UIINPUTPOINTER_H
#define CLASSES_UI_UIINPUTPOINTER_H

#include "classes/ui/UIInputLayer.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"

namespace mm { namespace mtl { class IAllocator; }}
namespace ui { class UISelectObjList; }

namespace ui {
// table 0x7100B74BD0
class UIInputPointer : public ::ui::UIInputLayer {
public:
    // the setup's own part follows the actions; the names are the UIO input table's columns
    // ui::UIObjFactory::setupObjectInput reads them from
    class PointerSetup : public InputSetup {
    public:
        unsigned short m_pointerSpeed;  // "pointer_speed": how far the stick moves the pointer a frame
        bool m_snap;                    // "snap": with the stick let go the pointer goes onto the selection
        unsigned short m_selectText;    // "select_text"
        unsigned short m_keySort;       // "key_sort"
    };
    // the region the pointer moves in and what it can select there (setupPointerSelection copies it whole and
    // counts a reference to the list); the names are not the original's
    class SelectionSetup {
    public:
        SelectionSetup() : m_sizeW(0), m_sizeH(0), m_list(nullptr), m_nearest(false) {}
        mm::Rect<short> m_rect;      // the region (scaled by m_regionScale from its corner)
        unsigned short m_sizeW;      // the pointer's size: it stays this far inside the region
        unsigned short m_sizeH;
        UISelectObjList* m_list;     // the objects it selects
        bool m_nearest;              // the one whose middle is nearest, not the first under the pointer
    };

    UIInputPointer(unsigned int id, unsigned int handle, const PointerSetup& setup)
        : UIInputLayer(id, handle, setup), m_pointerSpeed(setup.m_pointerSpeed), m_snap(setup.m_snap),
          m_selectText(setup.m_selectText), m_keySort(setup.m_keySort), m_pos(0, 0), m_dir(0.0f, 0.0f),
          m_snapped(false), m_scale(1.0f), m_eventExt(0), m_posChanged(false), m_scaleChanged(false),
          m_regionScale(1.0f), m_rectChanged(false), m_speedScale(1.0f) {}
    virtual ~UIInputPointer();  // slot 0
    virtual EventData* getInputEventExt();  // slot 2
    virtual bool hasEventExt() const;  // slot 3
    virtual void clearExt();  // slot 5
    virtual UIInputPointer* castUIInputPointer();  // slot 8
    virtual bool updateImpl();  // slot 9
    static UIInputPointer* create(unsigned int id, unsigned int handle, const PointerSetup& setup,
                                  mm::mtl::IAllocator* allocator);
    void setupPointerSelection(const SelectionSetup& setup);
    void changePointerPos(const mm::Pnt<short>& pos);
    void changeRegionScale(float scale);
    bool setPointerPos(const mm::Pnt<short>& pos, bool center, bool select);

    unsigned short m_pointerSpeed;
    bool m_snap;
    SelectionSetup m_selection;
    unsigned short m_selectText;
    unsigned short m_keySort;
    mm::Pnt<short> m_pos;  // where the pointer is
    mm::Vec2 m_dir;        // which way it last moved (0 when put somewhere)
    bool m_snapped;        // it went onto the selection with the stick let go
    float m_scale;         // the region scale the pointer's place is in
    EventData m_eventExt;  // 0xA: the pointer moved (where, whether onto a selection, the scale)
    bool m_posChanged;     // changePointerPos: the pointer goes to m_newPos on the next update
    mm::Pnt<short> m_newPos;
    bool m_scaleChanged;   // changeRegionScale: the region scales to m_regionScale on the next update
    float m_regionScale;
    bool m_rectChanged;    // the region becomes m_newRect on the next update (1.0.0's changeRegionRect)
    mm::Rect<short> m_newRect;
    float m_speedScale;    // scales m_pointerSpeed
};
}  // namespace ui

#endif
