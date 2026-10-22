#ifndef PTLIB_RENDERER_RENDERERSTREAMKIZUNA_H
#define PTLIB_RENDERER_RENDERERSTREAMKIZUNA_H

#include "grlib/CGLibVtxVertex.h"

namespace ptlib { class DrDrawWorkInfoEF; }
namespace ptlib { namespace renderer { class RenderSet2; } }

namespace ptlib { namespace renderer {

// the vertex stream the bond (kizuna) lines draw from: rings of points round a unit tube
// (particle_renderer_stream_kizuna.cpp)
class StreamObjKizuna : public grlib::CGLibVtxVertex {
public:
    StreamObjKizuna();
    ~StreamObjKizuna();
    void* lockStream(const DrDrawWorkInfoEF* pDrInfo);
    void unlockStream(const DrDrawWorkInfoEF* pDrInfo);
    void renderStreamNum(RenderSet2& set, const DrDrawWorkInfoEF* pDrInfo);

    unsigned char pad_28[0x10];  // the constructor sets 0x28-0x32 (see notes)
    void* m_pStream;  // where lockStream maps the buffer
};

}}  // namespace ptlib::renderer

#endif
