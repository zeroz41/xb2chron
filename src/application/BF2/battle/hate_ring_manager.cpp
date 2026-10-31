#include "classes/btl/HateRingManager.h"

namespace btl {

HateRingManager::~HateRingManager() {}

void HateRingManager::PreUpdate(const fw::UpdateInfo&) {}

void HateRingManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

unsigned char HateRingManager::fn_71000A1DB8(int index) const {
    return pad_112C[index];
}

unsigned int HateRingManager::fn_71000A1DC8() const {
    unsigned int packed = 0;
    for (int i = 0; i < 3; i++) {
        packed |= pad_112C[i] << (i * 10);
    }
    return packed;
}

}  // namespace btl
