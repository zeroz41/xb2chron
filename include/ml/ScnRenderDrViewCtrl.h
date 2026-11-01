#ifndef ML_SCNRENDERDRVIEWCTRL_H
#define ML_SCNRENDERDRVIEWCTRL_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// a view of a scene renderer drawn into a texture (ScnRenderDrSysParmAcc::createAddRenderView hands it to DrMan;
// the field names are not the original's)
// event::OffscrManager::createScreen news one with width/height 256, colour 0, m_clear 1, scales 1.0 and the flags 0.
class ScnRenderDrViewCtrl {
public:
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_viewIndex;              // DrMan's render system index, less one
    float m_color[4];                      // 0xC
    bool m_clear;                          // 0x1C
    unsigned char pad_1D[0x3];
    grlib::CGLibTextureBuffer* m_texture;  // UIScreenObject::create makes its layer object from it
    bool m_flagA;                          // 0x28
    unsigned char pad_29[0x3];
    float m_scaleX;                        // 0x2C
    float m_scaleY;                        // 0x30
    bool m_flagB;                          // 0x34
    bool m_isReady;  // ui::UIResource::isLoading waits until every view of its list has it set (the name is not the original's)
    unsigned char pad_36[0x2];  // 0x38 bytes: ui::UIResource::load news it
};
}  // namespace ml

#endif
