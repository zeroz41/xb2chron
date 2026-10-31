#include "mm/mtl/FixedList.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFobjDropitem.h"
#include "classes/gf/GfDropitemParams.h"
#include "classes/gf/GfFobjManager.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataEvent.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfObjManager.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/FixedVector.h"

// The effect is compared as a 16-bit value inside a callee (the original's and w8/cmp w8; the same compare written
// at the call site widens to and x8/cmp x8). The helper's name is not the original's.
static inline bool isLeaderBonus(unsigned short effect) { return effect == 0xFB; }

namespace gf {

GfFobjManager::GfFobjManager(const GfSetupParam& param)
    : m_initialized(false), m_dropitemParams(nullptr), m_dropitemListFP(nullptr), m_dropitemParamFP(nullptr),
      m_eventDisp(true), m_waitEventValue(0), m_waitEvent(false), m_gottenEffect(nullptr), m_seManager(nullptr),
      m_leaderBonus(0.0f), m_settingValue(0.0f) {
    initialize(param);
    GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
}

void GfFobjManager::initialize(const GfSetupParam& param) {
    GfEvent::addEventCallback(this);
    if (m_dropitemParams != nullptr) {
        delete m_dropitemParams;
        m_dropitemParams = nullptr;
    }
#line 89
    m_dropitemParams = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfDropitemParams();
    GfFobjGottenEffectManager::CreateInfo effectInfo;
    effectInfo.m_capacity = 0x20;
    m_gottenEffect.create(effectInfo);
    unsigned char* fp = GfDataBdat::getFP(0x7B);
    GfFobjSeManager::CreateInfo seInfo;
    unsigned int interval = Bdat::getValCheck(fp, 0, 0x44, 8);
    seInfo.m_interval = *reinterpret_cast<float*>(&interval);
    seInfo.m_maxSe = (unsigned short)Bdat::getValCheck(fp, 1, 0x45, 2);
    m_seManager.create(seInfo);
    unsigned int value = Bdat::getValCheck(fp, 0, 0x49, 8);
    m_settingValue = *reinterpret_cast<float*>(&value);
    m_initialized = true;
}

GfFobjManager::~GfFobjManager() {
    GfObjManager::removeListener(this);
}

void GfFobjManager::build(const GfSetupParam& param) {
#line 66
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFobjManager(param);
}

void GfFobjManager::destroy() {
    GfFobjManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfFobjManager::finalize() {
    m_seManager.dispose();
    m_gottenEffect.dispose();
    for (DropitemList::iterator it = m_registList.begin(); it != m_registList.end(); ++it) {
        GfObjUtil::destroy((*it)->m_handle);
    }
    for (DropitemList::iterator it = m_fieldList.begin(); it != m_fieldList.end(); ++it) {
        GfObjUtil::destroy((*it)->m_handle);
    }
    while (!m_registList.empty() || !m_fieldList.empty()) {
        GfSleep(1);
    }
    if (m_dropitemParams != nullptr) {
        delete m_dropitemParams;
        m_dropitemParams = nullptr;
    }
    GfEvent::removeEventCallback(this);
    m_initialized = false;
}

void GfFobjManager::update(const fw::UpdateInfo& info) {
    GfFobjManager* manager = get();
    if (manager == nullptr || !manager->m_initialized) {
        return;
    }
    manager->fn_7100289504();
    if (manager->m_dropitemListFP == nullptr) {
        manager->m_dropitemListFP =
            Bdat::isExistFP(GfGameManager::fn_71002A9E68() ? "RSC_dropitemListIra" : "RSC_dropitemList");
    }
    if (manager->m_dropitemParamFP == nullptr) {
        manager->m_dropitemParamFP = Bdat::isExistFP("RSC_dropitemParam");
    }
    if (manager->m_eventDisp) {
        for (DropitemList::iterator it = manager->m_fieldList.begin(); it != manager->m_fieldList.end(); ++it) {
            (*it)->update(info);
        }
    }
    if (manager->m_dropitemParams != nullptr) {
        manager->m_dropitemParams->update();
    }
    manager->m_gottenEffect.update(info.m_deltaTime);
    manager->m_seManager.update(info.m_deltaTime);
}

void GfFobjManager::fn_7100289504() {
    m_leaderBonus = 0.0f;
    GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
    int driver = acc.getDriverId();
    if (driver == 0) {
        return;
    }
    if (driver == 12) {
        unsigned int value = Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, 0x5D, 8);
        m_leaderBonus = *reinterpret_cast<float*>(&value);
        return;
    }
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    if (GfDataDriver::fn_7100247580(enhances, driver)) {
        unsigned char* fp = GfDataBdat::getFP(0x2C);
        for (unsigned short id : enhances) {
            if (isLeaderBonus(Bdat::getValCheck(fp, "EnhanceEffect", id, 2))) {
                unsigned int value = Bdat::getValCheck(fp, "Param1", id, 8);
                m_leaderBonus += *reinterpret_cast<float*>(&value);
            }
        }
    }
    m_leaderBonus *= 0.01f;
}

GfDropitemParams* GfFobjManager::getDropitemParams() {
    if (get() != nullptr) {
        return get()->m_dropitemParams;
    }
    return nullptr;
}

void GfFobjManager::fn_7100289668() {
    m_seManager.fn_7100282EA8();
}

void GfFobjManager::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int type) {
    if (type != 9) {
        return;
    }
    if (evt == IGfObjListener::OBJEVT(2)) {
        for (DropitemList::iterator it = m_registList.begin(); it != m_registList.end(); ++it) {
            GfFobjDropitem* item = *it;
            if (item->m_handle == handle) {
                if (m_fieldList.size() == 1024) {
                    GF_OBJ_HANDLE* oldest = m_fieldList.front()->m_handle;
                    GfObjUtil::destroy(oldest);
                    leaveGameField(oldest);
                }
                m_fieldList.push_back(*it);
                m_registList.erase(it);
                item->initialize();
                return;
            }
        }
    } else if (evt == IGfObjListener::OBJEVT(3)) {
        leaveGameField(handle);
    }
}

