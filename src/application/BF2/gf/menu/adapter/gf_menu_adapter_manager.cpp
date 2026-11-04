#include "mm/mtl/IntrusiveList.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuRewriteNumber.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "classes/ui/UIObjectWorldPosPlugin.h"
#include "classes/ui/UIObjectOffsetPlugin.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "classes/ui/UIObjectColorPlugin.h"
#include "classes/ui/UIObjectPatternPlugin.h"
#include "ui/UIStr.h"
#include "mm/Col3.h"
#include "mm/Pnt.h"
#include "mm/Vec3.h"
#include <string.h>

namespace gf {

GfMenuAdapterManager::GfMenuAdapterManager(const GfSetupParam& param)
    : m_categoryLists(), m_activeCategories(1), m_category(0), m_addAfter(false), m_cursor(m_list.begin()) {}

GfMenuAdapterManager::~GfMenuAdapterManager() {
    for (int i = 0; i < 5; i++) {
        AdapterList& list = m_categoryLists[i];
        for (AdapterList::iterator it = list.begin(); it != list.end();) {
            GfMenuAdapter* adapter = it.operator->();
            it = list.erase(it);
            delete adapter;
        }
        list.clear();
    }
    for (AdapterList::iterator it = m_list.begin(); it != m_list.end();) {
        GfMenuAdapter* adapter = it.operator->();
        it = m_list.erase(it);
        delete adapter;
    }
    m_list.clear();
    for (AdapterList::iterator it = m_afterList.begin(); it != m_afterList.end();) {
        GfMenuAdapter* adapter = it.operator->();
        it = m_afterList.erase(it);
        delete adapter;
    }
    m_afterList.clear();
}

void GfMenuAdapterManager::build(const GfSetupParam& param) {
#line 90
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuAdapterManager(param);
}

void GfMenuAdapterManager::destroy() {
    GfMenuAdapterManager* manager = get();
    if (manager != nullptr) {
        delete manager;
    }
}

bool GfMenuAdapterManager::isInitialized() {
    return true;
}

// whether postUpdate deletes the adapter: its plugin is gone or only it still holds it (the name is not the
// original's)
static inline bool isAdapterDead(const GfMenuAdapter* adapter) {
    return adapter->m_plugin == nullptr || adapter->m_plugin->m_RefCount == 1;
}

void GfMenuAdapterManager::postUpdate(const fw::UpdateInfo& info) {
    GfMenuAdapterManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (manager->m_activeCategories & (1 << i)) {
            AdapterList& list = manager->m_categoryLists[i];
            for (AdapterList::iterator it = list.begin(); it != list.end();) {
                GfMenuAdapter* adapter = it.m_node;
                if (isAdapterDead(adapter)) {
                    it = list.erase(it);
                    delete adapter;
                } else {
                    adapter->update(info);
                    ++it;
                }
            }
        }
    }
    AdapterList::iterator it = manager->m_cursor;
    for (unsigned int i = 0; i < 200; i++) {
        if (manager->m_list.end() == it) {
            break;
        }
        GfMenuAdapter* adapter = it.m_node;
        if (isAdapterDead(adapter)) {
            it = manager->m_list.erase(it);
            delete adapter;
        } else {
            adapter->update(info);
            ++it;
        }
    }
    if (manager->m_list.end() == it) {
        manager->m_cursor = manager->m_list.begin();
    } else {
        manager->m_cursor = it;
    }
}

void GfMenuAdapterManager::postUpdateAfter(const fw::UpdateInfo& info) {
    GfMenuAdapterManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    AdapterList& list = manager->m_afterList;
    for (AdapterList::iterator it = list.begin(); it != list.end();) {
        GfMenuAdapter* adapter = it.m_node;
        if (isAdapterDead(adapter)) {
            it = list.erase(it);
            delete adapter;
        } else {
            adapter->update(info);
            ++it;
        }
    }
}

bool GfMenuAdapterManager::isAdapterFull() {
    return false;
}

void GfMenuAdapterManager::beginCategory(unsigned int category) {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_category = category;
    }
}

void GfMenuAdapterManager::endCategory() {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_category = 0;
    }
}

void GfMenuAdapterManager::beginAddAfter() {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_addAfter = true;
    }
}

void GfMenuAdapterManager::endAddAfter() {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_addAfter = false;
    }
}

void GfMenuAdapterManager::addActiveCategory(unsigned int category) {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_activeCategories |= 1 << category;
    }
}

void GfMenuAdapterManager::delActiveCategory(unsigned int category) {
    if (GfMenuAdapterManager* manager = get()) {
        manager->m_activeCategories &= ~(1 << category);
    }
}

void GfMenuAdapterManager::cleanup() {
    GfMenuAdapterManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    for (int i = 0; i < 5; i++) {
        AdapterList& list = manager->m_categoryLists[i];
        for (AdapterList::iterator it = list.begin(); it != list.end();) {
            GfMenuAdapter* adapter = it.m_node;
            if (isAdapterDead(adapter)) {
                it = list.erase(it);
                delete adapter;
            } else {
                ++it;
            }
        }
    }
    for (AdapterList::iterator it = manager->m_list.begin(); it != manager->m_list.end();) {
        GfMenuAdapter* adapter = it.m_node;
        if (isAdapterDead(adapter)) {
            it = manager->m_list.erase(it);
            delete adapter;
        } else {
            ++it;
        }
    }
    for (AdapterList::iterator it = manager->m_afterList.begin(); it != manager->m_afterList.end();) {
        GfMenuAdapter* adapter = it.m_node;
        if (isAdapterDead(adapter)) {
            it = manager->m_afterList.erase(it);
            delete adapter;
        } else {
            ++it;
        }
    }
}

void GfMenuAdapterManager::addAdapter(GfMenuAdapter* adapter, bool uncategorized) {
    if (m_category == 0 && uncategorized) {
        m_list.push_back(adapter);
    } else if (!m_addAfter) {
        m_categoryLists[m_category].push_back(adapter);
    } else {
        m_afterList.push_back(adapter);
    }
}

void GfMenuAdapterManager::setAfterUpdate(GfMenuAdapter* adapter) {
    GfMenuAdapterManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    for (int i = 0; i < 5; i++) {
        AdapterList& list = manager->m_categoryLists[i];
        for (AdapterList::iterator it = list.begin(); it != list.end(); ++it) {
            if (it.m_node == adapter) {
                list.erase(it);
                manager->m_afterList.push_back(adapter);
                break;
            }
        }
    }
}

}  // namespace gf
