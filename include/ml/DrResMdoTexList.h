#ifndef ML_DRRESMDOTEXLIST_H
#define ML_DRRESMDOTEXLIST_H

#include "grlib/CGLibVtlMemPool.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrCalcStmListObj;

// A texture resource's header: the texture count, then the offset of its MdsTexInfo entries (the field names are not
// the original's).
struct MdsTexHeader {
    int m_num;               // 0x0
    unsigned int m_infoOfs;  // 0x4: from the header
};
// One texture of an MdsTexHeader (the struct's and fields' names are not the original's).
struct MdsTexInfo {
    unsigned int pad_0;
    unsigned int m_size;     // 0x4: the image's bytes
    unsigned int m_ofs;      // 0x8: the image, from the texture memory's start
    unsigned int m_nameOfs;  // 0xC: the name, from the header
};

// A model texture list resource; DrMdoTextureMan keeps them in a list. Field names are not the original's.
class DrResMdoTexList {
public:
    explicit DrResMdoTexList(const unsigned char* data);
    // stream textures matched to the stream's by name (createStmTexInfoList with true)
    DrResMdoTexList(const unsigned char* data, DrCalcStmListObj* stm, const unsigned char* mem, const MdsTexHeader* stmTex);
    // stream textures given by index (createStmTexInfoList with false)
    DrResMdoTexList(const unsigned char* data, DrCalcStmListObj* stm, const unsigned char* mem, const unsigned short* stmIdx);
    ~DrResMdoTexList();
    void createTexInfoList();
    void createTexList(const unsigned char* data, const unsigned char* mem);
    void createStmTexInfoList(DrCalcStmListObj* stm, const unsigned char* stmTex, bool byName);
    void update();
    void texStmUpdate();
    void callStmRead(int mode);
    grlib::CGLibTextureBuffer* getTexObj(unsigned int idx);
    grlib::CGLibTextureBuffer* getStmTexObj(unsigned int idx);
    void changeMemTexList(const unsigned char* mem);
    // the texture count: the first word of the texture data
    static unsigned int calcTextureMax(const unsigned char* data);

    // inline in the destructor, createTexInfoList and createStmTexInfoList: the buffers destroyed and freed (the name
    // is not the original's)
    void releaseTexInfo();
    const MdsTexHeader* getHeader() const { return reinterpret_cast<const MdsTexHeader*>(m_data); }
    const MdsTexInfo* getInfo() const {
        return reinterpret_cast<const MdsTexInfo*>(m_data + getHeader()->m_infoOfs);
    }

    enum {
        FLAG_CREATED = 0x1,
        FLAG_MEM = 0x20,
        FLAG_STM = 0x8000,
        FLAG_STM_READ = 0x10000,
        FLAG_STM_READ_ALL = 0x20000,
    };

    DrResMdoTexList* m_pPrev;          // 0x0: DrMdoTextureMan's list link
    DrResMdoTexList* m_pNext;          // 0x8: DrMdoTextureMan's list link
    const unsigned char* m_res;        // 0x10: the constructor's data
    // 0x18: 1 from the constructors; DrMdoMat::setupMpfResource adds a reference (the name is not the
    // original's)
    int m_refCount;
    unsigned char pad_1C[0x4];
    grlib::CGLibTextureBuffer* m_texBuf;  // 0x20: m_texNum buffers in m_texAlloc
    grlib::CGLibVtlMemPool m_pool;     // 0x28: over the texture memory
    DrCalcStmListObj* m_stmList;       // 0x58
    void* m_texAlloc;                  // 0x60
    int m_texNum;                      // 0x68
    unsigned int m_flags;              // 0x6C: FLAG_*
    int m_stmState;                    // 0x70: texStmUpdate: 1, 2 once the stream's textures are in
    unsigned char pad_74[0x4];
    unsigned short* m_stmIdx;          // 0x78: per texture, the stream's texture + 1 or 0
    const unsigned char* m_data;       // 0x80: an MdsTexHeader
    const unsigned char* m_mem;        // 0x88: the texture memory
    void* pad_90;
    void* pad_98;
};
}  // namespace ml

#endif
