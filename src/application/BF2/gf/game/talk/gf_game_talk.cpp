#include "classes/event/Manager.h"
#include "classes/gf/GfGameTalk.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameTalk.h"

namespace gf {

GfGameTalk::GfGameTalk(const GfSetupParam& param) {
    initialize(param);
}

void GfGameTalk::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfGameTalk::~GfGameTalk() {}

void GfGameTalk::build(const GfSetupParam& param) {
#line 48
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameTalk(param);
}

void GfGameTalk::destroy() {
    GfGameTalk* talk = get();
    talk->finalize();
    delete talk;
}

void GfGameTalk::finalize() {
    m_initialized = false;
}

bool GfGameTalk::isInitialized() {
    GfGameTalk* talk = get();
    if (talk != nullptr) {
        return talk->m_initialized;
    }
    return false;
}

void GfGameTalk::update(const fw::UpdateInfo& info) {}

bool GfGameTalk::isPlaying() {
    return event::Manager::get()->isPlaying();
}

void GfGameTalk::end() {
    event::Manager::get()->end();
}

}  // namespace gf
