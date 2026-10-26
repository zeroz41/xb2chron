#ifndef CLASSES_GF_GFFIELDLOCALSTEER_H
#define CLASSES_GF_GFFIELDLOCALSTEER_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a class with no table: an object's local steering (gf_game_stuck_meter's unit). 0x5060 bytes (GfComBehaviorMob
// holds one at 0x2C0, its TIsTargetNotSameSquad right after it)
class GfFieldLocalSteer {
public:
    class CreateInfo;
    template <typename T>
    class TIsTargetNotSameSquad;
    GfFieldLocalSteer(const CreateInfo* info);
    // the steering angle: blended from pad_30 to pad_34 by pad_3c / pad_38 (the name is getCurAngle's)
    float getCurAngle() const;
    // execTurnCmdToPos asks getCurAngle only while it is not -1
    GF_OBJ_HANDLE* pad_0;
    unsigned char pad_8[0x5058];
};
}  // namespace gf

#endif
