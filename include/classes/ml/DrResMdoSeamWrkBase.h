#ifndef CLASSES_ML_DRRESMDOSEAMWRKBASE_H
#define CLASSES_ML_DRRESMDOSEAMWRKBASE_H

#include "mm/Vec3.h"
#include "grlib/CGLibVtxInstans.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "mtl/MemManager.h"

namespace grlib { class CGLibTriUniformArray; }

namespace ml {
class DrMdoCtlSeamBaseMap;
class DrCalcViewWork;
class DrResMdoSeamParmRead;
class DrPixlShadowObj;
class DrPixlShadowCacheObj;
// a node of the base map's tree (0x18 bytes; the type name is the symbols', the field names are not the original's)
struct MdsSeamBaMpTreeData {
    float m_pos[3];  // the bounding sphere's centre
    float m_radius;  // 0xC
    unsigned short m_childStart;  // 0x10: first of the node's entries in DrResMdoSeamWrkBase::m_nodeChildIdx
    unsigned short m_childNum;    // 0x12
    unsigned short m_mdlStart;    // 0x14: first of the node's entries in DrResMdoSeamWrkBase::m_nodeMdlIdx
    unsigned short m_mdlNum;      // 0x16
    const mm::Vec3& getPos() const { return *reinterpret_cast<const mm::Vec3*>(m_pos); }
};
class DrResMdoSeamMemObj;
class DrResMdoSeamTexList;
class DrResMdoVertex;
struct MdoWrkMatRes;
class DrResMdoAlpTbl;

// the head of a seam base map's data (name from setupWork's symbol; the field names are not the original's, laid
// out like MdsSeamInstMapHead's)
struct MdsSeamBaseMapHead {
    unsigned char pad_0[0xC];
    // 0xC..0x14: offsets of data blocks: [1] and [0] go to DrMdoMat::initBaseMapMaterial and resetBaseMapMaterial,
    // [2] (0 when there is none) is the MdsSeamInstMatBlock of the material resources
    unsigned int m_dataOfs[3];
    unsigned char pad_18[0x8];
    int m_matArg;           // 0x20: initBaseMapMaterial's and resetBaseMapMaterial's last argument
    unsigned int m_optOfs;  // 0x24: their third data block, 0 when there is none
    unsigned char pad_28[0x4];
    unsigned int m_extOfs;  // 0x2C: their fourth data block
};

// table 0x7100B7DB00
// 0x8/0x10 are DrResChankList node links (a base, as in DrResMdoSeamWrkEnv: the constructor zeroes them before it
// stores the table; DrMdoCtlSeam::setupSeamMapHead chains the works through them).
class DrResMdoSeamWrkBase : public DrResChankList<DrResMdoSeamWrkBase>::Node {
public:
    DrResMdoSeamWrkBase();
    virtual ~DrResMdoSeamWrkBase();  // slot 0
    void calcCacheInfo();
    // true when the work is to be released (DrMdoCtlSeamBaseMap::readBaseMapCheck; the parameter names are not the
    // original's)
    bool update(DrCalcViewWork* view, const DrResMdoSeamParmRead* parm, bool readAll, unsigned int seamFlags);

    // readBaseMapCheck sets them each frame from DrMdoCtlSeamBaseMap's and DrMan's values
    static float SEAM_BASEMAP_READ_CHECK;
    static float SEAM_BASEMAP_READ_IN_CHECK;
    static float SEAM_BASEMAP_VERTEX_CHECK;
    static float SEAM_BASEMAP_VERTEX_MIDDLE;
    bool callTexReadUpdate(unsigned short* texListNo, DrResMdoSeamTexList* texLists, DrMdoCtlSeamBaseMap* ctl);
    // whether the vertex list entry index is ready (bit of m_nodeBits; the name is not the original's)
    bool isVertexReady(int index) const { return m_nodeBits[index >> 5] & (1 << (index & 31)); }
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
    void setupWork(MdoWrkMatRes* matRes, grlib::CGLibTriUniformArray* triArray, mtl::ALLOC_HANDLE handle,
                   DrMdoCtlSeamBaseMap* ctl, const MdsSeamBaseMapHead* head, unsigned int);
    void setVertexCache(unsigned int cacheIdx, DrResMdoSeamMemObj* memObj, int param, DrMdoCtlSeamBaseMap* ctl);

