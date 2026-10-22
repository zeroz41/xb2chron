#include "classes/gf/GfMenuAdapter.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "gf/GfDataFieldSkill.h"
#include "classes/gf/GfMenuFieldSkillAdapter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/ListConverter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/ReferenceConverter.h"
#include "classes/gf/GfMenuFieldSkillAdapter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/ListConverter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/ReferenceConverter.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text; number up to 99)
static GfMenuFieldSkillAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuFieldSkillAdapter::update_Name, {2, 0, 9999}},
    {&GfMenuFieldSkillAdapter::update_Lv, {0, 0, 99}},
};

GfMenuFieldSkillAdapter::~GfMenuFieldSkillAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuFieldSkillAdapter* GfMenuFieldSkillAdapter::create(unsigned int handle, unsigned int type,
                                                         const MenuFieldSkill& skill) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 176
    GfMenuFieldSkillAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuFieldSkillAdapter(plugin, false);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_skill = skill;
    plugin->release();
    return adapter;
}

bool GfMenuFieldSkillAdapter::update_Name(const MenuFieldSkill& skill) {
    unsigned char* bdat;
    unsigned int id;
    if (skill.m_id == 0 || !GfDataFieldSkill::getName(bdat, id, skill.m_id)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuFieldSkillAdapter::update_Lv(const MenuFieldSkill& skill) {
    if (skill.m_id == 0) {
        return false;
    }
    setNumber(skill.m_lv);
    return true;
}

GfMenuFieldSkillAdapter* GfMenuFieldSkillAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                     IConverter* converter, bool changed) {
    MenuFieldSkill skill;
    converter->getFieldSkill(skill);
    GfMenuFieldSkillAdapter* adapter = create(handle, type, skill);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuFieldSkillAdapter* GfMenuFieldSkillAdapter::createFromList(unsigned int handle, unsigned int type,
                                                                 GfMenuFieldSkillList* list, int index) {
#line 214
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    return createFromCoverter(handle, type, converter, false);
}

GfMenuFieldSkillAdapter* GfMenuFieldSkillAdapter::createFromReference(
    unsigned int handle, unsigned int type, mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference) {
#line 222
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceConverter(reference);
    return createFromCoverter(handle, type, converter, false);
}

void GfMenuFieldSkillAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        MenuFieldSkill skill;
        m_converter->getFieldSkill(skill);
        if (m_skill.m_id != skill.m_id) {
            m_skill.m_id = skill.m_id;
            setChange();
        }
        if (m_skill.m_lv != skill.m_lv) {
            m_skill.m_lv = skill.m_lv;
            setChange();
        }
    }
    if ((m_flags & 3) != 0 && m_update.isValid()) {
        bool disp = false;
        if (m_skill.m_id != 0) {
            disp = m_update(m_skill);
        }
        setDisp(disp);
        m_flags &= ~1;
    }
}

GfMenuFieldSkillAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuFieldSkillAdapter::ListConverter::getFieldSkill(MenuFieldSkill& skill) {
    if (m_index == -1 || m_index >= m_list->getSize()) {
        return;
    }
    const MenuFieldSkill& contents = m_list->getContents(m_list->getPageIndex(m_index));
    skill.m_id = contents.m_id;
    skill.m_lv = contents.m_lv;
}

GfMenuFieldSkillAdapter::ReferenceConverter::~ReferenceConverter() {
    m_reference = nullptr;
}

void GfMenuFieldSkillAdapter::ReferenceConverter::getFieldSkill(MenuFieldSkill& skill) {
    if (m_reference) {
        m_reference.get()->getFs(skill);
    }
}

}  // namespace gf
