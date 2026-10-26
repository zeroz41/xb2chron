#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuAchievementAdapter.h"
#include "classes/gf/GfMenuAchievementAdapter/IConverter.h"
#include "classes/gf/GfMenuAchievementAdapter/ReferenceBladeConverter.h"
#include "classes/gf/GfMenuAchievementAdapter/ReferenceBladeLineLevelConverter.h"
#include "gf/GfKizunaringBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBladeArts.h"
#include "gf/GfDataBladeSkill.h"
#include "gf/GfQuestUtil.h"
#include "ui/UIStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataFieldSkill.h"
#include "gf/GfDataHana.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
static GfMenuAchievementAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementCategory, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementTitle, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementResult, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementVoiceCategory, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementVoiceAfter, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementDifficulty, {0, 1, 5}},
    {&GfMenuAchievementAdapter::update_AchievementQuest, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementSetCategory, {0, 0, 12}},
    {&GfMenuAchievementAdapter::update_AchievementSetAbilityLevel, {0, 1, 5}},
    {&GfMenuAchievementAdapter::update_AchievementTypeIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementCategoryIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagColor, {8, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementSkillName, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_LearnNum, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_LearnMax, {0, 0, 99}},
    {&GfMenuAchievementAdapter::update_QuestNum, {0, 0, 9999999}},
    {&GfMenuAchievementAdapter::update_QuestMax, {0, 0, 9999999}},
    {&GfMenuAchievementAdapter::update_IdeaText, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_IdeaIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_QuestCaptionText, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_QuestResultText, {2, 0, 0}},
    {&GfMenuAchievementAdapter::update_KeyIcon, {1, 0, 0}},
    {&GfMenuAchievementAdapter::update_NetabareOkDisp, {3, 0, 0}},
};

GfMenuAchievementAdapter::~GfMenuAchievementAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuAchievementAdapter* GfMenuAchievementAdapter::create(unsigned int handle, unsigned int type,
    unsigned int bladeId, unsigned short kizunaLine, unsigned short kizunaLevel, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 190
    GfMenuAchievementAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuAchievementAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_bladeId = bladeId;
    adapter->m_kizunaLine = kizunaLine;
    adapter->m_kizunaLevel = kizunaLevel;
    plugin->release();
    return adapter;
}

