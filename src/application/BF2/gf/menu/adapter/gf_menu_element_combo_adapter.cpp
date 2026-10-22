#include "classes/gf/GfMenuAdapter.h"
#include "gf/GfObjUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "classes/gf/GfMenuElementComboAdapter.h"
#include "classes/gf/GfMenuElementComboAdapter/IConverter.h"
#include "classes/gf/GfMenuElementComboAdapter/ReferenceRouteConverter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (colour, image index, text, number, pattern, disp)
static GfMenuElementComboAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuElementComboAdapter::update_ComboRouteColor, {8, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteIcon, {1, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteEffectName, {2, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteEffect, {1, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteAttrPtn, {9, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRoutePassedDisp, {3, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteCurrentDisp, {3, 0, 0}},
};

GfMenuElementComboAdapter::~GfMenuElementComboAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuElementComboAdapter* GfMenuElementComboAdapter::create(unsigned int handle, unsigned int type,
                                                             unsigned int comboId, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 149
    GfMenuElementComboAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuElementComboAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_comboId = comboId;
    plugin->release();
    return adapter;
}

bool GfMenuElementComboAdapter::update_ComboRouteColor() {
    unsigned char atr = GfMenuObjUtil::getElementComboAtr(m_comboId);
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", atr);
    setAddColor(color.m_str);
    return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteIcon() {
    setNumber(GfMenuObjUtil::getElementComboAtr(m_comboId));
    return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteEffectName() {
    setText(GfMenuObjUtil::getElementComboEffectName(m_comboId));
    return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteEffect() {
    setNumber(GfMenuObjUtil::getElementComboEffect(m_comboId));
    return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteAttrPtn() {
    unsigned char atr = GfMenuObjUtil::getElementComboAtr(m_comboId);
    mm::mtl::FixStr<32> pattern;
    pattern.format("element%02d", atr);
    setTextFacePattern(pattern.m_str);
    return true;
}

// update_ComboRoutePassedDisp (0x710033C3F8): not identical yet (session12 w4 wip: the switch's cases 1 and 2 come
// out as selects, the original branches to its shared "false")

bool GfMenuElementComboAdapter::update_ComboRouteCurrentDisp() {
    int current = GfMenuReference::getElementComboRootCurrent();
    return m_routeNo == current;
}

// createReferenceRoute (0x710033C4F8): not identical yet (the inlined ReferenceRouteConverter::getElementComboId, below)

void GfMenuElementComboAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int comboId = m_converter->getElementComboId();
        if (m_comboId != comboId) {
            m_comboId = comboId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0 &&
        (GfMenuManager::isBattleState(0) || GfMenuManager::isBattleState(1))) {
        if (m_comboId == 0) {
            setDisp(false);
        } else {
            setDisp(m_update());
        }
        m_flags &= ~1;
    }
}

unsigned int GfMenuElementComboAdapter::ReferenceRouteConverter::getElementComboRouteNo() {
    return m_routeNo;
}

// ReferenceRouteConverter::getElementComboId (0x710033C6C8): not identical yet (session12 w4 wip: one branch -
// the enemy-less case returns through its own zero, the build reuses the null pointer)

}  // namespace gf
