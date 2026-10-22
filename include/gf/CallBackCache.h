#ifndef GF_CALLBACKCACHE_H
#define GF_CALLBACKCACHE_H

namespace anm { class AsmAnnotetion; }

namespace gf {
// an animation event as GfComAsm::executeCallback hands it to its callbacks (it keeps them 0x10 apart)
class CallBackCache {
public:
    unsigned char pad_0[8];
    // executeCallback picks the callback by its name; the callbacks compare the name with the events they know
    // ("salvageStep", "vibration"), and GfComBehavior::callbackAnim hands it on as MsgObjectNotifyAsmCallback's
    // annotation and reads its text ("ikEvent")
    const anm::AsmAnnotetion* m_event;
};
}  // namespace gf

#endif
