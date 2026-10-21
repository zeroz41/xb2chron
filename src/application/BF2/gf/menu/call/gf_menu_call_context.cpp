#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"

namespace gf {

// numbers the contexts create makes
static unsigned int s_nextId = 1;

GfMenuCallContext::~GfMenuCallContext() {}

GfMenuCallContext* GfMenuCallContext::create() {
#line 54
    GfMenuCallContext* context = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuCallContext;
    context->m_id = s_nextId;
    s_nextId++;
    // the caller holds its one reference: the original stores the count after the numbering, not with the base
    context->m_RefCount = 1;
    return context;
}

int GfMenuCallContext::getState() {
    if (isTerm()) {
        return 2;
    }
    return isActive() ? 1 : 0;
}

bool GfMenuCallContext::isTerm() const {
    if (m_handle != 0) {
        ui::UIObjectAcc acc(m_handle);
        if (acc.isTerm()) {
            return true;
        }
    }
    return m_terminated;
}

bool GfMenuCallContext::isActive() const {
    return m_handle != 0;
}

void GfMenuCallContext::reset() {
    if (!m_terminated) {
        terminate();
    }
    m_terminated = false;
    m_objectId = 0;
    m_results.clear();
}

void GfMenuCallContext::terminate() {
    m_terminated = true;
    m_handle = 0;
}

void GfMenuCallContext::abort() {
    if (m_handle != 0) {
        ui::EventData event;
        event.m_type = 2;
        ui::UIManager::get()->requestObjectEvent(m_handle, event, 0.0f);
    } else {
        m_terminated = true;
    }
}

bool GfMenuCallContext::popResult(GfMenuResult& result) {
    if (m_results.empty()) {
        return false;
    }
    result = *m_results.begin();
    m_results.erase(m_results.begin());
    return true;
}

void GfMenuCallContext::addResult(const GfMenuResult& result) {
    if (m_results.size() < m_results.capacity()) {
        m_results.push_back(result);
    }
}

void GfMenuCallContext::setup(unsigned int handle, unsigned int objectId) {
    if (!isActive()) {
        m_terminated = false;
        m_handle = handle;
        m_objectId = objectId;
    }
}

void GfMenuCallContext::callNext(unsigned int objectId) {
    if (isActive()) {
        m_objectId = objectId;
    }
}

}  // namespace gf
