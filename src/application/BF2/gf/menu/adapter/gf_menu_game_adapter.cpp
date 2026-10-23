#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfItemBox.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataUtil.h"
#include "gf/GfGameUtilCloudSea.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuItemUtil.h"
#include "ui/UIStr.h"
#include "ui/uiDateTime.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (time, number, image index, text, disp)
static GfMenuGameAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuGameAdapter::update_GamePlayTime, {7, 7, 0}},
    {&GfMenuGameAdapter::update_Money, {0, 0, 999999999}},
    {&GfMenuGameAdapter::update_FieldTime, {7, 6, 0}},
    {&GfMenuGameAdapter::update_WeatherIcon, {1, 0, 0}},
    {&GfMenuGameAdapter::update_CloudIcon, {1, 0, 0}},
    {&GfMenuGameAdapter::update_MapName, {2, 0, 0}},
    {&GfMenuGameAdapter::update_LocationName, {2, 0, 0}},
    {&GfMenuGameAdapter::update_TimeZoneName, {2, 0, 0}},
    {&GfMenuGameAdapter::update_TimeZoneIcon, {1, 0, 0}},
    {&GfMenuGameAdapter::update_ReferenceNum, {0, 0, 99999}},
    {&GfMenuGameAdapter::update_MercenariesName, {2, 0, 0}},
    {&GfMenuGameAdapter::update_MercenariesLv, {0, 0, 5}},
    {&GfMenuGameAdapter::update_MercenariesPoint, {0, 0, 99999}},
    {&GfMenuGameAdapter::update_MercenariesPointMax, {0, 0, 99999}},
    {&GfMenuGameAdapter::update_RealYear, {7, 1, 0}},
    {&GfMenuGameAdapter::update_RealTime, {7, 6, 0}},
    {&GfMenuGameAdapter::update_Chapter, {0, 1, 99}},
    {&GfMenuGameAdapter::update_DispAccess, {3, 0, 0}},
    {&GfMenuGameAdapter::fn_710033E76C, {1, 0, 0}},
    {&GfMenuGameAdapter::fn_710033E7CC, {0, 0, 999}},
    {&GfMenuGameAdapter::fn_710033E840, {0, 0, 999}},
};

// the body stores the table (an empty one would not): a statement the build compiles away
GfMenuGameAdapter::~GfMenuGameAdapter() {
    ;
}

GfMenuGameAdapter* GfMenuGameAdapter::create(unsigned int handle, unsigned int type, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 88
    GfMenuGameAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuGameAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    plugin->release();
    return adapter;
}

bool GfMenuGameAdapter::update_GamePlayTime() {
    GfFieldTime* fieldTime = GfFieldTime::get();
    if (fieldTime != nullptr) {
        ElapseTime time = fieldTime->getElapseTime();
        if (time.hour > 999) {
            time.hour = 999;
            time.min = 59;
            time.sec = 59;
        }
        setElapseTime(time);
    }
    return true;
}

bool GfMenuGameAdapter::update_Money() {
    setNumber(GfDataUtil::getMoney());
    return true;
}

bool GfMenuGameAdapter::update_FieldTime() {
    ui::uiDateTime time = {};
    GfFieldTime* fieldTime = GfFieldTime::get();
    if (fieldTime != nullptr) {
        time.hour = fieldTime->getHour();
        time.minute = fieldTime->getMin();
    }
    setTime(time);
    return true;
}

bool GfMenuGameAdapter::update_WeatherIcon() {
    setNumber(GfMenuBdat::getIconImageIndex(GfMenuBdat::getIconIDFromWeatherType(GfFieldWeather::getCurrentWtrType(false))));
    return true;
}

bool GfMenuGameAdapter::update_CloudIcon() {
    setNumber(GfGameUtilCloudSea::getCloudSea() == 0);
    return GfGameManager::getMapID() == 6 || GfGameManager::getMapID() == 10;
}

