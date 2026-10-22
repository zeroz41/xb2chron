#ifndef ANM_UTIL_H
#define ANM_UTIL_H

namespace anm { class Binding; }

namespace anm {
class Util {
public:
    // how long the binding's animation plays
    static float getPlayBackTime(const Binding& binding);
};
}  // namespace anm

#endif
