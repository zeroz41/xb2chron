#include "grlib/CGLibVtxVertex.h"
#include "ptlib/renderer/RendererStreamKizuna.h"
#include "math.h"

namespace ptlib { namespace renderer {

// 20 rings of 16 points round the z axis, radius 0.05, ring n at z = n; a point is 7 floats, of which the
// constructor sets the first three. The locals' names are not the original's; the fields are set in the order
// that schedules the original's stores
StreamObjKizuna::StreamObjKizuna() {
    m_pStream = nullptr;
    m_setupB = 1;
    m_setupA = 0x18;
    m_setupD = 1;
    m_setupC = 1;
    createVertexBuff(20 * 16 * 7 * sizeof(float), 7 * sizeof(float));
    void* pBuffer;
    unsigned int size;
    lock(&pBuffer, &size);
    float* pVertex = static_cast<float*>(pBuffer);
    int index = 0;
    for (int ring = 0; ring < 20; ring++) {
        for (int point = 0; point < 16; point++) {
            float angle = point * 6.2831855f * 0.0625f;
            pVertex[index * 7 + 0] = sinf(angle) * 0.05f;
            pVertex[index * 7 + 1] = cosf(angle) * 0.05f;
            pVertex[index * 7 + 2] = ring;
            index++;
        }
    }
    unlock();
}

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
