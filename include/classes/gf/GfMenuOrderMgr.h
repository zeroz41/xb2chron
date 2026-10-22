#ifndef CLASSES_GF_GFMENUORDERMGR_H
#define CLASSES_GF_GFMENUORDERMGR_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuOrderMgr; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5EE88
class GfMenuOrderMgr : public ::mm::mtl::PtrSingleton< ::gf::GfMenuOrderMgr> {
public:
    virtual ~GfMenuOrderMgr();  // slot 0
    // queues the event for the handle on that order channel; finishOrder ends the channel's current one
    static void setOrder(int channel, unsigned int handle, const ui::EventData& event);
    static void finishOrder(int channel);
    static void cancelOrder(int channel);
};
}  // namespace gf

#endif
