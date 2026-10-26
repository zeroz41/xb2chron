#ifndef GRLIB_CGLIBVTXFETCH_H
#define GRLIB_CGLIBVTXFETCH_H

#include "nvn/nvn.h"

namespace grlib {

// one vertex attribute of a fetch object (the field names are not the original's)
struct CGLibVtxAttr {
    unsigned int format;  // an NVNformat
    int location;
    int offset;  // in the vertex
    unsigned int stream;
};

// a vertex fetch object (0x10 bytes): how a vertex buffer's attributes are read
class CGLibVtxFetch {
public:
    CGLibVtxFetch();
    ~CGLibVtxFetch();
    // builds the fetch object for count attributes, in memory of its own
    void createFetchObj(CGLibVtxAttr* attributes, int count);
    // the same in the caller's memory; returns the bytes it takes
    int createMemFetchObj(void* memory, CGLibVtxAttr* attributes, int count);
    void release();

    // the NVN attribute states CGLibCtlShader::setShader binds and their count (the names are not the original's)
    NVNvertexAttribState* m_pAttribs;  // 0x0
    unsigned short m_attribNum;  // 0x8
    unsigned short m_isAlloc;  // 0xA: m_pAttribs is its own (createFetchObj's)
    unsigned char pad_C[0x4];
};

}  // namespace grlib

#endif