    // one entry of the vertex list release walks (the names are not the original's)
    struct VertexEntry {
        DrResMdoSeamMemObj* memObj;  // cleared by release; releaseCache hands it back to the map
        DrResMdoVertex* vertex;
        unsigned char pad_10[0x8];
    };

    // a model of the base map (0x28 bytes): m_mdlNo and, with bit 9 of m_cacheFlags, m_altMdlNo index
    // MdoWrkMatRes::m_pMdlTop and m_mdlVertex (the names are not the original's)
    struct MdlEntry {
        unsigned int m_mdlNo;
        unsigned int m_altMdlNo;  // 0x4
        unsigned char pad_8[0x4];
        float m_pos[3];  // 0xC: the bounding sphere's centre
        unsigned char pad_18[0xC];
        float m_radius;  // 0x24
        const mm::Vec3& getPos() const { return *reinterpret_cast<const mm::Vec3*>(m_pos); }
    };

    // m_num: the models with an alternate (calcCacheInfo; the names are not the original's)
    struct MdlCount {
        unsigned char pad_0[0x4];
        int m_num;  // 0x4
    };

    // the seam data's head: bit 2 of its first byte skips the default shadow render (the names are not the original's)
    struct SeamHeader {
        unsigned char m_flags;
        unsigned char pad_1[0x1B];
        unsigned int m_texRefOfs;  // 0x1C: offset of the m_texRefNum TexRef
        int m_texRefNum;           // 0x20
        unsigned char pad_24[0xC];
        unsigned int m_texListOfs;  // 0x30: offset of the m_texListNum texture list numbers
        int m_texListNum;           // 0x34
    };

    // a material texture of the seam data: texture m_texNo of texture list m_listNo when bit 0 of m_flags is set
    // (callTexReadUpdate; the names are not the original's)
    struct TexRef {
        unsigned short m_texNo;
        unsigned short m_listNo;  // 0x2: index into m_texLists
        unsigned char pad_4[0x2];
        unsigned short m_flags;   // 0x6
    };
    // a part to draw in a pass list (0xC bytes; the names are not the original's)
    struct RenderEntry {
        unsigned int m_infoOfs;      // 0x0: the MdsMdlInfoHeader, from MdoWrkMatRes::m_pMdlInfo
        unsigned short m_next;       // 0x4: the next entry + 1 in m_renderEntries, 0 at the list's end
        unsigned short m_vertexIdx;  // 0x6: selectVertex's index
        unsigned short m_alpIdx;     // 0x8: the alpha table entry (the partsZPrePassRender's last argument)
        unsigned char pad_A[0x2];
    };
    // an entry (0x4C bytes) of the seam map head's base map table (DrMdoCtlSeam::MapHead::m_baseMapTblOfs); the
    // names are not the original's
    struct MapEntry {
        // 0x0, 0xC: the box DrMdoCtlSeamBaseMap::readBaseModelCheck tests the read positions against
        float m_max[3];
        float m_min[3];
        unsigned char pad_18[0x10];
        // 0x28: readBaseModelCheck skips entries with bit 3 while the seam flags' bit 4 is set, bit 2 with bit 8
        unsigned char m_flags;
        unsigned char pad_29[0xB];
        unsigned int m_ofs;   // 0x34: where the base map data starts (DrMdoCtlSeamRead::callBaseMapStream)
        unsigned int m_size;  // 0x38
        unsigned char pad_3C[0x10];
    };

