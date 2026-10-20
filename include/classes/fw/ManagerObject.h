#ifndef CLASSES_FW_MANAGEROBJECT_H
#define CLASSES_FW_MANAGEROBJECT_H

namespace fw {
// table 0x7100B41DE0
class ManagerObject {
public:
    virtual ~ManagerObject();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void enterFinalizeApplet();  // slot 4
    virtual void getName() const;  // slot 5
    virtual void isInitialized() const;  // slot 6
    virtual void isFinalized() const;  // slot 7
    unsigned char pad_8[0x8];  // fields: size from its derived classes
};
}  // namespace fw

#endif
