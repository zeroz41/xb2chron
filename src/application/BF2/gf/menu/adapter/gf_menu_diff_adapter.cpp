#include "classes/gf/GfMenuDiffAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// per type: the update_* the comparison drives, and the plugin create makes (image index, colour, number, disp)
static GfMenuDiffAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuDiffAdapter::update_Icon, {1, 0, 0}},
    {&GfMenuDiffAdapter::update_MulCol, {8, 0, 0}},
    {&GfMenuDiffAdapter::update_Sub, {0, -9999, 9999}},
    {&GfMenuDiffAdapter::update_DispSameOn, {3, 0, 0}},
    {&GfMenuDiffAdapter::update_DispSameOff, {3, 0, 0}},
};

GfMenuDiffAdapter::~GfMenuDiffAdapter() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

GfMenuDiffAdapter* GfMenuDiffAdapter::create(unsigned int handle, GfMenuAdapter* lhs, GfMenuAdapter* rhs,
                                             unsigned int type, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr || lhs == nullptr || rhs == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 54
    GfMenuDiffAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuDiffAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_lhs = lhs;
    adapter->m_rhs = rhs;
    plugin->release();
    return adapter;
}

bool GfMenuDiffAdapter::update_Icon(int result) {
    switch (result) {
    case 0:
        return false;
    case 1:
        setNumber(0);
        break;
    case 2:
        setNumber(1);
        break;
    }
    return true;
}

bool GfMenuDiffAdapter::update_MulCol(int result) {
    switch (result) {
    case 0:
        setMulColor("select");
        break;
    case 1:
        setMulColor("diff_high");
        break;
    case 2:
        setMulColor("diff_low");
        break;
    }
    return true;
}

bool GfMenuDiffAdapter::update_Sub(int result) {
    setNumber(m_lhs->getNumber() - m_rhs->getNumber());
    return true;
}

bool GfMenuDiffAdapter::update_DispSameOn(int result) {
    return result == 0;
}

bool GfMenuDiffAdapter::update_DispSameOff(int result) {
    return result != 0;
}

void GfMenuDiffAdapter::update(const fw::UpdateInfo& info) {
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update(GfMenuAdapter::compare(m_lhs, m_rhs)));
        m_flags &= ~1;
    }
}

}  // namespace gf
