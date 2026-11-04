#include "classes/gf/GfItemManager.h"
#include "classes/gf/GfItemBox.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfItemManager::GfItemManager(const GfSetupParam& param) : m_initialized(false) {
    initialize(param);
}

void GfItemManager::initialize(const GfSetupParam& param) {
#line 80
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfItemBox;
    GfItemBox::get()->initialize();
    m_initialized = true;
}

GfItemManager::~GfItemManager() {}

void GfItemManager::build(const GfSetupParam& param) {
#line 51
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfItemManager(param);
}

void GfItemManager::destroy() {
    GfItemManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfItemManager::finalize() {
    GfItemBox::get()->finalize();
    delete GfItemBox::get();
    m_initialized = false;
}

const RecipeInfo::Result& RecipeInfo::getResultRarity() const {
    return m_resultRarity;
}

const RecipeInfo::Result& RecipeInfo::getResultColleCategory() const {
    return m_resultColleCategory;
}

const ::mm::mtl::FixedVector<RecipeInfo::Item, 8>& RecipeInfo::getResultItems() const {
    return m_resultItems;
}

GfItemBox::~GfItemBox() {}

}  // namespace gf
