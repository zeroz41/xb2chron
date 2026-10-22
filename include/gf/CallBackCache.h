#ifndef GF_CALLBACKCACHE_H
#define GF_CALLBACKCACHE_H

namespace gf {
// an animation event as GfComAsm::executeCallback hands it to its callbacks (it keeps them 0x10 apart)
class CallBackCache {
public:
    struct Event {
        const char* name;  // the callbacks compare it with the events they know ("salvageStep", "vibration")
    };

    unsigned char pad_0[8];
    const Event* m_event;  // executeCallback picks the callback by its name
};
}  // namespace gf

#endif
