#include "classes/fw/NaviManager.h"
#include "classes/navi/NvmshManager.h"
#include "navi/NvmshAccUtil.h"
#include "fw/NaviUtil.h"
#include "classes/ml/threadval.h"
#include "ml/AttrTransform.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/Scn.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

NaviManager::NaviManager() : m_resource(nullptr), m_nvmsh(nullptr) {}

bool NaviManager::initialize() {
    if (m_nvmsh == nullptr) {
#line 30
        m_nvmsh = new (Framework::getAllocator(), 16, __FILE__, __LINE__)
            navi::NvmshManager(mm::mtl::PtrSingleton<Framework>::get()->m_scn, FrameworkMemory::getMem(1));
    }
    return true;
}

bool NaviManager::finalize() {
    if (m_nvmsh != nullptr) {
        delete m_nvmsh;
        m_nvmsh = nullptr;
    }
    return true;
}

bool NaviManager::createNaviMesh(void* resource, const char* name) {
    if (m_nvmsh == nullptr) {
        return false;
    }
    m_resource = resource;
    m_nvmsh->setupResource(resource, name);
    return true;
}

void NaviManager::releaseNaviMesh() {
    if (m_resource != nullptr && m_nvmsh != nullptr) {
        m_resource = nullptr;
        m_nvmsh->releaseResource();
    }
}

navi::NvmshAcObj* NaviManager::createObject() {
    if (m_nvmsh != nullptr) {
        return m_nvmsh->createObj();
    }
    return nullptr;
}

void NaviManager::releaseObject(navi::NvmshAcObj* object) {
    if (object != nullptr && m_nvmsh != nullptr) {
        m_nvmsh->releaseObj(object);
    }
}

void NaviManager::update() {
    if (!isFinalized() && m_nvmsh != nullptr && m_resource != nullptr) {
        ml::ScnObjCam* cam = mm::mtl::PtrSingleton<Framework>::get()->m_scn->getCam(-1);
        if (cam != nullptr) {
            m_nvmsh->setPos(cam->m_info.m_render->m_transform.m_posGbl);
        }
    }
}

void NaviManager::tail() {
    if (!isFinalized() && m_nvmsh != nullptr) {
        m_nvmsh->tail();
    }
}

NaviManager::~NaviManager() {}

bool NaviUtil::testNaviColi(mm::Vec3& out, const mm::Vec3& pos, float param0, float param1) {
    navi::NvmshAccUtil util;
    return util.testNaviColi(out, pos, param0, param1, 0);
}

int NaviUtil::testNaviStraightLine(mm::Vec3& out, const mm::Vec3& start, const mm::Vec3& end, float param0,
                                   float param1) {
    navi::NvmshAccUtil util;
    return util.testNaviStraightLine(out, start, end, param0, param1, 0);
}

int NaviUtil::testNaviFindPos(const mm::Vec3& pos0, float param0, float param1, float param2, const mm::Vec3& pos1,
                              float param3, float param4, float param5, int) {
    navi::NvmshAccUtil util;
    return util.checkNaviFindPos(pos0, param0, param1, param2, 0.0f, pos1, param3, param4, param5, 0.0f, 0);
}

unsigned int ComponentObject::getLayer() const {
    return m_owner->m_updateBit;
}

mm::mtl::RTTI ComponentObject::m_rtti("ComponentObject", nullptr, nullptr);

}  // namespace fw
