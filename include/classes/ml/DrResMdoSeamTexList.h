#ifndef CLASSES_ML_DRRESMDOSEAMTEXLIST_H
#define CLASSES_ML_DRRESMDOSEAMTEXLIST_H

#include "mtl/MemManager.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoSeamParmRead;
// table 0x7100B7DA80
// The field and parameter names are not the original's.
class DrResMdoSeamTexList {
public:
    DrResMdoSeamTexList(int no);
    virtual ~DrResMdoSeamTexList();  // slot 0
    void release();
    // DrMdoCtlSeamRead::waitTexListStream builds the list once its stream is in
    void createTextureList(mtl::ALLOC_HANDLE handle);
    // true once the list has stayed unused long enough to be freed (DrMdoCtlSeam::updateTexutreSeam frees it)
    bool update(DrResMdoSeamParmRead* parmRead);
    static void setListCnt(int cnt);

    static int SEAMRES_TEXLIST_CNTMAX;

    // The list data update reads (type and field names are not the original's): the header gives the offset of
    // a table whose entries (from +0x4, 0x10 each) give each texture's image offset in the data and size.
    struct DataHead {
        int num;                // 0x0: the texture count (createTextureList)
        unsigned int tableOfs;  // 0x4
    };
    struct Entry {
        unsigned int size;      // 0x0
        unsigned int imageOfs;  // 0x4
        unsigned char pad_8[0x8];
    };
    struct Table {
        unsigned char pad_0[0x4];
        Entry entries[1];       // 0x4: m_num of them
    };

    DrResMdoSeamTexList* m_prev;           // 0x08: list links, zeroed by the constructor
    DrResMdoSeamTexList* m_next;           // 0x10
    // 0x18: the memory its stream reads into (DrMdoCtlSeamRead::callTexListStream); zeroed by the constructor and
    // the destructor (the name is not the original's)
    DrResMdoSeamMemObj* m_memObj;
    grlib::CGLibTextureBuffer* m_texture;  // 0x20: m_num buffers in m_buf
    // 0x28: the list data; update replaces it with the read memory (m_memObj->m_pData) once the stream is in;
    // zeroed by the constructor and release
    const unsigned char* m_data;
    void* m_buf;                           // 0x30: the allocation release deallocates
    short m_no;                            // 0x38: the constructor's argument
    unsigned char m_cnt;                   // 0x3A: zeroed by the constructor and waitTexListStream
    unsigned char m_readIn;                // 0x3B: update sets it once the data is in (as DrResMdoSeamTexture's)
    unsigned short m_dataIdx;              // 0x3C: its entry in the seam map's texture list table
    unsigned short m_num;                  // 0x3E
};
}  // namespace ml

#endif
