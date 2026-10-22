#ifndef MM_VEC2_H
#define MM_VEC2_H

namespace mm {

// two floats in 16 bytes on a 16-byte boundary, like Vec3: UIObjectSyncPlugin::execute's frame gives its scale
// (UIObjectAcc::getScale/setScale) a 16-byte slot that the 4-byte locals there share
class Vec2 {
public:
    float x;
    float y;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
