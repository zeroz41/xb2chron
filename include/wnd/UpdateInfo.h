#ifndef WND_UPDATEINFO_H
#define WND_UPDATEINFO_H

namespace wnd {
// what WindWorld::update passes its winds: the time it has added up and the step it was given
class UpdateInfo {
public:
    float time;
    float deltaTime;
    // WindWorld::update copies WindWorld::setDebugMode's flag (a word store of the flag's byte); 1.0.0's
    // Dispatcher::dispatchAll tests bit 0 and takes no area wind while it is set (the name is not the original's)
    unsigned int debugMode : 1;
    // the rest of the word: WindWorld::update's initialization stores the whole word (a byte store would do for
    // the flag alone), so the flags fill it; unknown
    unsigned int pad_8 : 31;
};
}  // namespace wnd

#endif
