#ifndef CLASSES_EVENT_SCHEDULEITEM_H
#define CLASSES_EVENT_SCHEDULEITEM_H

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3D540
// One fade step of an object a Scheduler drives (Scheduler::m_item): Scheduler::exec calls m_func with m_handle
// every frame while the object exists (the field names are not the original's)
class ScheduleItem {
public:
    typedef void (ScheduleItem::*Func)(gf::GF_OBJ_HANDLE*);
    // ScheManager::push's (inline: no symbol): the object's handle, no step, fully visible
    explicit ScheduleItem(gf::GF_OBJ_HANDLE* handle) : m_handle(handle), m_func(), m_alpha(1.0f) {}
    virtual ~ScheduleItem() {}  // slot 0
    void clear();
    void func_fadeout(gf::GF_OBJ_HANDLE* handle);
    void func_fadein(gf::GF_OBJ_HANDLE* handle);
    void func_fadewait(gf::GF_OBJ_HANDLE* handle);

    gf::GF_OBJ_HANDLE* m_handle;  // the object faded (ScheManager::push copies the Scheduler's)
    Func m_func;                  // the step exec calls next, none once done
    float m_alpha;                // 1.0 or 0.0: where the fade starts (func_fadeout/func_fadein)
};
}  // namespace event

#endif
