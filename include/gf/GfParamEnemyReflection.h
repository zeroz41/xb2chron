#ifndef GF_GFPARAMENEMYREFLECTION_H
#define GF_GFPARAMENEMYREFLECTION_H

namespace gf {

struct EnemeyMoveParam;

// an enemy's movement parameter block: the index's entry of the twenty-second param list
const EnemeyMoveParam* getEnemeyMoveParam(unsigned int index);

}  // namespace gf

#endif
