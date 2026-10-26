#ifndef CLASSES_BTL_SHAKECAMERAMANAGER_H
#define CLASSES_BTL_SHAKECAMERAMANAGER_H

#include "classes/btl/ShakeCameraElement.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }

namespace btl {
// the battle camera's shakes: up to 20 at once (a new one past that drops the oldest); it owns them and deletes
// each when it ends. The field names are not the original's.
// table 0x7100B3BCA0
class ShakeCameraManager {
public:
    ShakeCameraManager();
    virtual ~ShakeCameraManager();  // slot 0
    void RegisterData(ShakeCameraElement* element);
    void Update(const fw::UpdateInfo& info);
    void ApplyShake(mm::Vec3& pos, mm::Vec3& target);

    mm::mtl::FixedVector<ShakeCameraElement*, 20> m_elements;  // 0x8
    bool m_stopEternalShake;                                   // 0xB0: stops each element's eternal shake next Update
};

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function of namespace btl: it sits in
// ShakeCameraManager's unit and reads no object. What it does: returns the number of set bits of its argument (a
// 32-bit population count); Utility::fn_71000126C0 passes CharacterParameter::pad_5d8, EnemyParameter::fn_71000865AC
// calls it too.
unsigned int fn_71000A2B74(unsigned int bits);
}  // namespace btl

#endif
