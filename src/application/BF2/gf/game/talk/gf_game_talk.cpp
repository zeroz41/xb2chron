#include "classes/event/Manager.h"
#include "classes/gf/GfGameTalk.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameTalk.h"
#include "plugin/Bdat.h"
#include "gf/GfSetupPfTalk.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

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

void GfGameTalk::play(const GfSetupPfTalk& talk) {
    unsigned char* list = Bdat::getFP("EVT_listList");
    int top = Bdat::getIdTop(list);
    int count = Bdat::getIdCount(list);
    for (int i = top; i < top + count; i++) {
        unsigned char* seat = Bdat::getFP(reinterpret_cast<const char*>(Bdat::getVal(list, "listSeat", i)));
        int seatTop = Bdat::getIdTop(seat);
        int seatCount = Bdat::getIdCount(seat);
        if (talk.m_eventId >= seatTop && seatTop + seatCount > talk.m_eventId) {
            mm::mtl::FixStr<64> name(reinterpret_cast<const char*>(Bdat::getVal(seat, "evtName", talk.m_eventId)));
            if (name.m_str[0] == '\0') {
                return;
            }
            if (!event::Manager::get()->isDebugPlayOnetime() &&
                static_cast<unsigned short>(Bdat::getVal(seat, "linkID", talk.m_eventId)) != 0) {
                name += "_link";
            }
            // the category is read and not used
            Bdat::getVal(seat, "category", talk.m_eventId);
            event::Manager::get()->play(name.m_str, talk.m_handle, talk.pad_10, talk.m_npcTurn, 0, 0, mm::Vec3::zero,
                                        0.0f);
            return;
        }
    }
}

bool GfGameTalk::isPlaying() {
    return event::Manager::get()->isPlaying();
}

void GfGameTalk::end() {
    event::Manager::get()->end();
}

}  // namespace gf
