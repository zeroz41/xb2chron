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

// update_ComboRoutePassedDisp (0x710033C3F8): not identical yet: the inner route tests of cases 1 and 2 come out
// as returned bitmap values, the original branches on them to its shared true/false

bool GfMenuElementComboAdapter::update_ComboRouteCurrentDisp() {
    int current = GfMenuReference::getElementComboRootCurrent();
    return m_routeNo == current;
}

// createReferenceRoute (0x710033C4F8): not identical yet (3 words: the inlined getElementComboId's zero for an
// invalid target handle is set before the compare, the original sets it in the shared zero block)

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

// inline: createReferenceRoute inlines it (devirtualized; its cost needs the inline hint's threshold); the
// table keeps the out-of-line copy
inline unsigned int GfMenuElementComboAdapter::ReferenceRouteConverter::getElementComboId() {
    const GfMenuReference::ElemComboRoot* root = GfMenuReference::getElementComboRootInfo(m_routeNo);
    GF_OBJ_HANDLE* handle = GfMenuManager::getTargetObjHandle();
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc acc(handle);
        if (acc.getType() == 5) {
            GfObjProperty* property = GfObjUtil::getProperty(handle);
            if (property != nullptr) {
                GfObjPropertyEnemy* enemy = property->getEnemy();
                if (enemy != nullptr && enemy->m_elementComboId != 0 && enemy->m_elementComboLv != 0) {
                    return root->m_comboId;
                }
            }
        }
    }
    return 0;
}

}  // namespace gf
