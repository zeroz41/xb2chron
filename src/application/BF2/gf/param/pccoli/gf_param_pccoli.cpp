#include "gf/GfParamPcColi.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"

namespace gf {

const PcColiParameter* getPcColiParameter() {
    return fw::ParamManager::get()->m_paramLists[17]->getAdapter(0).get<PcColiParameter>();
}

}  // namespace gf
