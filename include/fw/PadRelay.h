#ifndef FW_PADRELAY_H
#define FW_PADRELAY_H

namespace fw {

// a pad's named actions and axes, bound to handlers (no table): PadBattle holds two, PadField one
class PadRelay {
public:
    PadRelay();
    ~PadRelay();

    alignas(8) unsigned char pad_0[0x38];  // fields: PadBattle's layout (relays at 0x8 and 0x40) gives the size
};

}  // namespace fw

#endif
