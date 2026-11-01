#ifndef ML_DRRESMDOVTXMESHOBJ_H
#define ML_DRRESMDOVTXMESHOBJ_H

#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "mm/Mat44.h"

namespace grlib {
class CGLibVtxVertex;
}

namespace ml {
class DrResMdoVertex;

// A mesh's extra vertex stream object (0x140 bytes, create builds it in the work and returns 0x140). Field names
// are not the original's; the layout comes from create/release/setActive/isRender/resourceInit.
class DrResMdoVtxMeshObj {
public:
    DrResMdoVtxMeshObj()
        : m_buf(nullptr), m_vtxNum(0), m_countMax(0), m_count0(0), m_count1(0), m_count2(0), m_count3(0) {
        m_val104 = 60.0f;
        m_val110 = 30;
        m_val108 = 1.2f;
        m_val10C = -0.05f;
        m_val114 = 0.18f;
        m_val118 = 0.12f;
        m_val11C = 0.09f;
        m_val120 = 0.998f;
        m_val124 = 0.3f;
        m_valE0 = 0.0f;
        m_valE4 = 1.0f;
        m_valF0 = 0.0f;
        m_valF4 = 1.0f;
        m_val100 = 1.0f;
        m_val12C = 1.0f;
        m_val130 = 1.0f;
        m_val98 = 0;
        m_valE8 = 0.0f;
        m_valF8 = 0.0f;
        m_val128 = 0.6f;
        m_flags = 0;
        m_active = false;
        m_countMax = 40000;
    }
    static unsigned int create(unsigned char* work, const unsigned char* data);
    static void release(DrResMdoVtxMeshObj*& obj);
    void resourceInit(DrResMdoVertex* vertex);
    bool isRender() const;
    // DrMdoCtlNom::callZSortNomAlphaRender
    void alpRender();
    // DrMdoCtlNom::callZSortNomRender, with whether the model has nodes
    void stmRender(bool);
    void setActive(bool active, unsigned int index);
    // the work bytes one object takes (a constant 0x140)
    static unsigned int calcWorkSize(const unsigned char* data);

    grlib::CGLibVtxVertex* m_vertex;           // 0x0: the vertex's EtcBlock::vertex
    grlib::CGLibOneUniformBlock* m_uniform;    // 0x8: the vertex's EtcBlock::uniform
    grlib::CGLibOneUniformBlock m_oneBlock;    // 0x10
    grlib::CGLibDblUniformBlock m_dblBlock;    // 0x38
    bool m_active;                             // 0x70: setActive(true) does nothing while set
    unsigned int m_flags;                      // 0x74: bit 0 render; 0x10000/0x40000 << double-buffer index
    void* m_buf;                               // 0x78: freed by release
    unsigned int m_vtxNum;                     // 0x80: m_vertex->m_num
    unsigned int m_countMax;                   // 0x84: setActive's count
    unsigned int m_count0;                     // 0x88
    unsigned int m_count1;                     // 0x8C: isRender when nonzero
    unsigned int m_count2;                     // 0x90
    unsigned int m_count3;                     // 0x94: isRender when nonzero
    unsigned int m_val98;                      // 0x98
    unsigned char pad_9C[0x4];
    mm::Mat44 m_mtx;                           // 0xA0
    float m_valE0;                             // 0xE0
    float m_valE4;                             // 0xE4
    float m_valE8;                             // 0xE8
    unsigned char pad_EC[0x4];
    float m_valF0;                             // 0xF0
    float m_valF4;                             // 0xF4
    float m_valF8;                             // 0xF8
    unsigned char pad_FC[0x4];
    float m_val100;                            // 0x100
    float m_val104;                            // 0x104
    float m_val108;                            // 0x108
    float m_val10C;                            // 0x10C
    int m_val110;                              // 0x110
    float m_val114;                            // 0x114
    float m_val118;                            // 0x118
    float m_val11C;                            // 0x11C
    float m_val120;                            // 0x120
    float m_val124;                            // 0x124
    float m_val128;                            // 0x128
    float m_val12C;                            // 0x12C
    float m_val130;                            // 0x130
    unsigned char pad_134[0xC];
};
}  // namespace ml

#endif
