#ifndef GRLIB_CGLIBVTXFETCH_H
#define GRLIB_CGLIBVTXFETCH_H

#include "nvn/nvn.h"

namespace grlib {

// one vertex attribute of a fetch object (the field names are not the original's)
struct CGLibVtxAttr {
    unsigned int format;
    unsigned int location;
    unsigned int offset;  // in the vertex
    unsigned int stream;
};

// a vertex fetch object (0x10 bytes): how a vertex buffer's attributes are read
class CGLibVtxFetch {
public:
    CGLibVtxFetch();
    ~CGLibVtxFetch();
    // the fetch object in memory, for count attributes
    // builds the fetch object for count attributes
    void createFetchObj(CGLibVtxAttr* attributes, int count);
    void createMemFetchObj(void* memory, CGLibVtxAttr* attributes, int count);
    void release();

    // the NVN attribute states CGLibCtlShader::setShader binds and their count (the names are not the original's)
    const NVNvertexAttribState* m_pAttribs;  // 0x0
    unsigned short m_attribNum;  // 0x8
    unsigned char pad_A[0x6];
};

}  // namespace grlib

#endif
