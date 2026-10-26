#ifndef CLOUD_CLOUDVERTEXMAN_H
#define CLOUD_CLOUDVERTEXMAN_H

namespace cloud {
// CloudMan's vertex buffers (0x90; CloudMan::beginSetup allocates it)
class CloudVertexMan {
public:
    CloudVertexMan();
    ~CloudVertexMan();

    unsigned char pad_0[0x90];
};
}  // namespace cloud

#endif
