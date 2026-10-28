#ifndef CLASSES_ML_DRRESMDOSEAMWRKBASE_H
#define CLASSES_ML_DRRESMDOSEAMWRKBASE_H

namespace ml {
class DrMdoCtlSeamBaseMap;
class DrResMdoSeamMemObj;
class DrResMdoVertex;
struct MdoWrkMatRes;

// table 0x7100B7DB00
class DrResMdoSeamWrkBase {
public:
    virtual ~DrResMdoSeamWrkBase();  // slot 0
    void release();
    void beginRender();
    void endRender();
    void selectVertex(int index);
    void setVertexCache(unsigned int cacheIdx, DrResMdoSeamMemObj* memObj, int param, DrMdoCtlSeamBaseMap* ctl);

    // one entry of the vertex list release walks (the names are not the original's)
    struct VertexEntry {
        void* pad_0;  // cleared by release
        DrResMdoVertex* vertex;
        unsigned char pad_10[0x8];
    };

    unsigned char pad_8[0x60];
    MdoWrkMatRes* m_matRes;  // 0x68: setupWork's matRes (the name is not the original's)
    unsigned char pad_70[0x8];
    VertexEntry* m_vertexList;  // 0x78 (the name is not the original's)
    unsigned char pad_80[0x20];
    // 0xA0: DrMdoCtlSeamRead::waitBaseVertexStream sets bit 4 when the vertex stream ends without its data
    unsigned int m_cacheFlags;
    unsigned char pad_A4[0xD4];
    short m_selectVertex;  // 0x178: the entry selectVertex last chose, -1 after beginRender (the name is not the original's)
    unsigned char pad_17A[0x6];
};
}  // namespace ml

#endif
