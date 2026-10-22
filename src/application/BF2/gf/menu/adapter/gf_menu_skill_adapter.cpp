#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuSkillAdapter.h"
#include "classes/gf/GfMenuSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuSkillAdapter/ReferenceDriverConverter.h"
#include "classes/gf/GfMenuSkillAdapter/ReferenceDriverLineLevelConverter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataDriverSkill.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, number up to 9999999 or 15, image index,
// colour)
static GfMenuSkillAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuSkillAdapter::update_SkillName, {2, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillCaption, {2, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillPoint, {0, 0, 9999999}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagIcon, {1, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagColor, {8, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagColorIcon, {1, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLearnDisp, {8, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLevelLockIcon, {1, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLearnNum, {0, 0, 15}},
    {&GfMenuSkillAdapter::update_SkillLearnMax, {0, 0, 15}},
    {&GfMenuSkillAdapter::update_SkillLevelUnlockNum, {0, 0, 15}},
};

GfMenuSkillAdapter::~GfMenuSkillAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuSkillAdapter* GfMenuSkillAdapter::create(unsigned int handle, unsigned int type, unsigned int driverId,
                                               unsigned short kizunaLine, unsigned short kizunaLevel,
                                               unsigned short round, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 192
    GfMenuSkillAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuSkillAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_driverId = driverId;
    adapter->m_kizunaLine = kizunaLine;
    adapter->m_kizunaLevel = kizunaLevel;
    adapter->m_round = round;
    plugin->release();
    return adapter;
}

bool GfMenuSkillAdapter::update_SkillName() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    unsigned int skill = GfDataDriverSkill::getSkillFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, m_round != 0);
    if (skill == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    GfDataDriverSkill::getName(bdat, id, skill);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuSkillAdapter::update_SkillCaption() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    bool round = m_round != 0;
    unsigned int skill = GfDataDriverSkill::getSkillFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, round);
    if (skill == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    GfDataDriverSkill::getEnhanceCaption(bdat, id, skill);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(bdat, id);
    text.m_ownerId = GfDataDriverSkill::getEnhanceFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, round);
    setText(text);
    return true;
}

bool GfMenuSkillAdapter::update_SkillPoint() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    bool round = m_round != 0;
    if (GfDataDriverSkill::getSkillFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, round) == 0) {
        return false;
    }
    if (GfDataDriverSkill::getSkill(m_driverId, m_kizunaLine, m_kizunaLevel, round) != 0) {
        return false;
    }
    setNumber(GfDataDriverSkill::getSkillPointFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, round));
    return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagIcon() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    bool round = m_round != 0;
    int number;
    if (GfDataDriverSkill::isSkillUnlock(m_driverId, m_kizunaLine, m_kizunaLevel, round)) {
        number = GfDataDriverSkill::getSkillCategoryFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, round) + 6;
    } else {
        number = 0x17;
    }
    setNumber(number);
    return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColor() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    bool round = m_round != 0;
    const char* color = "gray";
    if (GfDataDriverSkill::isSkillUnlock(m_driverId, m_kizunaLine, m_kizunaLevel, round) &&
        GfDataDriverSkill::getSkill(m_driverId, m_kizunaLine, m_kizunaLevel, round) != 0) {
        color = "white";
    }
    setColorMode(0);
    setColor(color);
    return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColorIcon() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    setNumber(GfDataDriverSkill::getSkillCategoryFromBdat(m_driverId, m_kizunaLine, m_kizunaLevel, m_round != 0) + 0x12);
    return true;
}

bool GfMenuSkillAdapter::update_SkillLearnDisp() {
    if (m_kizunaLine >= 5) {
        return false;
    }
    bool round = m_round != 0;
    if (!GfDataDriverSkill::isSkillUnlock(m_driverId, m_kizunaLine, m_kizunaLevel, round)) {
        return false;
    }
    if (GfDataDriverSkill::getSkill(m_driverId, m_kizunaLine, m_kizunaLevel, round) != 0) {
        setMulColor("white");
    } else {
        setMulColor("black");
    }
    return true;
}

bool GfMenuSkillAdapter::update_SkillLevelLockIcon() {
    int number = 5;
    if (m_kizunaLevel != 1 && !GfDataDriverSkill::isSkillLevelUnlock(m_driverId, m_kizunaLevel, m_round != 0)) {
        number = 0xB;
    }
    setNumber(number);
    return true;
}

bool GfMenuSkillAdapter::update_SkillLearnNum() {
    setNumber(GfDataDriverSkill::getValidSkillNum(m_driverId, m_round != 0));
    return true;
}

bool GfMenuSkillAdapter::update_SkillLearnMax() {
    setNumber(15);
    return true;
}

bool GfMenuSkillAdapter::update_SkillLevelUnlockNum() {
    if (m_kizunaLine != 5) {
        return false;
    }
    unsigned int num = GfDataDriverSkill::getSkillLevelUnlockNum(m_driverId, m_kizunaLevel, m_round != 0);
    if (num == 0) {
        return false;
    }
    setNumber(num);
    return true;
}

GfMenuSkillAdapter* GfMenuSkillAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                           IConverter* converter, bool changed) {
    GfMenuSkillAdapter* adapter = create(handle, type, converter->getDriverId(), converter->getKizunaLine(),
                                         converter->getKizunaLevel(), converter->getRound(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuSkillAdapter* GfMenuSkillAdapter::createFromReferenceDriver(unsigned int handle, unsigned int type,
                                                                  unsigned int reference, unsigned short kizunaLine,
                                                                  unsigned short kizunaLevel, unsigned short round,
                                                                  bool changed) {
#line 225
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceDriverConverter(reference, kizunaLine, kizunaLevel, round);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuSkillAdapter* GfMenuSkillAdapter::createFromReferenceDriverLineLevel(unsigned int handle, unsigned int type,
                                                                           unsigned int reference,
                                                                           unsigned short kizunaLine,
                                                                           unsigned short kizunaLevel,
                                                                           unsigned short round, bool changed) {
#line 233
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceDriverLineLevelConverter(reference, kizunaLine, kizunaLevel, round);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuSkillAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int driverId = m_converter->getDriverId();
        if (m_driverId != driverId) {
            m_driverId = driverId;
            setChange();
        }
        unsigned int kizunaLine = m_converter->getKizunaLine();
        if (m_kizunaLine != kizunaLine) {
            m_kizunaLine = kizunaLine;
            setChange();
        }
        unsigned int kizunaLevel = m_converter->getKizunaLevel();
        if (m_kizunaLevel != kizunaLevel) {
            m_kizunaLevel = kizunaLevel;
            setChange();
        }
        unsigned int round = m_converter->getRound();
        if (m_round != round) {
            m_round = round;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

}  // namespace gf
