#ifndef FW_PADRELAY_H
#define FW_PADRELAY_H

namespace fw {

// (functions, by its symbols)
class PadRelayUtil {
public:
    // the framework pad key a named input is bound to on a pad: whether it is bound (StateUtil asks pads 0-4; it
    // passes 0 for the two middle arguments, whose roles are not known)
    static bool getFwPadKey(unsigned int pad, const char* name, unsigned int, unsigned int, unsigned int* pKey);
};

// a pad's named actions and axes, bound to handlers (no table): PadBattle holds two, PadField one
class PadRelay {
public:
    PadRelay();
    ~PadRelay();

    alignas(8) unsigned char pad_0[0x38];  // fields: PadBattle's layout (relays at 0x8 and 0x40) gives the size
};

}  // namespace fw

#endif
