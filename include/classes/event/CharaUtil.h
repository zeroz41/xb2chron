#ifndef CLASSES_EVENT_CHARAUTIL_H
#define CLASSES_EVENT_CHARAUTIL_H

namespace gf { class GfObj; }
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// character helpers (no table; the symbols name the class and its functions)
class CharaUtil {
public:
    // out of line (0x71000D1094, not written yet); CharaPlayActionAuto::update waits while it is true
    static bool isActionBusy(gf::GfObj* obj);
    // out of line (0x71000D1560, not written yet); CharaLinerPos::update turns the gravity off
    static void setGravity(gf::GF_OBJ_HANDLE* handle, bool on);
};
}  // namespace event

#endif
