#ifndef CLASSES_GMK_GMKMOBINSTS_H
#define CLASSES_GMK_GMKMOBINSTS_H

#include "mm/mtl/Vector.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace gmk {
class GmkSquad;
// the game objects a mob gimmick spawns (GmkMob holds one at 0x48; GmkMob::create and GmkRoutedMob::create/dispose
// call its functions). No table: a plain class. Size 0xd0 (GmkMob's stride 0x118 minus 0x48).
class GmkMobInsts {
public:
    // where a mob gimmick's objects pop and what to do when they do (PopInfo::update takes one; GmkMob and
    // GmkRoutedMob each derive a PopXformFinder from it, tables 0x7100B6DD60 and 0x7100B6DE98: three slots, no
    // destructor)
    class IPopXformFinder {
    public:
        virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot) const = 0;  // slot 0
        virtual void onPopGob(gf::GF_OBJ_HANDLE* handle) const = 0;  // slot 1
        virtual void onCreateGobInsts(unsigned int num) const = 0;  // slot 2
    };
    // inline (no symbol in 1.0.0 or 3.0.1): GmkMob's destructor runs dispose again after its own dispose, then
    // clears 0x90 when it is set
    ~GmkMobInsts() {
        dispose();
        if (pad_90 != nullptr) {
            pad_90 = nullptr;
        }
    }
    void dispose();
    // shows or hides one of its objects by pad_a0 (display bit 8) when the object is bound to a gimmick
    void validateDisp(gf::GF_OBJ_HANDLE* handle) const;
    void disposeGobInsts(bool);
    unsigned char pad_0[0x90];
    void* pad_90;
    // 0x98: 1 makes the pop finders pop at the gimmick's own position, else somewhere in its shape
    // (GmkMob::PopXformFinder::findPosRot)
    int pad_98;
    unsigned char pad_9c[0x4];
    bool pad_a0;  // validateDisp(handle) shows the objects while it is set
    unsigned char pad_a1[0x7];
    mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* m_gobInsts;  // 0xa8: GmkMob's game objects (the name is not the original's)
    // 0xb0: the squad its objects join; the pop finders place the objects by it while it has room (the name is not
    // the original's)
    GmkSquad* m_squad;
    unsigned char pad_b8[0x18];
};
}  // namespace gmk

#endif
