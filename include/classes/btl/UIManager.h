#ifndef CLASSES_BTL_UIMANAGER_H
#define CLASSES_BTL_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class UIManager; }

namespace btl {
// table 0x7100B3BE28
class UIManager : public ::mm::mtl::PtrSingleton< ::btl::UIManager> {
public:
    virtual ~UIManager();  // slot 0
    static void Create();
    static void Destroy();
    // an input the battle UI is told about (GfGameTarget's selectRight sends 5, selectLeft 4; the names of the values
    // are not known)
    enum INPUT_TYPE {};
    void NotifyInput(INPUT_TYPE type, int arg);

    unsigned char pad_8[0xE8];
    // flags at 0xF0, one 32-bit storage unit (the reads narrow it to the byte at 0xF1, bit 7)
    unsigned int : 15;
    // GfGameTarget's changeMode, selectRight/selectLeft and startNearTarget test it (the name is not the original's)
    unsigned int pad_bit15 : 1;
    unsigned int : 16;
};
}  // namespace btl

#endif
