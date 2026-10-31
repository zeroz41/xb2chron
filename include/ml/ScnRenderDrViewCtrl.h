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
    unsigned char pad_28[0xD];
    bool m_isReady;  // ui::UIResource::isLoading waits until every view of its list has it set (the name is not the original's)
    unsigned char pad_36[0x2];  // 0x38 bytes: ui::UIResource::load news it
};
}  // namespace ml

#endif
