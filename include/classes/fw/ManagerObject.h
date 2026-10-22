#ifndef CLASSES_FW_MANAGEROBJECT_H
#define CLASSES_FW_MANAGEROBJECT_H

namespace fw {
// table 0x7100B41DE0
class ManagerObject {
public:
    virtual ~ManagerObject();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void enterFinalizeApplet();  // slot 4
    virtual const char* getName() const;  // slot 5: the manager's name (SensorManager's returns "SensorManager")
    virtual bool isInitialized() const;  // slot 6
    virtual bool isFinalized() const;  // slot 7
    ManagerObject();  // registers it with ManagerRegister
    // bit 0: initialize succeeded, bit 1: finalize succeeded (ManagerRegister's initialize and finalize set them);
    // the name is not the original's
    unsigned int m_flags;
    unsigned char pad_c[0x4];
};
}  // namespace fw

#endif
