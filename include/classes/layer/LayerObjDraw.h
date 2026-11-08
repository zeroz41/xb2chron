#ifndef CLASSES_LAYER_LAYEROBJDRAW_H
#define CLASSES_LAYER_LAYEROBJDRAW_H

#include "classes/layer/LayerActDef.h"

namespace grlib { class CGLibDblUniformBlock; }

namespace layer {
// one draw of a mesh: the vertex object's index and count, the texture list it reads (the field names are not the
// original's)
class LyrDrawData {
public:
    unsigned char pad_0[0x4];
    unsigned short m_vertexIdx;  // LayerShdManager::setupVertex's index
    unsigned short m_renderIdx;  // LayerVertexObj::render's index
    unsigned int m_texIdx;
    unsigned char m_texNum;
    unsigned char pad_D[0x2];
    // the window draws' sampler: 0 takes the object's m_texFilterType, 1..4 pick from a constant table (the name is
    // not the original's)
    unsigned char m_samplerSel;
};

// table none in 3.0.1: the draws LayerObjTopDef::finalRender calls through s_pCallDraw (its base place between
// LayerActDef and LayerObjMesh is inferred)
class LayerObjDraw : public ::layer::LayerActDef {
public:
    void draw_call_onm_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_onm_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_res_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_res_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_win_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_win_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_icon(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_number(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
    void draw_call_hdr(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);

    // LayerObjTopDef::finalRender calls one per draw
    static void (LayerObjDraw::*s_pCallDraw[9])(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data);
};
}  // namespace layer

#endif
