#ifndef CLOUD_CLOUDVERTEXMAN_H
#define CLOUD_CLOUDVERTEXMAN_H

namespace grlib { class CGLibVtxVertex; }
namespace grlib { class CGLibVtxIndex; }

namespace cloud {
// which of CloudVertexMan's buffers; the enumerators are not known
enum CloudVertexType {};

// CloudMan's vertex buffers (0x90; CloudMan::beginSetup allocates it)
class CloudVertexMan {
public:
    CloudVertexMan();
    void createVertexList();
    ~CloudVertexMan();
    void releaseVertexList();
    void createSphere();
    void createCapsule();
    void createHalfSphere();
    void bindVertexList(CloudVertexType type);
    void renderIndexList(CloudVertexType type);

    // the names are not the original's
    grlib::CGLibVtxVertex* m_pVertex[9];  // 0x0, by CloudVertexType
    grlib::CGLibVtxIndex* m_pIndex[9];    // 0x48, by CloudVertexType
};
}  // namespace cloud

#endif
