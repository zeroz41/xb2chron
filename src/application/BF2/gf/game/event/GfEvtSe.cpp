#include "gf/GfEvtSe.h"
#include "classes/fw/SoundResource.h"
#include "classes/fw/FrameworkMemory.h"

namespace gf {

GfEvtSe::GfEvtSe() : m_isCleanup(false) {}

GfEvtSe::~GfEvtSe() {}

void GfEvtSe::cleanup() {
    destroySe();
    m_isCleanup = true;
}

void GfEvtSe::destroySe() {
    for (SeInfo& se : m_ses) {
        fw::SoundResource* resource = se.m_resource;
        se.m_name.clear();
        se.m_pack = nullptr;
        if (resource != nullptr) {
            resource->release();
            se.m_resource = nullptr;
        }
    }
    m_ses.clear();
}

void GfEvtSe::createSe(const char* name) {
    if (name == nullptr || name[0] == '\0') {
        return;
    }
    mm::mtl::FixStr<128> path;
    path.format("sound/se/%s%s", name, ".xsp");
    fw::SoundResource::SetupInfo info;
    info.pad_8 = 0x80;
    info.pad_0 = 12;
    info.pad_4 = 0;
    fw::SoundResource* resource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), path.m_str, info,
                                                             static_cast<fw::LOAD_PRIO>(10));
    SeInfo se;
    se.m_name = name;
    se.m_resource = resource;
    se.m_pack = nullptr;
    m_ses.push_back(se);
}

// isLoadedSe (0x71002A0498) is not written yet: its code keeps clang's cleanup-destination switch (null resource 3,
// loaded 0, not loaded 1, loop end 2), which a plain range-for does not leave; a local with a non-trivial (empty)
// destructor around the loop reproduces it, and what that local was is not known.

}  // namespace gf
