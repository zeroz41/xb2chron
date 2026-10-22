#ifndef WND_UPDATEINFO_H
#define WND_UPDATEINFO_H

namespace wnd {
// what WindWorld::update passes its winds: the time it has added up and the step it was given
class UpdateInfo {
public:
    float time;
    float deltaTime;
    unsigned char pad_8[0x4];  // fields: WindWorld::update fills it from a flag of its own
};
}  // namespace wnd

#endif
