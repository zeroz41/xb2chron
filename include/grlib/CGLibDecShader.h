#ifndef GRLIB_CGLIBDECSHADER_H
#define GRLIB_CGLIBDECSHADER_H

#include "grlib/CGLibShader.h"
#include "grlib/CGLibVtlMemPool.h"
#include "mtl/AllocHandle.h"

namespace grlib {

// the head of a declared shader's data (the names are not the original's: calcTblSize checks the magic and the
// version and returns the declaration count)
struct CGLibDecShaderData {
    unsigned int m_magic;    // 0x0: 0x54434C53
    unsigned int m_version;  // 0x4: 0x1002 or 0x1003 (calcTblSize compares it shifted down by one)
    int m_declNum;           // 0x8: the declarations
    unsigned int m_declOfs;  // 0xC: the CGLibDecShaderDecl table, from the data's start
    int m_shaderNum;         // 0x10: the programs (calcWorkSize: one CGLibShader each)
    // setupMemPoolShader's tables (the names are not the original's): per program its reflection data (8-byte
    // entries, first word an offset from the data's start) and its code (8-byte entries: code offset from
    // m_codeOfs in the pool, control offset from m_controlOfs in the programs)
    unsigned int m_shaderInfoTblOfs;  // 0x14
    unsigned char pad_18[0x4];
    unsigned int m_codeTblOfs;  // 0x1C
    unsigned char pad_20[0x8];
    unsigned int m_controlOfs;  // 0x28
    unsigned char pad_2c[0x4];
    unsigned int m_codeOfs;  // 0x30
    unsigned int m_codeSize;  // 0x34: the code bytes at m_codeOfs (setupDataShader copies them; the name is not the
                              // original's)
};
struct CGLibDecShaderCode {  // a program's code (0x8 bytes; the names are not the original's)
    unsigned int m_codeOfs;  // 0x0
    unsigned int m_controlOfs;  // 0x4
};

// a declaration (0xC bytes; the names are not the original's): setDeclarationIdx clamps its value to m_valueNum - 1
// and moves the current program index by value * m_step; getDeclarationOfs finds it by name
struct CGLibDecShaderDecl {
    unsigned int m_valueNum;  // 0x0
    unsigned int m_step;      // 0x4
    unsigned int m_nameOfs;   // 0x8, from the data's start
};

// a shader with declarations (0x68 bytes): its programs by the declarations' current values

class CGLibDecShader {
public:
    CGLibDecShader();
    ~CGLibDecShader();
    void release();
    // the work bytes createMemPoolShader takes for the shader data (the parameter names are not the original's)
    static unsigned int calcWorkSize(const void* data, bool flag);
    // builds the shader in work from its data and the programs, its code in pool; returns the work bytes it took
    // (the parameter names are not the original's)
    unsigned int createMemPoolShader(void* work, const unsigned char* data, const unsigned char* programs,
                                     CGLibVtlMemPool* pool, bool flag);
    // builds the programs of data in work, their code in pool (the parameter names are not the original's)
    void setupMemPoolShader(const unsigned char* data, const unsigned char* programs, CGLibVtlMemPool* pool,
                            unsigned char* work, bool flag);
    // rebuilds the programs from new data with their code in pool (DrShdMdoDecShdObj::changeMemShader; the parameter
    // names are not the original's)
    void changeMemPoolSetMem(const unsigned char* data, const unsigned char* programs, CGLibVtlMemPool* pool);
    // builds the shader from a copy of data in memory of handle (CGLibUtilObj::setup; the parameter names are not
    // the original's)
    unsigned int createCopyShader(mtl::ALLOC_HANDLE handle, const void* data, bool flag);
    // builds the programs from m_pData (createCopyShader passes true; the parameter name is not the original's)
    void setupDataShader(bool flag);
    // the declarations' count, the size of a CGLibDecShdExtTbl table, of data (0 when it is no declared shader)
    static unsigned int calcTblSize(const void* data);
    unsigned int getDeclarationMax() const;
    unsigned int getDeclarationOfs(const char* name) const;
    void setDeclarationIdx(unsigned int ofs, unsigned int idx);
    // points the shader at data and its programs at work, all released, the declaration values after them when
    // flag (inline: createCopyShader and setupMemPoolShader inline it; the name is not the original's)
    void setupWork(const CGLibDecShaderData* data, void* work, bool flag) {
        CGLibShader* pShaders = static_cast<CGLibShader*>(work);
        m_pData = data;
        m_shaderNum = data->m_shaderNum;
        m_pShaders = pShaders;
        for (int i = 0; i < m_shaderNum; i++) {
            CGLibShader& shader = m_pShaders[i];
            shader.m_flags = 0;
            shader.m_pData = nullptr;
        }
        m_current = 0;
        if (flag) {
            m_pDeclValues = reinterpret_cast<unsigned char*>(pShaders + m_shaderNum);
            for (int i = 0; i < data->m_declNum; i++) {
                m_pDeclValues[i] = 0;
            }
        }
    }
    // the program the declarations select (inline: the name is not the original's)
    CGLibShader& getCurrentShader() { return *(m_pShaders + m_current); }
    const CGLibShader& getCurrentShader() const { return *(m_pShaders + m_current); }

    const CGLibDecShaderData* m_pData;  // 0x0
    CGLibVtlMemPool m_memPool;  // 0x8: the programs' code (release frees it; the name is not the original's)
    CGLibShader* m_pShaders;  // 0x38
    int m_shaderNum;  // 0x40: the programs in m_pShaders (the name is not the original's)
    unsigned char pad_44[0x4];
    // 0x48, 0x50: buffers release frees; createCopyShader allocates m_pCopyBuff for the programs and the declaration
    // values (the names are not the original's)
    void* m_pAllocBuff;  // 0x48
    void* m_pCopyBuff;  // 0x50
    unsigned int m_current;  // 0x58: the index of the program the declarations select
    unsigned char pad_5c[0x4];
    unsigned char* m_pDeclValues;  // 0x60: a value per declaration, after the programs (the name is not the original's)
};

// a shader table entry: a declared shader and the program it selects (the field names are not the original's; the
// size is not known)
class CGLibDecShdExtTbl {
public:
    CGLibDecShdExtTbl();
    // the table of declaration values (calcTblSize bytes)
    void setTbl(unsigned char* pTbl);
    // the shader the table selects programs of: its values all 0
    void setObj(CGLibDecShader* pDecShader);
    void setDeclarationIdx(unsigned int ofs, unsigned int idx);

    CGLibDecShader* m_pDecShader;  // 0x0
    unsigned int m_current;  // 0x8
    unsigned char* m_pTbl;  // 0x10: a value per declaration
};

}  // namespace grlib

#endif
