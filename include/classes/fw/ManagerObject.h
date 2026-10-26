#ifndef CLASSES_FW_MANAGEROBJECT_H
#define CLASSES_FW_MANAGEROBJECT_H

namespace fw {
// table 0x7100B41DE0
class ManagerObject {
public:
    virtual ~ManagerObject();  // slot 0
    // inline: 3.0.1 keeps anim_manager.cpp's copies (0x710015A06C on)
    virtual bool initialize() { return true; }  // slot 2
    virtual bool finalize() { return true; }  // slot 3
    virtual void enterFinalizeApplet() {}  // slot 4
    // slot 5: the manager's name (SensorManager's returns "SensorManager"); inline: 3.0.1 keeps one copy, in
    // coli_manager.cpp (0x71001677C4, after ColiManager's functions), which returns "undefined"
    virtual const char* getName() const { return "undefined"; }
    virtual bool isInitialized() const { return m_flags & 1; }  // slot 6
    virtual bool isFinalized() const { return (m_flags >> 1) & 1; }  // slot 7
    ManagerObject();  // registers it with ManagerRegister
    // bit 0: initialize succeeded, bit 1: finalize succeeded (ManagerRegister's initialize and finalize set them);
    // the name is not the original's
    unsigned int m_flags;
    unsigned char pad_c[0x4];
};
}  // namespace fw

#endif