void GfFobjManager::leaveGameField(GF_OBJ_HANDLE* handle) {
    for (DropitemList::iterator it = m_registList.begin(); it != m_registList.end(); ++it) {
        if ((*it)->m_handle == handle) {
            (*it)->destroy();
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
            m_registList.erase(it);
            break;
        }
    }
    for (DropitemList::iterator it = m_fieldList.begin(); it != m_fieldList.end(); ++it) {
        if ((*it)->m_handle == handle) {
            (*it)->destroy();
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
            m_fieldList.erase(it);
            return;
        }
    }
}

void GfFobjManager::registFiledObj(GfFobjDropitem* item) {
    GfFobjManager* manager = get();
    if (manager->m_registList.size() == 1024) {
        GF_OBJ_HANDLE* oldest = manager->m_registList.front()->m_handle;
        GfObjUtil::destroy(oldest);
        manager->leaveGameField(oldest);
    }
    manager->m_registList.push_back(item);
}

bool GfFobjManager::isExistObj() {
    GfFobjManager* manager = get();
    return !manager->m_registList.empty() || !manager->m_fieldList.empty();
}

void GfFobjManager::destroyObj() {
    GfFobjManager* manager = get();
    for (DropitemList::iterator it = manager->m_registList.begin(); it != manager->m_registList.end(); ++it) {
        GfObjUtil::destroy((*it)->m_handle);
    }
    for (DropitemList::iterator it = manager->m_fieldList.begin(); it != manager->m_fieldList.end(); ++it) {
        GfObjUtil::destroy((*it)->m_handle);
    }
}

void GfFobjManager::gevPlayEvent(GEV gev, unsigned int eventId) {
    if (GfDataEvent::getEventType(eventId) == 1) {
        if (eventId == 0x5373 || eventId == 0x5374) {
            m_eventDisp = true;
            for (DropitemList::iterator it = m_registList.begin(); it != m_registList.end(); ++it) {
                (*it)->setEventDisp(m_eventDisp);
            }
            for (DropitemList::iterator it = m_fieldList.begin(); it != m_fieldList.end(); ++it) {
                (*it)->setEventDisp(m_eventDisp);
            }
        }
    } else {
        if (gev == GEV(10)) {
            m_eventDisp = false;
        } else if (gev == GEV(11)) {
            m_eventDisp = true;
        }
        for (DropitemList::iterator it = m_registList.begin(); it != m_registList.end(); ++it) {
            (*it)->setEventDisp(m_eventDisp);
        }
        for (DropitemList::iterator it = m_fieldList.begin(); it != m_fieldList.end(); ++it) {
            (*it)->setEventDisp(m_eventDisp);
        }
    }
}

void GfFobjManager::gevGameObjLeave(GF_OBJ_HANDLE* handle) {
    leaveGameField(handle);
}

}  // namespace gf
