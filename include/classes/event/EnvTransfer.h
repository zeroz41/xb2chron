#ifndef CLASSES_EVENT_ENVTRANSFER_H
#define CLASSES_EVENT_ENVTRANSFER_H

namespace gf { enum WEATHERID : int; }

namespace event {
// the base of EnvTransferEvent and EnvTransferField: both tables hold ~EnvTransfer (0x710014C3A0) in slot 0; the
// original emits no table of its own. EnvManager's constructor stores both derived tables after these fields, so they
// are the base's
class EnvTransfer {
public:
    EnvTransfer() : m_hour(0), m_min(0), m_weatherID((gf::WEATHERID)1) {}
    virtual ~EnvTransfer() {}  // slot 0
    // applies the time and weather to the field (when it has a clock) and the cloud sea to EnvManager
    void load();
    unsigned int m_hour;  // 0x8 (the name is not the original's)
    unsigned int m_min;  // 0xc (the name is not the original's)
    gf::WEATHERID m_weatherID;  // 0x10 (the name is not the original's)
    // not set by the constructor; EnvManager::login stores the current cloud sea
    int m_cloudSea;  // 0x14 (the name is not the original's)
};
}  // namespace event

#endif
