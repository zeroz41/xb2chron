#ifndef GF_CALLBACKCACHE_H
#define GF_CALLBACKCACHE_H

#include "anm/AsmListener.h"

namespace gf {
// an animation event as GfComAsm::executeCallback hands it to its callbacks (it keeps them 0x10 apart)
class CallBackCache {
public:
    // (inline: GfComAsm::AsmLisener::callback queues one per annotation; the names are not the original's)
    CallBackCache(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion* event) : m_type(type), m_event(event) {}

    anm::AsmListener::CallBackType m_type;  // the listener callback's
    // executeCallback picks the callback by its name; the callbacks compare the name with the events they know
    // ("salvageStep", "vibration"), and GfComBehavior::callbackAnim hands it on as MsgObjectNotifyAsmCallback's
    // annotation and reads its text ("ikEvent")
    const anm::AsmAnnotetion* m_event;
};
}  // namespace gf

#endif
