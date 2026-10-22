#include "grlib/CGLibVtxVertex.h"
#include "ptlib/renderer/RendererStreamKizuna.h"

namespace ptlib { namespace renderer {

StreamObjKizuna::~StreamObjKizuna() {
    delayRelease();
}

void* StreamObjKizuna::lockStream(const DrDrawWorkInfoEF* pDrInfo) {
    unsigned int size;
    lock(&m_pStream, &size);
    return m_pStream;
}

void StreamObjKizuna::unlockStream(const DrDrawWorkInfoEF* pDrInfo) {
    unlock();
}

}}  // namespace ptlib::renderer
