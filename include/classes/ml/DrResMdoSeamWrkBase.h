#ifndef CLASSES_ML_DRRESMDOSEAMWRKBASE_H
#define CLASSES_ML_DRRESMDOSEAMWRKBASE_H

namespace grlib {
class CGLibVtxInstans;
}

namespace ml {
class DrMdoCtlSeamBaseMap;
class DrPixlShadowObj;
class DrPixlShadowCacheObj;
struct MdsSeamBaMpTreeData;
class DrResMdoSeamMemObj;
class DrResMdoVertex;
struct MdoWrkMatRes;

// table 0x7100B7DB00
class DrResMdoSeamWrkBase {
public:
    virtual ~DrResMdoSeamWrkBase();  // slot 0
    void release();
    void releaseCache(DrMdoCtlSeamBaseMap* ctl);
    void beginRender();
    void endRender();
    void selectVertex(int index);
    void seachDefShadowBaseMapRender(DrPixlShadowObj* shadow, DrMdoCtlSeamBaseMap* ctl);
    void seachDefShadowBaseMapRenderChild(DrPixlShadowObj* shadow, DrMdoCtlSeamBaseMap* ctl,
                                          const MdsSeamBaMpTreeData* tree);
    void callShadowCacheBaseUpdate(unsigned long mask);
    bool seachShadowBaseMapRender(DrPixlShadowCacheObj& cache, DrMdoCtlSeamBaseMap* ctl);
    bool seachShadowBaseMapRenderChild(DrPixlShadowCacheObj& cache, DrMdoCtlSeamBaseMap* ctl,
                                       const MdsSeamBaMpTreeData* tree);
    void setVertexCache(unsigned int cacheIdx, DrResMdoSeamMemObj* memObj, int param, DrMdoCtlSeamBaseMap* ctl);

    // one entry of the vertex list release walks (the names are not the original's)
    struct VertexEntry {
        DrResMdoSeamMemObj* memObj;  // cleared by release; releaseCache hands it back to the map
        DrResMdoVertex* vertex;
        unsigned char pad_10[0x8];
    };

    // the seam data's head: bit 2 of its first byte skips the default shadow render (the names are not the original's)
    struct SeamHeader {
        unsigned char m_flags;
    };

    // 0x8: the next work in DrMdoCtlSeam::m_pBaseList (DrMdoCtlSeamAll::callShadowCacheUpdate walks it; the name
    // is not the original's)
    DrResMdoSeamWrkBase* m_pLink;
    unsigned char pad_10[0x10];
    const SeamHeader* m_header;  // 0x20 (the name is not the original's)
    unsigned char pad_28[0x10];
    const MdsSeamBaMpTreeData* m_baseMapTree;  // 0x38: the root seachDefShadowBaseMapRender walks (the name is not the original's)
    unsigned char pad_40[0x28];
    MdoWrkMatRes* m_matRes;  // 0x68: setupWork's matRes, freed by release (the name is not the original's)
    void* m_matWork;  // 0x70: freed by release (the name is not the original's)
    VertexEntry* m_vertexList;  // 0x78: m_vertexNum entries (the name is not the original's)
    unsigned char pad_80[0x18];
    // 0x98: one bit per shadow cache (DrPixlShadowCacheObj::m_cacheBit) already rendered; callShadowCacheBaseUpdate
    // clears the bits it is given (the name is not the original's)
    unsigned long m_shadowCacheDone;
    // 0xA0: DrMdoCtlSeamRead::waitBaseVertexStream sets bit 4 when the vertex stream ends without its data
    unsigned int m_cacheFlags;
    unsigned char pad_A4[0x4];
    void** m_bufList;  // 0xA8: m_bufNum buffers freed by release (the name is not the original's)
    int m_bufNum;      // 0xB0 (the name is not the original's)
    unsigned char pad_B4[0x2C];
    unsigned int* m_nodeBits;  // 0xE0: one bit per tree node, cleared by release (the name is not the original's)
    void* m_nodeWork;  // 0xE8: cleared by release (the name is not the original's)
    void** m_shadowCacheBuf;             // 0xF0: 36 buffers, one per shadow cache (the name is not the original's)
    unsigned int m_shadowCacheBufSize;   // 0xF8: bytes of each buffer (the name is not the original's)
    unsigned char pad_FC[0x4];
    void* m_curShadowCacheBuf;           // 0x100: the buffer of the cache being rendered (the name is not the original's)
    unsigned char pad_108[0x50];
    unsigned long m_readMask;  // 0x158: cleared by release (the name is not the original's)
    unsigned char pad_160[0x8];
    grlib::CGLibVtxInstans* m_instans;  // 0x168: released and destroyed by release (the name is not the original's)
    unsigned char pad_170[0x8];
    short m_selectVertex;  // 0x178: the entry selectVertex last chose, -1 after beginRender (the name is not the original's)
    unsigned char pad_17A[0x4];
    short m_vertexNum;     // 0x17E: entries of m_vertexList (the name is not the original's)
};
}  // namespace ml

#endif
