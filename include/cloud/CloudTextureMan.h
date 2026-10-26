#ifndef CLOUD_CLOUDTEXTUREMAN_H
#define CLOUD_CLOUDTEXTUREMAN_H

namespace grlib { class CGLibTextureBuffer; }

namespace cloud {
// CloudMan's textures (0x20; CloudMan::beginSetup allocates it and calls createTexture)
class CloudTextureMan {
public:
    CloudTextureMan();
    ~CloudTextureMan();
    void releaseTexture();
    void createTexture();

    // the name is not the original's: CloudDataMan's textures 1..4 (volume, volume2, pnoise, tg_smoke_01_n)
    grlib::CGLibTextureBuffer* m_pTextures[4];
};
}  // namespace cloud

#endif
