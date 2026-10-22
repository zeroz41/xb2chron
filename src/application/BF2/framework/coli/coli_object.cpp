#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiUserData.h"
#include "classes/fw/ColiObjUserData.h"

namespace fw {

void ColiObject::update() {}

mm::mtl::RTTI ColiObject::m_rtti("ColiObject", nullptr, nullptr);
mm::mtl::RTTI ColiObjUserData::m_rtti("ColiObjUserData", &ColiUserData::m_rtti, nullptr);

}  // namespace fw
