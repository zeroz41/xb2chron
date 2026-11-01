#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyBelonging.h"
#include "classes/gf/GfObjPropertyBlade.h"
#include "classes/gf/GfObjPropertyDriver.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "classes/gf/GfObjPropertyEnWeapon.h"
#include "classes/gf/GfObjPropertyEvent.h"
#include "classes/gf/GfObjPropertyExtra.h"
#include "classes/gf/GfObjPropertyFobj.h"
#include "classes/gf/GfObjPropertyGimmick.h"
#include "classes/gf/GfObjPropertyMap.h"
#include "classes/gf/GfObjPropertyMob.h"
#include "classes/gf/GfObjPropertyNpc.h"
#include "classes/gf/GfObjPropertyPcWeapon.h"
#include "classes/gf/GfObjPropertyUi.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfObjUtil.h"

namespace gf {

GfObjProperty* GfObjProperty::create(GF_OBJ_HANDLE* handle) {
    GfObjProperty* property = nullptr;
    switch (GfObjUtil::getObjType(handle)) {
    case 1:
#line 26
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyMap(handle);
        break;
    case 3:
#line 28
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyDriver(handle);
        break;
    case 4:
#line 30
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyBlade(handle);
        break;
    case 5:
#line 32
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyEnemy(handle);
        break;
    case 6:
#line 34
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyNpc(handle);
        break;
    case 7:
#line 36
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyMob(handle);
        break;
    case 8:
#line 38
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyGimmick(handle);
        break;
    case 9:
#line 40
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyFobj(handle);
        break;
    case 10:
#line 42
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyPcWeapon(handle);
        break;
    case 11:
#line 44
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyEvent(handle);
        break;
    case 12:
#line 46
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyEnWeapon(handle);
        break;
    case 13:
#line 48
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyBelonging(handle);
        break;
    case 14:
#line 50
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyExtra(handle);
        break;
    case 15:
#line 52
        property = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjPropertyUi(handle);
        break;
    }
    return property;
}

GfObjPropertyDriver::GfObjPropertyDriver(GF_OBJ_HANDLE* handle)
    : GfObjProperty(handle, &m_characterPart, &m_targetPart) {
    m_characterPart.reset();
    pad_190 = 0;
    pad_198 = 0;
    pad_1A0 = 0;
}

GfObjPropertyBlade::GfObjPropertyBlade(GF_OBJ_HANDLE* handle)
    : GfObjProperty(handle, &m_characterPart, &m_targetPart), pad_190(0),
      pad_194{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, m_comboReady(0) {
    m_characterPart.reset();
    pad_190 = 0;
    // the body sets the 14 bytes again as one loop (its stores are not the initializer's: 0x1A0 is one halfword)
    for (int i = 0; i < 0xE; i++) {
        pad_194[i] = i % 6 == 0;
    }
    m_kizuna = 0;
    m_specialLv = 0;
    m_specialGauge = 0.0f;
    m_changeRecast = 0.0f;
}

GfObjPropertyEnemy::GfObjPropertyEnemy(GF_OBJ_HANDLE* handle) : GfObjProperty(handle, &m_characterPart) {
    m_characterPart.reset();
    pad_150 = 0;
    pad_154 = false;
    pad_155 = false;
    pad_C0 = 0;
    m_scout = false;
    pad_C3 = 0;
    m_artsId = 0;
    pad_C8 = 0;
    pad_D0 = 0;
    m_weakAttr = 0;
    m_elementComboId = 0;
    m_elementComboTime = 0.0f;
    m_elementComboSuspend = false;
    m_elementComboLv = 0;
    m_fightCombo = 0;
    m_fightComboTime = 0.0f;
    m_fightComboSuspend = false;
    m_elemEffId = 0;
    for (int i = 0; i < 9; i++) {
        m_resAttrs[i].m_flags = 0;
        m_resAttrs[i].m_level = 0;
    }
}

GfObjPropertyCharacter::GfObjPropertyCharacter() {
    memset(&m_uiMaxHp, 0, 0xE);  // m_uiMaxHp to pad_C
    pad_28 = -1;
    pad_30 = false;
    unsigned char* fp = Bdat::getFP("BTL_Buff");
    if (fp != nullptr && Bdat::getIdCount(fp) != 0) {
        m_buffs.setAllocator(getAllocator(ALLOCATOR(0)));
        m_buffs.reserve(Bdat::getIdCount(fp));
        reset();
    }
}

GfObjPropertyDriver* GfObjProperty::getDriver() {
    return GfObjUtil::getObjType(m_handle) == 3 ? static_cast<GfObjPropertyDriver*>(this) : nullptr;
}

GfObjPropertyBlade* GfObjProperty::getBlade() {
    return GfObjUtil::getObjType(m_handle) == 4 ? static_cast<GfObjPropertyBlade*>(this) : nullptr;
}

GfObjPropertyEnemy* GfObjProperty::getEnemy() {
    return GfObjUtil::getObjType(m_handle) == 5 ? static_cast<GfObjPropertyEnemy*>(this) : nullptr;
}

}  // namespace gf
