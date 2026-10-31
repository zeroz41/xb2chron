#include "classes/gf/GfBladeManager.h"
#include "classes/gf/GfBladeCreateInfo.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatItem.h"
#include "gf/GfDataBladeCreate.h"
#include "gf/GfItemUtil.h"
#include "ml/MtRand.h"

namespace gf {

GfBladeManager::~GfBladeManager() {}

namespace _gfdbm {
int s_outofname = 1;
}  // namespace _gfdbm

void GfBladeManager::build(const GfSetupParam& param) {
#line 149
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBladeManager;
}

void GfBladeManager::destroy() {
    GfBladeManager* manager = get();
    manager->m_initialized = false;
    delete manager;
}

void GfBladeManager::setupGame() {
    if (GfDataBladeCreate::getRareBladeAppearType() == 0) {
        GfDataBladeCreate::setRareBladeAppearType(ml::mtRand(5) + 1);
        GfDataBladeCreate::resetAssureCount();
    }
}

bool GfBladeManager::isBindRareBladeCrystal(unsigned int item) {
    if (item == 0 || GfItemUtil::getType(item) != 11) {
        return false;
    }
    GfBdatItem* bdat = GfBdatItem::get();
    return bdat != nullptr && bdat->getCrystalListBladeID(item) != 0;
}

GfBladeCreate::GfBladeCreate() {}

void GfBladeCreate::clear() {
    GfBladeCreateInfo::clear();
}

void GfBladeCreate::setupDriver(unsigned int driver) {
    m_driver = driver;
}

bool GfBladeCreate::setupCoreCrystal(unsigned int item) {
    if (GfItemUtil::isValidCrystal(item)) {
        m_coreCrystal = item;
        return true;
    }
    return false;
}

}  // namespace gf
