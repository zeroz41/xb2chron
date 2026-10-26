#ifndef CLOUD_CLOUDMDLLISTMAN_H
#define CLOUD_CLOUDMDLLISTMAN_H

namespace cloud {

class CloudMdlParts;

// the list of a cloud model's parts (0x10: CloudObjMdl holds it at 0x20 before its uniforms at 0x30). The field
// names are not the original's.
class CloudMdlListMan {
public:
    CloudMdlListMan();
    ~CloudMdlListMan();
    void releaseAll();

    CloudMdlParts* m_pTop;  // 0x0
    unsigned char pad_8[0x8];
};

}  // namespace cloud

#endif
