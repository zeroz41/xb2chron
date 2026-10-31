#include "classes/gf/GfAssetMultiBind.h"

namespace gf {

GfAssetMultiBind::GfAssetMultiBind(unsigned int id, bool flag)
    : m_id(id), m_objNum(0), m_loadedNum(0), m_flag(flag) {}

bool GfAssetMultiBind::isValid() const {
    return m_bindObj.size() == m_objNum && m_loadedObj.size() == m_bindObj.size();
}

bool GfAssetMultiBind::bind(GF_OBJ_HANDLE* handle) {
    if (m_bindObj.find(handle) == m_bindObj.end()) {
        m_bindObj.push_back(handle);
    }
    return true;
}

bool GfAssetMultiBind::unbind(GF_OBJ_HANDLE* handle) {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>::iterator it = m_bindObj.find(handle);
    if (m_bindObj.end() != it) {
        m_bindObj.erase(it);
        return true;
    }
    return false;
}

bool GfAssetMultiBind::loadedAsset(GF_OBJ_HANDLE* handle) {
    if (m_bindObj.end() == m_bindObj.find(handle)) {
        return false;
    }
    if (m_loadedObj.find(handle) == m_loadedObj.end()) {
        m_loadedObj.push_back(handle);
        ++m_loadedNum;
    }
    return true;
}

bool GfAssetMultiBind::unloadedAsset(GF_OBJ_HANDLE* handle) {
    if (m_bindObj.end() == m_bindObj.find(handle)) {
        return false;
    }
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>::iterator it = m_loadedObj.find(handle);
    if (m_loadedObj.end() != it) {
        m_loadedObj.erase(it);
        --m_loadedNum;
    }
    return true;
}

GfAssetMultiBind::~GfAssetMultiBind() {}

}  // namespace gf
