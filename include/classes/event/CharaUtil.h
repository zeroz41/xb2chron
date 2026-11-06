#ifndef CLASSES_EVENT_CHARAUTIL_H
#define CLASSES_EVENT_CHARAUTIL_H

namespace gf { class GfObj; }
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace event {
// character helpers (no table; the symbols name the class and its functions)
class CharaUtil {
public:
    // whether the object's event-anim (or asm) state is the given one, or one of two
    static bool checkStat(gf::GfObj* obj, const char* stat);
    static bool checkStat(gf::GfObj* obj, const char* stat, const char* stat2);
    // whether the state name contains the text
    static bool checkStatSeries(gf::GfObj* obj, const char* stat);
    // CharaPlayActionAuto::update waits while it is true
    static bool isActionBusy(gf::GfObj* obj);
    // CharaLinerPos::update turns the gravity off
    static void setGravity(gf::GF_OBJ_HANDLE* handle, bool on);
    // out of line (0x71000D145C, not written yet); CharaObj::linerPos fits its position's height with it
    static void adjestPosY(mm::Vec3& pos, mm::Vec3*);
};
}  // namespace event

#endif
