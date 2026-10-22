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

    // set once by the constructor (0x18, 1, 1, 1) and read by nothing in the module: the names are not the
    // original's
    unsigned int m_setupA;
    unsigned int m_setupB;
    unsigned short m_setupC;
    unsigned char m_setupD;
    unsigned char pad_33[0x5];
    void* m_pStream;  // where lockStream maps the buffer
};

}}  // namespace ptlib::renderer

#endif
