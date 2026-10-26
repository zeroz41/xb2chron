#ifndef CLASSES_GF_GFFIELDLOCALSTEER_H
#define CLASSES_GF_GFFIELDLOCALSTEER_H

#include "classes/gf/TGfTween.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class GmkRouteNavi; }
namespace mm { class Vec3; }
namespace navi { class NvmshAcObj; }

namespace gf {
// a class with no table: an object's local steering (gf_game_stuck_meter's unit). 0x5060 bytes (GfComBehaviorMob
// holds one at 0x2C0, its TIsTargetNotSameSquad right after it)
class GfFieldLocalSteer {
public:
    // what create takes; the class keeps a copy (create copies it whole). Defaults from dispose
    struct CreateInfo {
        CreateInfo() : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_8(2.0f), pad_c(1.0f), pad_10(0.5f),
                       pad_14(true), pad_18(nullptr) {}
        GF_OBJ_HANDLE* m_handle;  // -1 without one
        float pad_8;
        float pad_c;
        float pad_10;
        bool pad_14;
        void* pad_18;
    };
    class UpdateInfo;
    template <typename T>
    class TIsTargetNotSameSquad;
    GfFieldLocalSteer(const CreateInfo* info);
    void create(const CreateInfo& info);
    void dispose();
    // whether it has an object and pad_24 (seconds, as the 5.0 limit reads) passed 5
    bool isTimeOutCollide() const;
    // the steering angle: the tween's value (the name is getCurAngle's)
    float getCurAngle() const;

    CreateInfo m_info;
    bool pad_20;
    float pad_24;
    TGfTween<float> m_angle;  // getCurAngle's value; create resets it to 0
    unsigned char pad_40[0x5000];
    void* pad_5040;
    unsigned char pad_5048[0x8];
    int pad_5050;
    bool pad_5054;
    unsigned char pad_5055[0xB];
};

// whether the navigation object holds a move vector to read (flag bit 1, state 1)
bool canGetMoveVec(const navi::NvmshAcObj* obj);
// the navigation object's move vector into out when canGetMoveVec; returns whether it did
bool getMoveVec(mm::Vec3& out, const navi::NvmshAcObj* obj);
}  // namespace gf

#endif
