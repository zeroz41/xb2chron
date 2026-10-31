#ifndef CLASSES_EVENT_RESPACK_H
#define CLASSES_EVENT_RESPACK_H

#include "classes/event/IResPackEvent.h"
#include "classes/fw/RenderResource.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace event {
// table 0x7100B3C058
class ResPack {
public:
    // out of line, the key function: D2/D0 sit before draw (0x71000B87A0)
    virtual ~ResPack();  // slot 0
    void draw();
    void load(mtl::ALLOC_HANDLE handle, const char* name, IResPackEvent* event);
    void func_loading();

    mtl::ALLOC_HANDLE m_handle;  // @0x8: load's; the name is not the original's
    mm::mtl::FixStr<128> m_name;  // @0xc, length @0x8c: load's name; the name is not the original's
    IResPackEvent* m_event;  // @0x90: load's listener; the name is not the original's
    void (ResPack::*m_func)();  // @0x98: load sets func_loading; the name is not the original's
    fw::RenderResource* m_res;  // @0xa8: fw::RenderResource::request's; the name is not the original's
};
}  // namespace event

#endif
