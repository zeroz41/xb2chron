#ifndef CLASSES_FW_WINDPROBE_H
#define CLASSES_FW_WINDPROBE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }
namespace wnd { class Transform; }
namespace wnd { class WindProbe; }

namespace fw {
// table 0x7100B43538; counted (its constructor clears the count at 8). A point that feels the wind: it keeps a
// wndlib probe where its frame is. Its list node base is what WindManager's probe list links.
class WindProbe : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNodeBase {
public:
    WindProbe(unsigned int capacity, float radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame, bool isMain);
    virtual ~WindProbe();  // slot 0
    void update();

    wnd::WindProbe* m_pProbe;  // the constructor's, referenced; the destructor releases it
    mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;  // where the probe is: m_radius up from its world origin
    // the probe's sphere's radius (0.01 when not above zero) and its height above the frame
    float m_radius;
    bool m_isMain;  // WindManager::addProbe keeps a reference to the last such probe added
};
}  // namespace fw

#endif