bool GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon() {
    setNumber(GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementCategory() {
    setNumber(GfKizunaringBlade::getAchievementCategory(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementTitle() {
    if (m_kizunaLine == 9 && m_kizunaLevel == 1) {
        return false;
    }
    if (GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel) == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBlade::getTaskSkillMessage(bdat, id, m_bladeId, m_kizunaLine)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementResult() {
    if (GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel) == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (GfKizunaringBlade::getAchievementResultMsg(bdat, id, m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        unsigned int enhance = GfKizunaringBlade::getAchievementResultEnhance(m_bladeId, m_kizunaLine, m_kizunaLevel);
        ui::UIStr text(bdat, id);
        text.m_ownerId = enhance;
        setText(text);
        return true;
    }
    if (m_kizunaLine == 9) {
        unsigned int level = m_kizunaLevel;
        if (level >= 2 && level <= 5) {
            unsigned int linkCh = GfDataBlade::getLinkChNum(m_bladeId);
            if (linkCh == 3 && level == 3) {
                level = 6;
            }
            if (level == 5 && linkCh == 5) {
                level = 7;
            }
            unsigned int msg = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x162), "name", level));
            ui::UIStr text(GfDataBdat::getFP(0x1ba), msg);
            setText(text);
            return true;
        }
    } else if (GfDataHana::isValid(m_bladeId)) {
        id = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x15a), "name", 3));
        bdat = GfDataBdat::getFP(0xf5);
        ui::UIStr text(bdat, id);
        setText(text);
        return true;
    }
    return false;
}

bool GfMenuAchievementAdapter::update_AchievementIcon() {
    setNumber(GfKizunaringBlade::getAchievementIcon(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementVoiceCategory() {
    setNumber(GfKizunaringBlade::getAchievementVoiceCategory(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementVoiceAfter() {
    GfKizunaringBlade::getAchievementAfterVoice(m_bladeId, m_kizunaLine, m_kizunaLevel);
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementDifficulty() {
    setNumber(GfKizunaringBlade::getAchievementDifficulty(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementQuest() {
    setNumber(GfKizunaringBlade::getAchievementQuest(m_bladeId, m_kizunaLine, m_kizunaLevel));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementSetCategory() {
    setNumber(GfKizunaringBlade::getAchievementSetCategory(m_bladeId, m_kizunaLine));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementSetAbilityLevel() {
    setNumber(GfKizunaringBlade::getAchievementSetAbilityLevel(m_bladeId, m_kizunaLine));
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementTypeIcon() {
    unsigned int release = GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel);
    if (m_kizunaLine == 9) {
        if (m_kizunaLevel == 1) {
            return false;
        }
        int icon;
        if (release == 4 || release == 5) {
            icon = 5;
        } else if (GfMenuObjUtil::fn_710048FD30(3) && release == 3) {
            icon = 5;
        } else {
            icon = 11;
        }
        setNumber(icon);
        return true;
    }
    int icon;
    if (release == 1) {
        icon = 23;
    } else if (release == 0) {
        icon = 10;
    } else {
        ACHIEVEMENT_TYPE type;
        unsigned int index;
        icon = 10;
        if (GfDataAchievement::getAchievementType(type, index, m_kizunaLine)) {
            switch (static_cast<int>(type)) {
            case 0: icon = 12; break;
            case 1: icon = 13; break;
            case 2: icon = 14; break;
            }
        }
    }
    setNumber(icon);
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementCategoryIcon() {
    if (GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel) == 0) {
        return false;
    }
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (GfDataAchievement::getAchievementType(type, index, m_kizunaLine) && type == 3 &&
        m_kizunaLine == 9 && m_kizunaLevel == 1) {
        return false;
    }
    int icon;
    switch (static_cast<int>(type)) {
    case 0: icon = 0; break;
    case 1: icon = 3; break;
    case 2: icon = 1; break;
    default: icon = 9; break;
    }
    setNumber(icon);
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementReleaseFlagColor() {
    unsigned int release = GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel);
    if (release == 0 || release == 1) {
        return true;
    }
    if (release == 4 || release == 5) {
        setMulColor("white");
    } else {
        setMulColor("black");
    }
    return true;
}

bool GfMenuAchievementAdapter::update_AchievementSkillName() {
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (!GfDataAchievement::getAchievementType(type, index, m_kizunaLine)) {
        return false;
    }
    unsigned int skill = GfDataBlade::getSkillLineId(m_bladeId, m_kizunaLine);
    if (skill == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    switch (static_cast<int>(type)) {
    case 0: GfDataBladeArts::getName(bdat, id, skill); break;
    case 1: GfDataBladeSkill::getName(bdat, id, skill); break;
    case 2: GfDataFieldSkill::getName(bdat, id, skill); break;
    default: return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuAchievementAdapter::update_LearnNum() {
    setNumber(GfDataBlade::getKizunaringCompleteNum(m_bladeId));
    return true;
}

bool GfMenuAchievementAdapter::update_LearnMax() {
    setNumber(GfDataBlade::getKizunaringMax(m_bladeId));
    return true;
}

bool GfMenuAchievementAdapter::update_QuestNum() {
    AchievInfo* info = GfDataBlade::getAchievInfo(m_bladeId, m_kizunaLine);
    unsigned int count;
    unsigned int max;
    if (GfQuestUtil::getDispCount(count, max, info->m_quests[m_kizunaLevel - 1])) {
        setNumber(count);
        return true;
    }
    return false;
}

bool GfMenuAchievementAdapter::update_QuestMax() {
    AchievInfo* info = GfDataBlade::getAchievInfo(m_bladeId, m_kizunaLine);
    unsigned int count;
    unsigned int max;
    if (GfQuestUtil::getDispCount(count, max, info->m_quests[m_kizunaLevel - 1])) {
        setNumber(max);
        return true;
    }
    return false;
}

bool GfMenuAchievementAdapter::update_IdeaText() {
    unsigned int idea;
    unsigned int count;
    if (GfQuestUtil::getResultIdea(idea, count, m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        if (count != 0) {
            ui::UIStr text(GfDataBdat::getFP(0x126), idea + 1);
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuAchievementAdapter::update_IdeaIcon() {
    unsigned int idea;
    unsigned int count;
    if (GfQuestUtil::getResultIdea(idea, count, m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        if (count != 0) {
            setNumber(idea);
            return true;
        }
    }
    return false;
}

bool GfMenuAchievementAdapter::update_QuestCaptionText() {
    unsigned char* bdat;
    unsigned int id;
    if (!GfKizunaringBlade::isNetabareOK(m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        unsigned int msg = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x15a), "name", 1));
        ui::UIStr text(GfDataBdat::getFP(0xf5), msg);
        setText(text);
        return true;
    }
    if (GfDataBlade::getTaskTitleMessage(bdat, id, m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        ui::UIStr text(bdat, id);
        if (text.size() != 0 && GfDataBlade::getTaskSkillMessage(bdat, id, m_bladeId, m_kizunaLine)) {
            ui::UIStr skill(bdat, id);
            GfMenuReference::setReferenceString(skill, 0);
            text.m_ownerId = 0;
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuAchievementAdapter::update_QuestResultText() {
    unsigned char* bdat;
    unsigned int id;
    if (GfDataBlade::getTaskResultMessage(bdat, id, m_bladeId, m_kizunaLine, m_kizunaLevel)) {
        ui::UIStr text(bdat, id);
        if (text.size() != 0 && GfDataBlade::getTaskSkillMessage(bdat, id, m_bladeId, m_kizunaLine)) {
            ui::UIStr skill(bdat, id);
            GfMenuReference::setReferenceString(skill, 1);
            text.m_ownerId = 1;
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuAchievementAdapter::update_KeyIcon() {
    unsigned int release = GfKizunaringBlade::getReleaseAchievement(m_bladeId, m_kizunaLine, m_kizunaLevel);
    setNumber(m_kizunaLevel == 1 || release == 4 || release == 5 ? 5 : 11);
    return true;
}

bool GfMenuAchievementAdapter::update_NetabareOkDisp() {
    return GfKizunaringBlade::isNetabareOK(m_bladeId, m_kizunaLine, m_kizunaLevel);
}

GfMenuAchievementAdapter* GfMenuAchievementAdapter::createFromReferenceBlade(unsigned int handle, unsigned int type,
    unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel, bool changed) {
#line 221
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeConverter(reference, kizunaLine, kizunaLevel);
    GfMenuAchievementAdapter* adapter = create(handle, type, converter->getBladeId(), converter->getKizunaLine(),
        converter->getKizunaLevel(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuAchievementAdapter* GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(unsigned int handle,
    unsigned int type, unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel, bool changed) {
#line 229
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeLineLevelConverter(reference, kizunaLine, kizunaLevel);
    GfMenuAchievementAdapter* adapter = create(handle, type, converter->getBladeId(), converter->getKizunaLine(),
        converter->getKizunaLevel(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

void GfMenuAchievementAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int bladeId = m_converter->getBladeId();
        if (m_bladeId != bladeId) {
            m_bladeId = bladeId;
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
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeConverter::getBladeId() {
    return GfMenuReference::getReferenceBladeID(m_reference);
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeConverter::getKizunaLine() {
    return m_kizunaLine;
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeConverter::getKizunaLevel() {
    return m_kizunaLevel;
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeLineLevelConverter::getBladeId() {
    return GfMenuReference::getReferenceBladeID(m_reference);
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeLineLevelConverter::getKizunaLine() {
    return GfMenuReference::getReferenceNumber(m_kizunaLine);
}

unsigned int GfMenuAchievementAdapter::ReferenceBladeLineLevelConverter::getKizunaLevel() {
    return GfMenuReference::getReferenceNumber(m_kizunaLevel);
}

}  // namespace gf
