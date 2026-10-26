#ifndef GRLIB_CGLIBDECSHADER_H
#define GRLIB_CGLIBDECSHADER_H

#include "grlib/CGLibShader.h"

namespace grlib {

// the head of a declared shader's data (the names are not the original's: calcTblSize checks the magic and the
// version and returns the declaration count)
struct CGLibDecShaderData {
    unsigned int m_magic;    // 0x0: 0x54434C53
    unsigned int m_version;  // 0x4: 0x1002 or 0x1003 (calcTblSize compares it shifted down by one)
    int m_declNum;           // 0x8: the declarations
};

// a shader with declarations (0x68 bytes): its programs by the declarations' current values
class CGLibVtlMemPool;

class CGLibDecShader {
public:
    CGLibDecShader();
    ~CGLibDecShader();
    // the work bytes createMemPoolShader takes for the shader data (the parameter names are not the original's)
    static unsigned int calcWorkSize(const void* data, bool flag);
    // builds the shader in work from its data and the programs, its code in pool; returns the work bytes it took
    // (the parameter names are not the original's)
    unsigned int createMemPoolShader(void* work, const unsigned char* data, const unsigned char* programs,
                                     CGLibVtlMemPool* pool, bool flag);
    // the declarations' count, the size of a CGLibDecShdExtTbl table, of data (0 when it is no declared shader)
    static unsigned int calcTblSize(const void* data);
    unsigned int getDeclarationMax() const;
    unsigned int getDeclarationOfs(const char* name) const;
    void setDeclarationIdx(unsigned int ofs, unsigned int idx);
    // the program the declarations select (inline: the name is not the original's)
    CGLibShader& getCurrentShader() { return *(m_pShaders + m_current); }
    const CGLibShader& getCurrentShader() const { return *(m_pShaders + m_current); }

    const CGLibDecShaderData* m_pData;  // 0x0
    unsigned char pad_8[0x30];
    CGLibShader* m_pShaders;
    unsigned char pad_40[0x18];
    unsigned int m_current;  // the index of the program the declarations select
    unsigned char pad_5c[0xC];
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

    CGLibDecShader* m_pDecShader;  // 0x0
    unsigned int m_current;  // 0x8
    unsigned char* m_pTbl;  // 0x10: a value per declaration
};

}  // namespace grlib

#endif
