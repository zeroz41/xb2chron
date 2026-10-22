#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5BAF0; a route of the elemental combo on the menu's target: its colour, icon, effect and whether it
// was passed or is the current one
class GfMenuElementComboAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceRouteConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuElementComboAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 3.0.1 has no copy (create builds it in place)
    GfMenuElementComboAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, true, changed), m_comboId(0), m_routeNo(7), m_converter(nullptr) {}
    virtual ~GfMenuElementComboAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuElementComboAdapter* create(unsigned int handle, unsigned int type, unsigned int comboId,
                                             bool changed);
    bool update_ComboRouteColor();
    bool update_ComboRouteIcon();
    bool update_ComboRouteEffectName();
    bool update_ComboRouteEffect();
    bool update_ComboRouteAttrPtn();
    bool update_ComboRoutePassedDisp();
    bool update_ComboRouteCurrentDisp();
    // an adapter showing a combo route's element on the object (GfMenuObjComboRoute::setupComboRoute's: kinds 1,
    // 2, 5 and 6, each with its route index)
    static GfMenuElementComboAdapter* createReferenceRoute(unsigned int handle, unsigned int type, unsigned int route,
                                                           bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none. The menu's target's property when the target is an enemy
    static GfObjPropertyEnemy* getTargetProperty() {
        GF_OBJ_HANDLE* handle = GfMenuManager::getTargetObjHandle();
        if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            return nullptr;
        }
        GfObjAcc acc(handle);
        if (acc.getType() != 5) {
            return nullptr;
        }
        GfObjProperty* property = GfObjUtil::getProperty(handle);
        if (property == nullptr) {
            return nullptr;
        }
        return property->getEnemy();
    }
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    unsigned int m_comboId;              // the combo (create's; update takes it from m_converter)
    unsigned int m_routeNo;              // the route (7: none); the name is not the original's
    IConverter* m_converter;             // owned
};
}  // namespace gf

#endif
