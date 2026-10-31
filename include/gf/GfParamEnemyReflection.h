#ifndef GF_GFPARAMENEMYREFLECTION_H
#define GF_GFPARAMENEMYREFLECTION_H

namespace gf {

// the rates (per second) an enemy's field move speed changes at, by the speed it leaves and the one it takes
// (GfBehaviorEnemyField::applyFieldMoveSpeed; the field names are not the original's)
struct EnemeyMoveParam {
    float pad_0;   // 0 -> 1
    float pad_4;   // 1 -> 2
    float pad_8;   // 0 -> 2
    float pad_c;   // 2 -> 1
    float pad_10;  // 1 -> 0
    float pad_14;  // 2 -> 0
};

// an enemy's movement parameter block: the index's entry of the twenty-second param list
const EnemeyMoveParam* getEnemeyMoveParam(unsigned int index);

}  // namespace gf

#endif
