#ifndef BTL_MISC_H
#define BTL_MISC_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace btl {

// the battle code's vector helpers (1.0.0's btl::Misc; 3.0.1 keeps the ones below in battle/Misc.cpp)
class BattleCharacter;
namespace Misc {
// whether chr is within range of pos (EnemyParameter::AngryInfection passes its character's position, the
// candidate, the candidate's radius plus its range, and false)
bool CheckInRange(const mm::Vec3& pos, BattleCharacter* chr, float range, bool flag);

// which way GetCrossDirection turns: 0 one side, any other the opposite (the names are not the original's)
enum CROSS_MODE {
    CROSS_MODE_0 = 0,
};

// v to length 1: a zero one becomes unitZ, a tiny one is scaled up first, one still too short becomes zero
void Normalize(mm::Vec3& v);
// dir turned toward target by up to angle (radians) about their common normal; one within angle (and not force)
// becomes target. The angle between them, or angle when turned
float TurnDirectionAngle(mm::Vec3& dir, const mm::Vec3& target, float angle, bool force);
// the direction from from to to, false (and zero) when they are within 1e-6 of each other
bool CalcDirection(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out);
// v turned a quarter about the Y axis in the XZ plane
void GetCrossDirection(const mm::Vec3& v, mm::Vec3& out, CROSS_MODE mode);
// the direction a rotation turns unitZ to
void GetPostureDirection(const mm::Quat& q, mm::Vec3& out);
// the angle between two directions; signed, negative when b lies the other way about the Y axis
float CalcAngle(const mm::Vec3& a, const mm::Vec3& b, bool isSigned);
// the angle of v about the Y axis from unitZ
float CalcRotY(const mm::Vec3& v);

}  // namespace Misc

}  // namespace btl

#endif
