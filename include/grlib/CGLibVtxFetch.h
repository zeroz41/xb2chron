#ifndef GRLIB_CGLIBVTXFETCH_H
#define GRLIB_CGLIBVTXFETCH_H

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
    void createMemFetchObj(void* memory, CGLibVtxAttr* attributes, int count);
    void release();

    unsigned char pad_0[0x10];
};

}  // namespace grlib

#endif
