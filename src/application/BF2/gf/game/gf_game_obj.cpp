#include "mm/mtl/FixedList.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameObjEnemy.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfGameMount.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"

namespace gf {

GfGameObj::GfGameObj(const GfSetupParam& param) : m_enemy(nullptr), pad_55c70(false) {
    initialize(param);
    GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
}

GfGameObj::~GfGameObj() {
    GfObjManager::removeListener(this);
}

void GfGameObj::build(const GfSetupParam& param) {
#line 213
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameObj(param);
}

void GfGameObj::postUpdate(const fw::UpdateInfo& info) {
    get()->updateObjectProperty();
}

void GfGameObj::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int) {
    GfGameObj* self = get();
    switch (evt) {
    case 1:
        GfGameEvent::applySetDispObject(handle);
        break;
    case 2:
        self->addInObj(handle, 0.5f);
        break;
    case 3:
        self->removeGameObj(handle);
        break;
    }
}

void GfGameObj::addInObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    GfGameEvent::applySetDispObject(handle);
    GfObjAcc acc(handle);
    float alpha = acc.getAlphaLife();
    m_inList.push_back(INOUT(handle, fadeTime, alpha));
    acc.setFlag(15, true);
    if (acc.getType() == 5) {
        acc.getObj()->setUpdateComponent(true);
    }
}

GfGameObj::ObjList* GfGameObj::getListType(unsigned int kind, GF_OBJ_HANDLE* handle) {
    switch (kind) {
    case 3:
        return &m_listDriver;
    case 4:
        return &m_listBlade;
    case 5:
        if (GfObjUtil::isEnemyBlade(handle)) {
            return &m_listEnemyBlade;
        }
        return &m_listEnemy;
    case 6:
        return &m_listType6;
    case 7:
        return &m_listType7;
    case 8:
        return &m_listType8;
    case 9:
        return &m_listType9;
    case 10:
        return &m_listType10;
    case 0:
    case 14:
        return &m_listType0;
    case 12:
        return &m_listType12;
    case 11:
        return &m_listType11;
    case 13:
        return &m_listType13;
    default:
        return &m_listOther;
    }
}

mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>* GfGameObj::getList(unsigned int kind) {
    return get()->getListType(kind, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
}

GfGameObj::ObjList* GfGameObj::getListEnemyBlade() {
    return &get()->m_listEnemyBlade;
}

void GfGameObj::flushEvent() {
    for (GF_OBJ_HANDLE** it = m_enterObjs.begin(); it != m_enterObjs.end(); ++it) {
        if (m_enemy != nullptr) {
            m_enemy->enterEnemyObj(*it);
        }
        GfEvent::callGameObjEnter(*it);
    }
    for (GF_OBJ_HANDLE** it = m_leaveObjs.begin(); it != m_leaveObjs.end(); ++it) {
        if (m_enemy != nullptr) {
            m_enemy->leaveEnemyObj(*it);
        }
        GfEvent::callGameObjLeave(*it);
    }
    m_enterObjs.clear();
    m_leaveObjs.clear();
}

void GfGameObj::destroyGameObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    if (GfObjUtil::getObj(handle) != nullptr) {
        if (!get()->addOutObj(handle, fadeTime, true)) {
            GfObjUtil::destroy(handle);
        }
    }
}

bool GfGameObj::isDestroyGameObj(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return true;
    }
    return !acc.testFlag(14);
}

bool GfGameObj::isEnterGameObj(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    mm::mtl::FixedList<INOUT, 1024>& list = get()->m_inList;
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == handle) {
            return true;
        }
    }
    return false;
}

void GfGameObj::setupEnterGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            setupEnterGameObj(mount->getAllWeapons(i), fadeTime);
        }
    }
}

void GfGameObj::setupLeaveGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            setupLeaveGameObj(mount->getAllWeapons(i), fadeTime);
        }
    }
}

void GfGameObj::enterStayObject(GF_OBJ_HANDLE* handle) {
    GfObjManager::enterStayObject(handle);
}

void GfGameObj::enterStayObjectMount(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            GfObjManager::enterStayObject(mount->getAllWeapons(i));
        }
    }
}

void GfGameObj::enterStayObjectWithVolumeFade(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
    if (setup != nullptr) {
        setup->pad_50 = 1.0f;
        setup->pad_60 = false;
        setup->pad_64 = 4;
    }
    GfObjManager::enterStayObject(handle);
}

GfObj* GfGameObj::getObj(GF_OBJ_HANDLE* handle) {
    GfGameObj* self = get();
    GfObjAcc acc(handle);
    mm::mtl::FixedList<INOUT, 1024>& list = self->m_inList;
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == handle) {
            return GfObjUtil::getObj(handle);
        }
    }
    if (!acc.testFlag(14)) {
        return nullptr;
    }
    return GfObjUtil::getObj(handle);
}

}  // namespace gf