    const MapEntry* m_mapEntry;  // 0x18: set by DrMdoCtlSeamRead::callBaseMapStream (the name is not the original's)
    const SeamHeader* m_header;  // 0x20 (the name is not the original's)
    unsigned char pad_28[0x8];
    const MdlEntry* m_mdlList;  // 0x30: the models the tree nodes list (the name is not the original's)
    const MdsSeamBaMpTreeData* m_baseMapTree;  // 0x38: the root seachDefShadowBaseMapRender walks (the name is not the original's)
    const unsigned short* m_nodeMdlIdx;    // 0x40: a node's m_mdlNum indices into m_mdlList (the name is not the original's)
    const unsigned short* m_nodeChildIdx;  // 0x48: a node's m_childNum indices into m_baseMapTree (the name is not the original's)
    const MdlCount* m_mdlCount;  // 0x50 (the name is not the original's)
    const unsigned short* m_mdlVertex;  // 0x58: the vertex list entry of each model (the name is not the original's)
    unsigned char pad_60[0x8];
    MdoWrkMatRes* m_matRes;  // 0x68: setupWork's matRes, freed by release (the name is not the original's)
    void* m_matWork;  // 0x70: freed by release (the name is not the original's)
    VertexEntry* m_vertexList;  // 0x78: m_vertexNum entries (the name is not the original's)
    unsigned char pad_80[0x4];
    int m_dataIdx;  // 0x84: its m_mapEntry's index (DrMdoCtlSeamRead::callBaseMapStream; the name is not the original's)
    unsigned char pad_88[0x10];
    // 0x98: one bit per shadow cache (DrPixlShadowCacheObj::m_cacheBit) already rendered; callShadowCacheBaseUpdate
    // clears the bits it is given (the name is not the original's)
    unsigned long m_shadowCacheDone;
    // 0xA0: DrMdoCtlSeamRead::waitBaseVertexStream sets bit 4 when the vertex stream ends without its data
    unsigned int m_cacheFlags;
    unsigned char pad_A4[0x4];
    void** m_bufList;  // 0xA8: m_bufNum buffers freed by release (the name is not the original's)
    int m_bufNum;      // 0xB0 (the name is not the original's)
    // 0xB4: cleared by the constructor; DrMdoCtlSeamRead::callBaseMapStream stores m_mapEntry's size (the name is not
    // the original's)
    int m_readSize;
    unsigned char pad_B8[0x28];
    unsigned int* m_nodeBits;  // 0xE0: one bit per tree node, cleared by release (the name is not the original's)
    // 0xE8: one bit per vertex list entry, set by calcCacheInfo from m_nodeBits; cleared by release (the name is
    // not the original's)
    unsigned int* m_nodeWork;
    void** m_shadowCacheBuf;             // 0xF0: 36 buffers, one per shadow cache (the name is not the original's)
    unsigned int m_shadowCacheBufSize;   // 0xF8: bytes of each buffer (the name is not the original's)
    unsigned char pad_FC[0x4];
    void* m_curShadowCacheBuf;           // 0x100: the buffer of the cache being rendered (the name is not the original's)
    unsigned char pad_108[0x10];
    // 0x118: by pass list (the z pre-pass's from 0, the thickness pass's from MdoWrkMatRes::m_matNum * 7), the first
    // RenderEntry of the list (the name is not the original's)
    RenderEntry** m_renderList;
    unsigned char pad_120[0x18];
    // 0x138: the lists of each pass: [0] the z pre-pass's, [7] the thickness pass's (the name is not the original's)
    int* m_renderNum;
    unsigned char pad_140[0x10];
    RenderEntry* m_renderEntries;  // 0x150: RenderEntry::m_next - 1 indexes it (the name is not the original's)
    // 0x158: the memory its stream reads into (DrMdoCtlSeamRead::callBaseMapStream); cleared by release (the name is
    // not the original's)
    DrResMdoSeamMemObj* m_memObj;
    // 0x160: by SeamHeader texture list, the DrResMdoSeamTexList holding it (the name is not the original's)
    DrResMdoSeamTexList** m_texLists;
    // 0x168: released and destroyed by release; createBaseZPrePassDisplayList passes it to
    // DrMdoCtl::partsZPrePassRender as the parts' alpha table (the name is not the original's)
    DrResMdoAlpTbl* m_instans;  // 0x168: passed as partsZPrePassRender's DrResMdoAlpTbl* (symbol); the name is not the original's
    unsigned char pad_170[0x8];
    short m_selectVertex;  // 0x178: the entry selectVertex last chose, -1 after beginRender (the name is not the original's)
    // 0x17A: update counts the frames the work stays out of read range (bit 5 of m_cacheFlags from 20 on) (the
    // name is not the original's)
    short m_outFrame;
    short m_fadeAlpha;  // 0x17C: update steps it by 20 between 0 and 255 (the name is not the original's)
    short m_vertexNum;     // 0x17E: entries of m_vertexList (the name is not the original's)
};
}  // namespace ml

#endif
