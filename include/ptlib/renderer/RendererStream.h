#ifndef PTLIB_RENDERER_RENDERERSTREAM_H
#define PTLIB_RENDERER_RENDERERSTREAM_H

#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibVtxIndex.h"

namespace ptlib { class StaticAllocObj; }
namespace ptlib { class DrDrawWorkInfoEF; }
namespace ptlib { namespace renderer { class RenderSet; } }

namespace ptlib {
// a particle vertex's layout (StreamObj::init's; no value has a name yet: 1 is the stream's own buffer)
enum FxVertexType : int {};
}  // namespace ptlib

namespace ptlib { namespace renderer {

// the renderer's shared sampler, vertex fetch and index state (particle_renderer_stream.cpp). The names of the
// members other than the functions' are not the original's.
class EffStateManager {
public:
    EffStateManager();
    ~EffStateManager();
    static EffStateManager* get();
    void init(StaticAllocObj* pAlloc);
    void initSampler();
    void initVtxFetch();
    void initVtxIndex();
    // the frame's instances start again
    void begin();

    static EffStateManager* s_instance;  // the constructor sets it, the destructor clears it

    grlib::CGLibSampler m_samplers[32];
    // the vertex fetch objects of the streams' sizes 16?, 20, 24, ... 40 (StreamObj::initFetchVertex takes
    // [1] to [6]); the destructor releases each with its instanced counterpart
    grlib::CGLibVtxFetch m_fetch[7];
    grlib::CGLibVtxFetch m_instanceFetch[7];
    grlib::CGLibVtxFetch m_otherFetch[2];
    grlib::CGLibVtxVertex m_vertex;  // the vertices the instanced streams share
    grlib::CGLibVtxVertex m_otherVertex;
    // an index buffer the destructor leaves alone, and the ones it releases
    grlib::CGLibVtxIndex m_keptIndex;
    grlib::CGLibVtxIndex m_index[4];
    grlib::CGLibVtxInstans m_instans;  // the instanced streams' per-instance data
    unsigned char pad_648[0xD8];  // RenderManager::init allocates 0x720 bytes for it; the constructor leaves these
};

// how many bytes a particle's stream data takes: 20 to 40, by fours (no value has a name yet)
enum STREAM_SIZE_TYPE : int {};

// a particle renderer's vertex stream (particle_renderer_stream.cpp). The names of the fields are not the original's.
class StreamObj {
public:
    void init(STREAM_SIZE_TYPE size, unsigned int count, FxVertexType type);
    void release();
    void releaseSub();
    // the fetch objects of the size and type
    void initFetchVertex();
    // where to write the frame's stream data
    void* lockStream(const DrDrawWorkInfoEF* pDrInfo);
    // count particles' data written
    void unlockStream(const DrDrawWorkInfoEF* pDrInfo, unsigned int count);
    void renderStreamNum(RenderSet& set, const DrDrawWorkInfoEF* pDrInfo);

    grlib::CGLibVtxFetch* m_pFetch;
    grlib::CGLibVtxFetch* m_pInstanceFetch;
    grlib::CGLibVtxVertex* m_pVertex;  // its own or EffStateManager's
    grlib::CGLibVtxVertex m_vertex;
    int m_indexType;  // 2 with its own vertices, 0 with the shared ones: renderStreamNum's index buffer
    STREAM_SIZE_TYPE m_size;
    unsigned int m_offset;  // where the frame's instances start
    FxVertexType m_type;
    bool m_initialized;
};

}}  // namespace ptlib::renderer

#endif
