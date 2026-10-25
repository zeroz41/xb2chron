#ifndef GRLIB_CGLIBPIPELINE_H
#define GRLIB_CGLIBPIPELINE_H

#include "nvn/nvn.h"

namespace grlib { class CGLibShader; }

namespace grlib {
// the drawing pipeline: the command buffer drawing records into and the NVN state objects the CGLibState /
// CGLibColorCtl / CGLibPolygon / CGLibDepthCtl / CGLibCtlVertex / CGLibCtlShader setters bind into it (the system
// context's, at 0x1070). The field names are not the original's.
class CGLibPipeline {
public:
    void setDefaults();
    // binds the vertex streams the setters changed since the last draw
    void updateVertex();

    NVNcommandBuffer* m_pCmdBuf;  // 0x0
    NVNblendState m_blendState;  // 0x8: setMrtBlendControl
    NVNchannelMaskState m_channelMask;  // 0x10: setColorChannelMask
    NVNchannelMaskState m_channelMaskOn;  // 0x14: setColorBufferOn
    NVNchannelMaskState m_channelMaskOff;  // 0x18: setColorBufferOff
    NVNcolorState m_mrtColorState;  // 0x1C: CGLibColorCtl::setMrtBlend
    NVNcolorState m_blendOffColorState;  // 0x20: CGLibColorCtl::setBlendOffControl
    NVNcolorState m_blendOnColorState;  // 0x24: CGLibColorCtl::setBlendControl
    NVNdepthStencilState m_depthStencilState;  // 0x28
    NVNpolygonState m_polygonCullOff;  // 0x30: CGLibPolygon::setCullingOff
    NVNpolygonState m_polygonCullFront;  // 0x34
    NVNpolygonState m_polygonCullBack;  // 0x38
    NVNpolygonState m_polygonDispOff;  // 0x3C: setCullingDispOff
    unsigned char pad_40[0x10];
    NVNvertexStreamState m_vertexStreams[8];  // 0x50
    int m_lastVertexStream;  // 0x90: the highest stream the setters changed
    bool m_vertexStreamDirty;  // 0x94: the streams need binding before the next draw
    CGLibShader* m_pShader;  // 0x98: the shader setShader / setComputeShader bound last
};
}  // namespace grlib

#endif
