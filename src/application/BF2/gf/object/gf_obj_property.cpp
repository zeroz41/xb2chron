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

// GfObjPropertyDriver's, GfObjPropertyBlade's and GfObjPropertyEnemy's constructors (0x710054A958, 0x710054ABB8,
// 0x710054AE7C) are not here yet: they construct a GfTargetProperty (Driver, Blade) and fields not modelled yet.

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
