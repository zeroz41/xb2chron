#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/Map.h"
#include "classes/fw/CameraLayer.h"
#include "classes/gf/GfGameVisible.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/gf/GfAllocator.h"
#include "mm/Vec3.h"

namespace gf {

void GfGameVisible::build(const GfSetupParam& param) {
#line 40
    GfGameVisible* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameVisible();
    if (self != nullptr) {
        self->setup();
    }
}

void GfGameVisible::setup() {
    m_map.setAllocator(fw::FrameworkMemory::getAllocator(5));
    for (int i = 0; i < 1024; ++i) {
        m_pool.push_back(&m_infos[i]);
    }
}

void GfGameVisible::destroy() {
    delete get();
}

void GfGameVisible::update(const fw::UpdateInfo& info) {
    if (get() != nullptr) {
        get()->updateImpl(info);
    }
}

void GfGameVisible::updateImpl(const fw::UpdateInfo& info) {
    for (InfoMap::node* n = m_map.m_tree.first(); n != nullptr; n = m_map.m_tree.next(n)) {
        n->value.second->m_checked = false;
    }
    mm::Vec3 pos = mm::Vec3::zero;
    if (fw::CameraManager::get() != nullptr) {
        pos = fw::CameraManager::get()->m_layers[0].getCameraPosition();
    }
    searchObj(5, pos);
    searchObj(6, pos);
    searchObj(7, pos);
    searchObj(8, pos);
    ::mm::mtl::FixedQueue<GF_OBJ_HANDLE*, 1024> lost;
    for (InfoMap::node* n = m_map.m_tree.first(); n != nullptr; n = m_map.m_tree.next(n)) {
        if (!n->value.second->m_checked) {
            lost.push_back(n->value.first);
        }
    }
    for (::mm::mtl::FixedQueue<GF_OBJ_HANDLE*, 1024>::iterator it = lost.begin(); it != lost.end(); ++it) {
        Info* info = m_map.lookup(*it)->second;
        m_map.erase(*it);
        m_pool.push_back(info);
    }
}

bool GfGameVisible::isVisible(GF_OBJ_HANDLE* handle) {
    // (the original combines the two with an and, reading visible even when nothing was found)
    bool visible;
    bool found = false;
    if (GfGameVisible* self = get()) {
        if (InfoMap::node* n = self->m_map.find(handle)) {
            if (Info* info = n->value.second) {
                visible = info->m_visible;
                found = true;
            }
        }
    }
    return found & visible;
}

GfGameVisible::~GfGameVisible() {}

}  // namespace gf

// searchObj (not written yet) adds an Info per handle: the map's insert and rebalance are emitted here
template gf::GfGameVisible::InfoMap::node* gf::GfGameVisible::InfoMap::tree_type::insert(
    const gf::GfGameVisible::InfoMap::tree_type::value_type&);
