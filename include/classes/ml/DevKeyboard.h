#ifndef CLASSES_ML_DEVKEYBOARD_H
#define CLASSES_ML_DEVKEYBOARD_H

#include "classes/ml/DevBase.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// the development keyboard; 3.0.1 has no table of its own (no instance is created), only its static functions and
// PtrSingleton<DevKeyboard>'s instance. Bases as every device's (DevBase, then its PtrSingleton at 0x1B0): the fields
// its static functions reach start at 0x1B8
class DevKeyboard : public ::ml::DevBase, public ::mm::mtl::PtrSingleton<DevKeyboard> {
public:
    // named by the symbols: the keys held (the low word of the field at 0x1C0); 0 with no object
    static unsigned int getVkHold();
    // FrameworkLauncher::destroy calls it with no object once the launcher is done
    static void clearKey();

    unsigned long pad_1b8;
    unsigned long m_vkHold;  // 0x1C0 (getVkHold reads it; clearKey clears it)
    unsigned long pad_1c8;
    unsigned char pad_1d0[0x80];
    unsigned long pad_250;
    unsigned long pad_258;
};
}  // namespace ml

#endif
