#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace gf {

GfMenuCallManager::~GfMenuCallManager() {
    for (CallInfo* it = m_calls.begin(); it != m_calls.end(); ++it) {
        if (it->m_context != nullptr) {
            it->m_context->release();
            it->m_context = nullptr;
        }
    }
    m_calls.clear();
}

bool GfMenuCallManager::canCall(unsigned int id) const {
    if (id <= 0x90) {
        return m_handles[id] != 0;
    }
    return false;
}

void GfMenuCallManager::build(const GfSetupParam& param) {
#line 75
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuCallManager(param);
}

void GfMenuCallManager::destroy() {
    if (GfMenuCallManager* manager = get()) {
        delete manager;
    }
}

bool GfMenuCallManager::isInitialized() {
    return true;
}

void GfMenuCallManager::postUpdate(const fw::UpdateInfo& info) {
    GfMenuCallManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    for (CallInfo* it = manager->m_calls.begin(); it != manager->m_calls.end();) {
        if (it->m_context->isTerm() || it->m_context->m_RefCount == 1) {
            if (it->m_context != nullptr) {
                it->m_context->release();
                it->m_context = nullptr;
            }
            manager->m_calls.erase(it);
        } else {
            ++it;
        }
    }
}

void GfMenuCallManager::reciveUIEvent(const ui::EventData& event, unsigned int handle) {
    mm::mtl::FixedVector<CallInfo, 256>& calls = get()->m_calls;
    if (event.m_type == 9) {
        for (CallInfo* it = calls.begin(); it != calls.end(); ++it) {
            if (it->m_context->m_handle == handle) {
                if (it->m_eventHandler != 0) {
                    ui::EventData data;
                    data.m_type = 0x42;
                    data.m_param0 = it->m_context->m_id;
                    data.m_param1 = it->m_context->m_objectId;
                    ui::UIManager::get()->requestObjectEvent(it->m_eventHandler, data, 0.0f);
                }
                it->m_context->terminate();
                if (it->m_context != nullptr) {
                    it->m_context->release();
                    it->m_context = nullptr;
                }
                calls.erase(it);
                return;
            }
        }
    } else if (event.m_type == 8) {
        for (CallInfo* it = calls.begin(); it != calls.end(); ++it) {
            if (it->m_context->m_handle == handle) {
                GfMenuCallContext::GfMenuResult result;
                result.m_id = event.m_param0;
                result.m_value = event.m_param1;
                it->m_context->addResult(result);
                if (it->m_eventHandler != 0) {
                    ui::EventData data;
                    data.m_type = 0x41;
                    data.m_param0 = it->m_context->m_id;
                    data.m_param1 = it->m_context->m_objectId;
                    data.m_param2 = result.m_id;
                    data.m_param3 = result.m_value;
                    ui::UIManager::get()->requestObjectEvent(it->m_eventHandler, data, 0.0f);
                }
            }
        }
    }
}

void GfMenuCallManager::attachCall(unsigned int id, unsigned int handle) {
    m_handles[id] = handle;
}

void GfMenuCallManager::detachCall(unsigned int id) {
    if (id <= 0x90 && m_handles[id] != 0) {
        m_handles[id] = 0;
    }
}

unsigned int GfMenuCallManager::getAttachedObject(unsigned int id) {
    if (id <= 0x90) {
        return m_handles[id];
    }
    return 0;
}

unsigned short GfMenuCallManager::registString(const ui::UIStr& text) {
    return m_strLinker.addString(text);
}

void GfMenuCallManager::releaseString(unsigned short id) {
    m_strLinker.delString(id);
}

const ui::UIStr& GfMenuCallManager::getString(unsigned short id) {
    return m_strLinker.getString(id);
}

void GfMenuCallManager::startCallContext(GfMenuCallContext* context, unsigned int id, unsigned int handle) {
    if (m_calls.size() == m_calls.capacity()) {
        return;
    }
    if (context->isActive() && !context->isTerm()) {
        return;
    }
    for (CallInfo* it = m_calls.begin(); it != m_calls.end(); ++it) {
        if (it->m_context->m_id == context->m_id) {
            context->setup(handle, id);
            return;
        }
    }
    context->setup(handle, id);
    context->addRef();
    CallInfo info;
    info.m_context = context;
    info.m_eventHandler = 0;
    m_calls.push_back(info);
}

void GfMenuCallManager::nextCallContext(GfMenuCallContext* context, unsigned int id) {
    if (context->isActive()) {
        context->callNext(id);
    }
}

void GfMenuCallManager::setCallContextEventHandler(GfMenuCallContext* context, unsigned int handle) {
    for (CallInfo* it = m_calls.begin(); it != m_calls.end(); ++it) {
        if (it->m_context->m_id == context->m_id) {
            it->m_eventHandler = handle;
            return;
        }
    }
}

}  // namespace gf
