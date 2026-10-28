#ifndef CLASSES_GMK_GMKMOBINSTS_H
#define CLASSES_GMK_GMKMOBINSTS_H

namespace gmk {
// the game objects a mob gimmick spawns (GmkMob holds one at 0x48; GmkMob::create and GmkRoutedMob::create/dispose
// call its functions). No table: a plain class. Size 0xd0 (GmkMob's stride 0x118 minus 0x48).
class GmkMobInsts {
public:
    // inline (no symbol in 1.0.0 or 3.0.1): GmkMob's destructor runs dispose again after its own dispose, then
    // clears 0x90 when it is set
    ~GmkMobInsts() {
        dispose();
        if (pad_90 != nullptr) {
            pad_90 = nullptr;
        }
    }
    void dispose();
    void disposeGobInsts(bool);
    unsigned char pad_0[0x90];
    void* pad_90;
    unsigned char pad_98[0x38];
};
}  // namespace gmk

#endif
