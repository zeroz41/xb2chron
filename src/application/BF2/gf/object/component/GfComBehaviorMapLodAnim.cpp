#include "gf/PluginManager.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfComBehaviorMapLodAnim.h"

namespace gf {

void GfComBehaviorMapLodAnim::update(fw::UpdateInfo const& info) {
    GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(17) || acc.getObj() == nullptr) {
        return;
    }
    GfFieldLodColiAnim::PosInfo* posInfo = static_cast<GfFieldLodColiAnim::PosInfo*>(acc.getUserData(GfObjUserData(1)));
    if (posInfo != nullptr) {
        posInfo->update(info);
    }
}

mm::mtl::RTTI GfComBehaviorMapLodAnim::m_rtti("GfComBehaviorMapLodAnim", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf
