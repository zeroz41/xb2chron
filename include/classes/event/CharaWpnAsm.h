#ifndef CLASSES_EVENT_CHARAWPNASM_H
#define CLASSES_EVENT_CHARAWPNASM_H

#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3CB18
class CharaWpnAsm {
public:
    virtual ~CharaWpnAsm();  // slot 0
    unsigned int pad_8;  // 0x8: flags update tests
    unsigned char pad_c[0x1c];
    // execCmd (0x71000E0928) pushes motion numbers, update clears them (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 8> m_mots;  // 0x28 (count at 0x48)
    unsigned int pad_50;  // 0x50: update sets 1
};
}  // namespace event

#endif
