#ifndef CLASSES_EVENT_RANDUTIL_H
#define CLASSES_EVENT_RANDUTIL_H

namespace event {
class Object;

// helpers of the random talk players (no table)
class RandUtil {
public:
    // the event object with the id (RandPlayer::Wait::update tests its kind for 2, a character, before reading it as an
    // ObjectChara)
    static Object* searchByID(int id);
};
}  // namespace event

#endif
