#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuZoneAdapter.h"
#include "classes/gf/GfMenuZoneAdapter/IConverter.h"
#include "classes/gf/GfMenuZoneAdapter/ReferenceNumberConverter.h"
#include "classes/gf/GfMenuZoneAdapter/ReferenceZoneConverter.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataDevelop.h"
#include "gf/GfDataMercenaries.h"
#include "mm/mtl/FixedVector.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, number from 1 to 5, image index, colour,
// disp)
static GfMenuZoneAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuZoneAdapter::update_ZoneName, {2, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneLv, {0, 1, 5}},
    {&GfMenuZoneAdapter::update_ZoneIcon, {1, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneLvIcon, {1, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneStatColor, {8, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneNoticeDisp, {3, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneNotice, {2, 0, 0}},
};

GfMenuZoneAdapter::~GfMenuZoneAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuZoneAdapter* GfMenuZoneAdapter::create(unsigned int handle, unsigned int type, unsigned short zoneId,
                                             bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 125
    GfMenuZoneAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuZoneAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_zoneId = zoneId;
    plugin->release();
    return adapter;
}

bool GfMenuZoneAdapter::update_ZoneName() {
    ui::UIStr text(GfDataBdat::getFP(0x1AC), m_zoneId);
    setText(text);
    return true;
}

bool GfMenuZoneAdapter::update_ZoneLv() {
    setNumber(GfDataDevelop::getLevel(m_zoneId));
    return true;
}

bool GfMenuZoneAdapter::update_ZoneIcon() {
    if (m_zoneId == 0) {
        return false;
    }
    setNumber(m_zoneId - 1);
    return true;
}

bool GfMenuZoneAdapter::update_ZoneLvIcon() {
    setNumber(GfDataDevelop::getLevel(m_zoneId));
    return true;
}

bool GfMenuZoneAdapter::update_ZoneStatColor() {
    if (GfDataMercenaries::getTeamNum() < m_teamId) {
        return false;
    }
    mm::mtl::FixedVector<unsigned short, 3> working;
    GfDataMercenaries::getTeamByZoneMissionWorking(working, m_zoneId);
    mm::mtl::FixedVector<unsigned short, 3> complete;
    GfDataMercenaries::getTeamByZoneMissionComplete(complete, m_zoneId);
    const char* color = "mer_unit_ready";
    bool isWorking = false;
    for (unsigned short i = 0; i < working.size(); i++) {
        if (working[i] == m_teamId) {
            color = "mer_unit_active";
            isWorking = true;
            break;
        }
    }
    bool isComplete = false;
    for (unsigned short i = 0; i < complete.size(); i++) {
        if (complete[i] == m_teamId) {
            color = "blue";
            isComplete = true;
            break;
        }
    }
    if (!isComplete && !isWorking) {
        color = GfDataMercenaries::isTeamStateExpedition(m_teamId) || GfDataMercenaries::isTeamStateReward(m_teamId)
                    ? "darkgray"
                    : color;
    }
    setAddColor(color);
    return true;
}

bool GfMenuZoneAdapter::update_ZoneNoticeDisp() {
    mm::mtl::FixedVector<unsigned short, 500> missions;
    GfGameMercenaries::getZoneMission(missions, m_zoneId);
    if (missions.size() != 0) {
        mm::mtl::FixedVector<unsigned short, 500>::iterator it = missions.begin();
        do {
            if (GfDataMercenaries::getMissionCategory(*it) == 3 || GfDataMercenaries::isNewMission(*it++)) {
                return true;
            }
        } while (it != missions.end());
    }
    return false;
}

bool GfMenuZoneAdapter::update_ZoneNotice() {
    mm::mtl::FixedVector<unsigned short, 500> missions;
    GfGameMercenaries::getZoneMission(missions, m_zoneId);
    bool hasCategory3 = false;
    int category3Count = 0;
    int newCount = 0;
    if (missions.size() != 0) {
        mm::mtl::FixedVector<unsigned short, 500>::iterator it = missions.begin();
        do {
            if (GfDataMercenaries::getMissionCategory(*it) == 3) {
                category3Count++;
            }
            newCount += GfDataMercenaries::isNewMission(*it++);
        } while (it != missions.end());
        hasCategory3 = category3Count > 0;
    }
    unsigned char* message = GfDataBdat::getFP(0xF5);
    unsigned char* notice = GfDataBdat::getFP(0x13D);
    int row;
    if (m_teamId == 1) {
        if (hasCategory3) {
            row = 0x11;
        } else if (newCount > 0) {
            row = 0x12;
        } else {
            return false;
        }
    } else {
        if (!((newCount > 0) & hasCategory3)) {
            return false;
        }
        row = 0x12;
    }
    ui::UIStr text(message, (unsigned short)Bdat::getVal(notice, "name", row));
    setText(text);
    return true;
}

GfMenuZoneAdapter* GfMenuZoneAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                         IConverter* converter, bool changed) {
    GfMenuZoneAdapter* adapter = create(handle, type, converter->getZoneId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuZoneAdapter* GfMenuZoneAdapter::createFromReferenceZone(unsigned int handle, unsigned int type, bool changed) {
#line 153
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceZoneConverter();
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuZoneAdapter* GfMenuZoneAdapter::createFromReference(unsigned int handle, unsigned int type,
                                                          mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                          bool changed) {
#line 161
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceNumberConverter(reference);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuZoneAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int zoneId = m_converter->getZoneId();
        if (m_zoneId != zoneId) {
            m_zoneId = zoneId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_zoneId != 0) {
            setDisp(m_update());
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
