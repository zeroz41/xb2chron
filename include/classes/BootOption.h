#ifndef CLASSES_BOOTOPTION_H
#define CLASSES_BOOTOPTION_H

// table 0x7100B72020
class BootOption {
public:
    virtual ~BootOption();  // slot 0

    unsigned char pad_8[0x9600];
    // the destructor clears it when it is set (the type and name are not the original's)
    void* pad_9608;
};

#endif
