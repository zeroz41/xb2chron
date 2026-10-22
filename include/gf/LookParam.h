#ifndef GF_LOOKPARAM_H
#define GF_LOOKPARAM_H

namespace gf {

// a PC's look parameters: entry 4 of the param manager's list 5 (TargetIKPlugin's; LookAxisPlugin reads the same
// entry). The names are 1.0.0's (LookParam::createReflection registers the fields by name and offset).
struct LookParam {
    float lookAngle;           // degrees from the PC's front within which TargetIKPlugin looks at its target
    float targetMoveTime;      // TargetIKPlugin's fade and target change time
    float fadeInTime;
    float changeTargetTime;
    float fadeOutTime;
    float changeBehaviorTime;  // the time TargetIKPlugin's up and down ratios take to change
};

}  // namespace gf

#endif
