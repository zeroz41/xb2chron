#ifndef CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H
#define CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "grlib/CGLibMemPoolAdder.h"
#include "grlib/CGLibPipeline.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibDisplay.h"
#include "grlib/CGLibState.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibBuffSamplerTbl.h"
#include "grlib/CGLibBuffFixAlloc.h"
#include "grlib/CGLibGpuTimeStamp.h"
namespace grlib { struct CGLibMemType; }

namespace grlib { namespace context { class CGLibSystemContext; }}

namespace grlib { namespace context {
// table 0x7100B79E78
// The field names are not the original's.
class CGLibSystemContext : public ::mm::mtl::PtrSingleton< ::grlib::context::CGLibSystemContext> {
public:
    CGLibSystemContext();
    virtual ~CGLibSystemContext();  // slot 0

    void setup();
    // true when everything was released
    bool cleanup();
    void begin();
    void end();

    // the etc uniform buffers' sizes (CGLibManager::deviceInit hands them to CGLibMemHandle::setup)
    static const unsigned int ETCBUFFER_128_SIZE;
    static const unsigned int ETCBUFFER_256_SIZE;
    static const unsigned int ETCBUFFER_512_SIZE;
    static const unsigned int ETCBUFFER_768_SIZE;
    static const unsigned int ETCBUFFER_1024_SIZE;

    bool isRelease();
    // the bytes of one counter report (CGLibOcclusionQuery double-buffers its reports)
    static unsigned int s_nvReportCounterSize;
    // the device's texture and sampler descriptor sizes and the descriptors it reserves at the start of each pool
    // (CGLibTexDescriptor/CGLibSamplerDescriptor::setup and the _plf register calls)
    static unsigned int s_nvTextureSize;
    static unsigned int s_nvSamplerSize;
    static int s_nNnumReservedTextures;
    static int s_nNumReservedSamplers;
    // the GPU address of a block's memory, into address
    void getVertexGpuAddress(unsigned long& address, const CGLibMemType& mem);
    // the GPU address of a uniform block's memory, into address
    void getUniformoGpuAddress(unsigned long& address, const CGLibMemType& mem);
    // the global uniform buffer's current position: its CPU pointer and its GPU address
    void getGlbUniformParam(unsigned char*& buffer, unsigned long& gpuAddress);
    // advances the global uniform buffer past size bytes (rounded up to 0x100)
    void nextGlbUniformOfs(unsigned int size);
    unsigned int getPixelResAreaOffset(unsigned int offset);
    // frees the block once the GPU is done with it
    void releaseDelayVertex(CGLibMemType& mem);
    // releases the pool (and frees the buffer, when one is passed) once the GPU is done with it
    void releaseDelayMempool(NVNmemoryPool* pool, void* buffer);
    // finalizes and frees the texture, frees the memory and the descriptor ids once the GPU is done with them
    void releaseDelayTexture(NVNtexture* texture, void* mem, int textureId, int samplerId);

    unsigned char pad_8[0x530];
    CGLibBuffFixAlloc m_texDescriptor;  // 0x538: texture and sampler descriptor ids (CGLibTextureBuffer::release)
    unsigned char pad_560[0x40];
    // 0x5A0: the sampler descriptor ids and pool (CGLibSamplerParam::setupResource/releaseParams; the name is not the
    // original's)
    CGLibSamplerDescriptor m_samplerDescriptor;
    CGLibBuffSamplerTbl m_samplerTbl;  // 0x608: CGLibSampler::updateData
    CGLibBuffOcclusion m_occlusion;  // 0xE38: CGLibOcclusionQuery's report slots
    CGLibBuffFixAlloc m_textureAlloc;  // 0xE60: the NVNtexture objects (CGLibTextureBuffer::release)
    unsigned char pad_E88[0x8];
    CGLibBuffMemPoolTbl m_memPoolTbl;  // 0xE90: CGLibMemPool takes its NVNmemoryPool objects from it (the name is not the original's)
    unsigned char pad_EB8[0x40];
    CGLibMemPoolAdder m_memPoolAdder;  // 0xEF8: CGLibGPUCache's pools
    // the five etc buffers (ArgMemInfo m_etc128Size..m_etc1024Size); CGLibMemHandle::free indexes them by
    // CGLibMemType::m_type (the name is not the original's)
    CGLibBuffMinUniform m_etcBuffer[5];  // 0xF08
    CGLibPipeline m_pipeline;  // 0x1070
    CGLibDisplay m_display;  // 0x1110
    unsigned char pad_2120[0x200];
    CGLibDecShader m_decShader;  // 0x2320: CGLibCtlShader::getDecShader
    CGLibVtxFetch m_vtxFetches[3];  // 0x2388: CGLibCtlShader::getVtxFetch
    CGLibSampler m_samplers[2];  // 0x23B8: CGLibCtlShader::getSampler (CGLibUtilObj's constructor builds two)
    unsigned char pad_23F8[0x60];
    NVNmemoryPool* m_pReportPool;  // 0x2458: the pool the occlusion reports are written to
    unsigned char pad_2460[0x10];
    unsigned char* m_pReportPoolMem;  // 0x2470: its memory
    NVNmemoryPool* m_pPixelPool;  // 0x2478: the pool pixel memory comes from
    unsigned char pad_2480[0x10];
    unsigned char* m_pPixelPoolMem;  // 0x2490: its memory
    unsigned char pad_2498[0x40];
    CGLibGpuTimeStamp m_gpuTimeStamp;  // 0x24D8: end() ends it, CGLibManager::getGpuTimeStamp reads it
    unsigned char pad_2540[0x8];
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
