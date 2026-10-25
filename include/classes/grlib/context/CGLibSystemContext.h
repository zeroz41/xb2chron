#ifndef CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H
#define CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "grlib/CGLibMemPoolAdder.h"
#include "grlib/CGLibPipeline.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibState.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibSampler.h"
namespace grlib { struct CGLibMemType; }

namespace grlib { namespace context { class CGLibSystemContext; }}

namespace grlib { namespace context {
// table 0x7100B79E78
// The field names are not the original's.
class CGLibSystemContext : public ::mm::mtl::PtrSingleton< ::grlib::context::CGLibSystemContext> {
public:
    virtual ~CGLibSystemContext();  // slot 0

    bool isRelease();
    // the GPU address of a block's memory, into address
    void getVertexGpuAddress(unsigned long& address, const CGLibMemType& mem);
    // the global uniform buffer's current position: its CPU pointer and its GPU address
    void getGlbUniformParam(unsigned char*& buffer, unsigned long& gpuAddress);
    // advances the global uniform buffer past size bytes (rounded up to 0x100)
    void nextGlbUniformOfs(unsigned int size);
    unsigned int getPixelResAreaOffset(unsigned int offset);
    // frees the block once the GPU is done with it
    void releaseDelayVertex(CGLibMemType& mem);

    unsigned char pad_8[0xEF0];
    CGLibMemPoolAdder m_memPoolAdder;  // 0xEF8: CGLibGPUCache's pools
    unsigned char pad_F08[0x168];
    CGLibPipeline m_pipeline;  // 0x1070
    CGLibRenderTarget m_mainRenderTargets[2];  // 0x1110: the display's, m_mainIndex picks the current one
    unsigned char pad_18A0[0x120];
    CGLibDepthBuffer* m_pMainDepthBuffer;  // 0x19C0
    unsigned char pad_19C8[0x70C];
    int m_mainIndex;  // 0x20D4
    unsigned char pad_20D8[0x248];
    CGLibDecShader m_decShader;  // 0x2320: CGLibCtlShader::getDecShader
    CGLibVtxFetch m_vtxFetches[3];  // 0x2388: CGLibCtlShader::getVtxFetch
    CGLibSampler m_samplers[6];  // 0x23B8: CGLibCtlShader::getSampler
    NVNmemoryPool* m_pPixelPool;  // 0x2478: the pool pixel memory comes from
    unsigned char pad_2480[0x10];
    unsigned char* m_pPixelPoolMem;  // 0x2490: its memory
    unsigned char pad_2498[0xB0];
    unsigned long m_glbUniformGpuAddress;  // 0x2548
    unsigned char* m_pGlbUniformBuffer;  // 0x2550
    unsigned char pad_2558[0x10];
    unsigned long m_glbUniformOffset;  // 0x2568
    unsigned char pad_2570[0x4];
    unsigned int m_glbUniformRest;  // 0x2574: the bytes left
    unsigned char pad_2578[0x8];
    void* m_pPixelResArea;  // 0x2580: CGLibState::setPixelResidentArea's
    void* m_pPixelResAreaPrev[2];  // 0x2588: the area each CGLibManager::s_nStkNowIdx half had before
    unsigned int m_pixelResAreaSize;  // 0x2598
    unsigned long m_pixelResAreaGpuAddress;  // 0x25A0
    unsigned int m_pixelResAreaOffset;  // 0x25A8
    int m_renderTargetNum;  // 0x25AC
    const NVNtextureView* m_renderTargetViews[8];  // 0x25B0
    const NVNtexture* m_renderTargets[8];  // 0x25F0
    LibMainStateViewPort m_viewport;  // 0x2630
    const NVNtexture* m_pDepthTarget;  // 0x2648
};
}}  // namespace grlib::context

#endif
