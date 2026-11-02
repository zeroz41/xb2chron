#include "classes/fw/ResourceManager.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/gf/GfPause.h"
#include "gf/GfStaticRes.h"
#include "gf/GfSetupParam.h"
#include "classes/fw/CommonResource.h"
#include "mtl/MemManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/IGfEvent.h"
#include "classes/fw/ResourceManager.h"
#include "ml/MlMem.h"
#include "gf/GfSoundSource.h"

namespace gf {

GfPause::~GfPause() {}

void GfPause::build(const GfSetupParam& param) {
#line 46
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfPause(param);
}

void GfPause::destroy() {
    GfPause* self = get();
    self->finalize();
    delete self;
}

void GfPause::destroyPauseHandle(GF_PAUSE_HANDLE* handle) {
    unsigned int index = reinterpret_cast<unsigned long>(handle) & 0x3F;
    m_kinds.free(index);
    HandleList::iterator it = m_handles.find(handle);
    if (it != m_handles.end()) {
        m_handles.erase(it);
    }
}

void GfPause::destroyHandle(GF_PAUSE_HANDLE* handle) {
    if (handle != reinterpret_cast<GF_PAUSE_HANDLE*>(-1)) {
        get()->m_releases.push_back(handle);
    }
}

bool GfPause::isPause(unsigned int kind) {
    return (get()->m_pauseBit & kind) == kind;
}

}  // namespace gf
