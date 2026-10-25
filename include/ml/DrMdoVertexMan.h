#ifndef ML_DRMDOVERTEXMAN_H
#define ML_DRMDOVERTEXMAN_H

namespace grlib { class CGLibVtxInstans; }

namespace ml {
// DrMdlMan's vertex manager (its constructor makes it first). Only what DrGpuCheckRender reads is recovered.
class DrMdoVertexMan {
public:
    DrMdoVertexMan();

    unsigned char pad_0[0x10];
    grlib::CGLibVtxInstans* m_instans;  // 0x10, the instance ring DrGpuCheckRender takes its part of (the name is not the original's)
};
}  // namespace ml

#endif
