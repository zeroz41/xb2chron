#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/SCOM_CHAR_DEAD.h"
#include "classes/fw/UpdatableObject.h"
#include "gf/GfObjUtil.h"
#include "gf/GfTargetProperty.h"
#include "gf/GfEnvProperty.h"
#include "gf/SoundVariable.h"
#include "gf/MsgObjectFlushProperty.h"
#include "gf/MsgGameChangeTarget.h"
#include "gf/MsgObjectMaxHp.h"
#include "gf/MsgObjectSetHp.h"
#include "gf/MsgUnk_1000045.h"
#include "gf/MsgObjectDead.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/MsgObjectAlpha.h"
#include "gf/MsgObjectDamage.h"
#include "gf/MsgObjectHealHp.h"
#include "gf/MsgObjectNotifyHealHp.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfMenuObjDamageValue.h"
#include "btl/Utility.h"
#include "gf/MsgUnk_1000046.h"
#include "gf/MsgUnk_1000047.h"
#include "gf/MsgUnk_1000048.h"
#include "mm/mtl/UniquePtr.h"

namespace gf {

GfComProperty::GfComProperty() {}

GfComProperty::~GfComProperty() {}

void GfComProperty::flush() {
    GfObjPropertyCharacter* character = GfObjUtil::getProperty(static_cast<GfObj*>(m_owner)->m_handle)->m_character;
    if (character != nullptr) {
        if (GfStatusProperty* status = m_status.get()) {
            character->m_uiMaxHp = status->m_maxHp;
            character->m_uiHp = status->m_hp;
        }
        if (m_target) {
            character->pad_28 = reinterpret_cast<long>(m_target->m_target);
        }
    }
    MsgObjectFlushProperty msg;
    recieveMessage(static_cast<GfObj*>(m_owner), msg);
}

// onDead, recieveMessage, procMsgObjectDamage and procMsgObjectHealHp sit here (not matched yet)

void GfComProperty::setAlpha(unsigned int kind, float alpha) {
    if (m_alpha) {
        GfAlphaProperty* property = m_alpha.operator->();
        if (kind < 6) {
            if (property->m_alpha[kind] != alpha) {
                property->m_alpha[kind] = alpha;
                m_alpha->m_changed = true;
                m_alpha->m_total = 1.0f;
                const float* all = m_alpha->m_alpha;
                for (int i = 0; i < 6; ++i) {
                    m_alpha->m_total *= all[i];
                }
            }
        } else if (property->m_changed) {
            property->m_changed = false;
        }
    }
}
}  // namespace gf

template void mm::mtl::UniquePtr<gf::GfDebugStatusProperty, mm::mtl::UniquePtrDefaultDeleter<gf::GfDebugStatusProperty> >::_safe_bool_helper::safe_bool_function() const;

namespace gf {

mm::mtl::RTTI GfComProperty::m_rtti("GfComProperty", &GfComponent::m_rtti, nullptr);

}  // namespace gf
