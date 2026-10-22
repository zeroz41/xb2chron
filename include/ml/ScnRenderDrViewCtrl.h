#ifndef ML_SCNRENDERDRVIEWCTRL_H
#define ML_SCNRENDERDRVIEWCTRL_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// a view of a scene renderer drawn into a texture (ScnRenderDrSysParmAcc::createAddRenderView hands it to DrMan;
// the field names are not the original's)
class ScnRenderDrViewCtrl {
public:
    unsigned char pad_00[0x8];
    unsigned int m_viewIndex;              // DrMan's render system index, less one
    unsigned char pad_0C[0x14];
    grlib::CGLibTextureBuffer* m_texture;  // UIScreenObject::create makes its layer object from it
};
}  // namespace ml

#endif
