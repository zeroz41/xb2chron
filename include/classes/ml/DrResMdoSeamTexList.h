#ifndef CLASSES_ML_DRRESMDOSEAMTEXLIST_H
#define CLASSES_ML_DRRESMDOSEAMTEXLIST_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7DA80
// The field and parameter names are not the original's.
class DrResMdoSeamTexList {
public:
    DrResMdoSeamTexList(int no);
    virtual ~DrResMdoSeamTexList();  // slot 0
    void release();
    static void setListCnt(int cnt);

    static int SEAMRES_TEXLIST_CNTMAX;

    DrResMdoSeamTexList* m_prev;           // 0x08: list links, zeroed by the constructor
    DrResMdoSeamTexList* m_next;           // 0x10
    void* pad_18;                          // 0x18: zeroed by the constructor
    grlib::CGLibTextureBuffer* m_texture;  // 0x20: m_num buffers in m_buf
    void* pad_28;                          // 0x28: zeroed by the constructor and release
    void* m_buf;                           // 0x30: the allocation release deallocates
    short m_no;                            // 0x38: the constructor's argument
    unsigned short pad_3A;                 // 0x3A: zeroed by the constructor
    unsigned char pad_3C;                  // 0x3C
    unsigned char pad_3D;                  // 0x3D
    unsigned short m_num;                  // 0x3E
};
}  // namespace ml

#endif
