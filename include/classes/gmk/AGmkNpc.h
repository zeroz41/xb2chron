#ifndef CLASSES_GMK_AGMKNPC_H
#define CLASSES_GMK_AGMKNPC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B719F8
class AGmkNpc {
public:
    virtual ~AGmkNpc() {}  // slot 0
    virtual bool isPopCondMatched() const = 0;  // slot 2
    virtual void isDepopCondMatched() const = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual void getBindedBdatFp() const = 0;  // slot 6
    virtual void getBindedBdatId() const = 0;  // slot 7
    // true when it found them (GmkNpc's returns 1; LocatorTalk_NpcID::update tests it)
    virtual bool findPopPosRot(mm::Vec3& pos, mm::Vec3& rot) const = 0;  // slot 8
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;  // slot 9
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;  // slot 10
    virtual void validateDisp() const = 0;  // slot 11
    virtual void debugUpdate(float) {}  // slot 12
};
}  // namespace gmk

#endif
