#include "mm/mtl/FixedList.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"
#include "classes/ai/AiData.h"
#include "classes/ai/AiScriptManager.h"
#include "classes/ai/AiManager.h"
#include "classes/ai/AiScriptDataManager.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"

namespace ai {

void AiManager::init() {
    AiScriptDataManager::init();
    AiScriptManager::init();
    gf::GfObjManager::addListener(this, static_cast<gf::IGfObjListener::OBJEVT>(0));
}

void AiManager::destroy() {
    gf::GfObjManager::removeListener(this);
    _clear();
    AiScriptDataManager::destroy();
    AiScriptManager::destroy();
}

void AiManager::_clear() {
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end();) {
        AiData*& data = *it;
        AiScriptManager::end(AiScriptDataManager::getScriptName(data->getId()));
        if (*it) {
            delete data;
            data = nullptr;
        }
        it = m_dataList.erase(it);
    }
}

void AiManager::update(const fw::UpdateInfo& info) {
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        (*it)->update(info);
    }
    AiScriptDataManager::update(info);
    AiScriptManager::update(info);
}

void AiManager::regist(gf::GF_OBJ_HANDLE* handle, int id) {
#line 61
    AiData* data = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) AiData();
    data->setHandle(handle);
    data->setId(id);
    data->init();
    m_dataList.push_back(data);
    AiScriptManager::start(AiScriptDataManager::getScriptName(id));
}

void AiManager::unregist(gf::GF_OBJ_HANDLE* handle) {
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end();) {
        AiData*& data = *it;
        if (data->getHandle() == handle) {
            AiScriptManager::end(AiScriptDataManager::getScriptName(data->getId()));
            if (data) {
                delete data;
                data = nullptr;
            }
            it = m_dataList.erase(it);
        } else {
            ++it;
        }
    }
}

AiData* AiManager::getDataFromHandle(gf::GF_OBJ_HANDLE* handle) {
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        AiData* data = *it;
        if (data->getHandle() == handle) {
            return data;
        }
    }
    return nullptr;
}

AiData* AiManager::getDataFromId(int id, int index) {
    AiData* result = nullptr;
    int count = 0;
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        AiData* data = *it;
        if (data->getId() == id) {
            if (count == index) {
                result = data;
                break;
            }
            count++;
        }
    }
    return result;
}

int AiManager::getNumFromId(int id) {
    int count = 0;
    for (DataList::iterator it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        if ((*it)->getId() == id) {
            count++;
        }
    }
    return count;
}

// event 3: the object is going (the event's name is not known)
void AiManager::listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int) {
    if (evt == static_cast<gf::IGfObjListener::OBJEVT>(3)) {
        unregist(handle);
    }
}

AiManager::~AiManager() {}

}  // namespace ai
