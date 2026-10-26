#ifndef CLOUD_CLOUDTEXTUREMAN_H
#define CLOUD_CLOUDTEXTUREMAN_H

namespace cloud {
// CloudMan's textures (0x20; CloudMan::beginSetup allocates it and calls createTexture)
class CloudTextureMan {
public:
    CloudTextureMan();
    ~CloudTextureMan();
    void createTexture();

    unsigned char pad_0[0x20];
};
}  // namespace cloud

#endif