bool GfMenuGameAdapter::update_MapName() {
    const char* name = GfFieldManager::getMapName();
    if (name == nullptr) {
        return false;
    }
    ui::UIStr text(name, false);
    setText(text);
    return true;
}

bool GfMenuGameAdapter::update_LocationName() {
    unsigned char* bdat;
    int id;
    if (!GfFieldManager::getLandmarkNameId(bdat, id)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuGameAdapter::update_TimeZoneName() {
    unsigned char* bdat;
    unsigned int id;
    GfFieldTime* fieldTime = GfFieldTime::get();
    if (fieldTime != nullptr && !fieldTime->getTimeRangeName(bdat, id)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuGameAdapter::update_TimeZoneIcon() {
    GfFieldTime* fieldTime = GfFieldTime::get();
    if (fieldTime == nullptr) {
        return false;
    }
    setNumber(fieldTime->getTimeRange());
    return true;
}

bool GfMenuGameAdapter::update_ReferenceNum() {
    int number = GfMenuReference::getReferenceNumber(m_referenceIndex);
    setNumber(number);
    return number >= GfMenuReference::getReferenceNumberMin(m_referenceIndex) &&
           number <= GfMenuReference::getReferenceNumberMax(m_referenceIndex);
}

bool GfMenuGameAdapter::update_MercenariesName() {
    ui::UIStr text("Mercenaries", false);
    setText(text);
    return true;
}

bool GfMenuGameAdapter::update_MercenariesLv() {
    setNumber(GfDataMercenaries::getLevel());
    return true;
}

bool GfMenuGameAdapter::update_MercenariesPoint() {
    if (GfDataMercenaries::getLevel() == 5) {
        setNumber(0);
    } else {
        setNumberMax(GfDataMercenaries::getPointMax());
        setNumber(GfDataMercenaries::getPoint());
    }
    return true;
}

bool GfMenuGameAdapter::update_MercenariesPointMax() {
    setNumberMax(GfDataMercenaries::getPointMax());
    setNumber(GfDataMercenaries::getPointMax());
    return true;
}

bool GfMenuGameAdapter::update_RealYear() {
    RealTime realTime = {};
    GfFieldTime::get()->getRealTime(realTime);
    ui::uiDateTime time = {};
    time.year = realTime.year;
    time.month = realTime.month;
    time.day = realTime.day;
    setTime(time);
    return true;
}

bool GfMenuGameAdapter::update_RealTime() {
    RealTime realTime = {};
    GfFieldTime::get()->getRealTime(realTime);
    ui::uiDateTime time = {};
    time.hour = realTime.hour;
    time.minute = realTime.minute;
    setTime(time);
    return true;
}

bool GfMenuGameAdapter::update_Chapter() {
    setNumber(GfGameManager::getScenarioId());
    setNumberMax(10);
    return true;
}

bool GfMenuGameAdapter::update_DispAccess() {
    return GfGameManager::isPlaySequenceClear();
}

bool GfMenuGameAdapter::fn_710033E76C() {
    unsigned int type = GfMenuReference::fn_710036934C();
    if (type < 1 || type > 20) {
        return false;
    }
    unsigned int number;
    if (!GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(type), 0, number, false)) {
        return false;
    }
    setNumber(number);
    return true;
}

bool GfMenuGameAdapter::fn_710033E7CC() {
    unsigned int type = GfMenuReference::fn_710036934C();
    if (type < 1 || type > 20) {
        return false;
    }
    int count = 0;
    if (!GfMenuItemUtil::canCountStack(type)) {
        count = GfItemBox::get()->fn_71002F9DD4(static_cast<ItemType::Type>(type));
    }
    setNumber(count);
    return true;
}

bool GfMenuGameAdapter::fn_710033E840() {
    unsigned int type = GfMenuReference::fn_710036934C();
    if (type < 1 || type > 20) {
        return false;
    }
    setNumber(GfItemBox::get()->fn_71002F9F6C(static_cast<ItemType::Type>(type)));
    return true;
}

void GfMenuGameAdapter::update(const fw::UpdateInfo& info) {
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

}  // namespace gf
