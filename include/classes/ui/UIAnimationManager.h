#ifndef CLASSES_UI_UIANIMATIONMANAGER_H
#define CLASSES_UI_UIANIMATIONMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace ui { class UIAnimationManager; }
namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74320; the image objects with animations it watches: when one's animation stops playing it sends an
// event (0xC) to the object hooked to it
class UIAnimationManager : public ::mm::mtl::PtrSingleton< ::ui::UIAnimationManager> {
public:
    // one watched object (0x20 bytes: registObject's allocation); the names are not the original's
    struct ObjectNode : public mm::mtl::IntrusiveListNodeBase {
        unsigned int m_handle;       // the object
        bool m_playing;              // its animation was playing at the last update
        unsigned int m_eventHandle;  // the object update sends the event to (registObject: the object itself)
        unsigned int m_eventParam;   // the event's first parameter (registObject: 0)
    };
    UIAnimationManager();
    virtual ~UIAnimationManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    bool registObject(unsigned int handle);  // false unless the object is an image with an animation
    // Placeholder name: 1.0.0 has nothing under this name, but in 1.0.0 the same caller
    // (gf::GfMenuObject::hookAnimationEvent, with the same first two arguments: its second and first) calls
    // ui::UIAnimationManager::changeEventHandleObject(unsigned int, unsigned int), at the same place in this unit,
    // which stores only the event handle; 3.0.1's takes a third argument (hookAnimationEvent's third). A member
    // because it walks m_list. What it does: for every node of the object handle, sets m_eventHandle and
    // m_eventParam.
    void fn_710066B148(unsigned int handle, unsigned int eventHandle, unsigned int eventParam);

    mm::mtl::IntrusiveList<ObjectNode> m_list;  // the name is not the original's
};
}  // namespace ui

#endif
