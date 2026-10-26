#ifndef CLOUD_CLOUDMDLPARTS_H
#define CLOUD_CLOUDMDLPARTS_H

namespace cloud {

// one part of a cloud model, kept in a list (CloudMdlListMan). Only what CloudObjMdl uses is declared; the field
// names are not the original's.
class CloudMdlParts {
public:
    // 0 or 1, read as a 32-bit value (CloudObjMdl::counterRender tests the whole register: not a bool)
    int isDisp() const;
    void bindVertex();
    void render();

    unsigned char pad_0[0xC0];
    CloudMdlParts* m_pNext;  // 0xC0, CloudObjMdl::counterRender walks the parts through it
};

}  // namespace cloud

#endif
