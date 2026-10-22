#ifndef ML_SCNRENDERDRSYSPARMACC_H
#define ML_SCNRENDERDRSYSPARMACC_H

namespace ml { class DrMan; }
namespace ml { class ScnRenderDrSys; }
namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// a texture a scene's models are drawn with: setModelTexture passes the texture and the flag to DrMan as a
// DR_MODEL_TEXTURE, in the slot it names (the field names are not the original's)
struct ScnRenderDrMdlTexture {
    grlib::CGLibTextureBuffer* m_texture;
    unsigned int m_slot;
    bool m_enable;  // UIScreenObject::createOnMemory sets it
};

// access to a scene renderer's parameters, through its DrMan
class ScnRenderDrSysParmAcc {
public:
    ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view);
    void setModelTexture(const ScnRenderDrMdlTexture& texture);
    void resetModelTexture(unsigned int slot);

    DrMan* m_drMan;                  // the renderer's (its 0x10)
    unsigned char pad_08[0x8];       // what the renderer holds for the view
    int m_view;                      // the constructor's
};
}  // namespace ml

#endif
