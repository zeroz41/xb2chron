#ifndef CLASSES_EVENT_RANDUTIL_H
#define CLASSES_EVENT_RANDUTIL_H

#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
class Object;

// helpers of the random talk players (no table)
class RandUtil {
public:
    // the event object with the id (RandPlayer::Wait::update tests its kind for 2, a character, before reading it as an
    // ObjectChara)
    static Object* searchByID(int id);
    // the position of the character holding the handle raised by its eye height (CharaObj 0x1730), or zero
    static mm::Vec3 getEyePos(gf::GF_OBJ_HANDLE* handle);
};
}  // namespace event

#endif
