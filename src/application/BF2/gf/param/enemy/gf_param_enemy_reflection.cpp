#include "gf/GfParamEnemyReflection.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"

namespace gf {

const EnemeyMoveParam* getEnemeyMoveParam(unsigned int index) {
    return fw::ParamManager::get()->m_paramLists[21]->getAdapter(index).get<EnemeyMoveParam>();
}

}  // namespace gf
