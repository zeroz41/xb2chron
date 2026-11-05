#ifndef CLASSES_LAYER_LAYEROBJMESH_H
#define CLASSES_LAYER_LAYEROBJMESH_H

#include "classes/layer/LayerObjDraw.h"

namespace grlib { class CGLibDblUniformBlock; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }

namespace layer {
// what LayerObjMesh::updateMeshUniformBlock and its s_pCallUniform callbacks read and write (the field names are
// not the original's)
struct LayerArgMdlRenInf {
    // one mesh's entry of LayerObjTopDef's mesh table (0x38 bytes; the type and names are not the original's)
    struct Node {
        LayerResMatrix m_matrix;  // updatePosMatrixUniformBlock's first matrix
        LayerResColor m_color;  // updateMeshUniformBlock combines it with m_color
        unsigned char pad_34[0x2];
        unsigned char m_flags;  // bit 0: the mesh is hidden (updateMeshUniformBlock clears the draw bit)
        unsigned char pad_37[0x1];
    };

    unsigned int* m_dispFlags;  // bit 0 set when the mesh draws
    grlib::CGLibDblUniformBlock* m_uniformBlock;  // m_buff starts at its getBuff()
    const Node* m_node;
    const LayerResMatrix* m_viewMatrix;  // its second
    const LayerResColor* m_color;
    const unsigned char* m_meshInfo;  // [3]: the s_pCallUniform index
    float* m_buff;  // the uniform data being written; each callback steps it past what it writes
};

// table none in 3.0.1. 1.0.0's table (0x71011B7E38) is LayerActDef's (slot 10 LayerActDef::updatePartsAction) but
// for slot 1 (its own destructor), and its methods take a LayerObjTopDef's this unadjusted (updateParams).
// its base LayerObjDraw is inferred (no table names it): LayerObjDraw's functions sit between LayerActDef's and
// LayerObjMesh's in the unit and LayerObjTopDef::finalRender calls them with its this
class LayerObjMesh : public ::layer::LayerObjDraw {
public:
    void updateMeshUniformBlock(LayerArgMdlRenInf& arg);
    void call_uniform_def(LayerArgMdlRenInf& arg);
    void call_uniform_win(LayerArgMdlRenInf& arg);
    void call_uniform_win_ga_X(LayerArgMdlRenInf& arg);
    void call_uniform_win_ga_Y(LayerArgMdlRenInf& arg);
    void call_uniform_icon(LayerArgMdlRenInf& arg);
    void call_uniform_number(LayerArgMdlRenInf& arg);
    void call_uniform_uvscl(LayerArgMdlRenInf& arg);
    void call_uniform_noImage(LayerArgMdlRenInf& arg);
    void call_uniform_win_height(LayerArgMdlRenInf& arg);
    void call_uniform_win_sclheight(LayerArgMdlRenInf& arg);
    void call_uniform_win_sclga_X(LayerArgMdlRenInf& arg);
    void call_uniform_win_sclga_Y(LayerArgMdlRenInf& arg);
    void call_uniform_hdr(LayerArgMdlRenInf& arg);
    void setUniformWinGaX(LayerArgMdlRenInf& arg, bool scl);
    void setUniformWinGaY(LayerArgMdlRenInf& arg, bool scl);
    void setUniformWinHeight(LayerArgMdlRenInf& arg, bool scl);

    // one character of the number call_uniform_number writes into LayerActDef::NumberWork's instances (0x24 bytes,
    // LayerObjDraw::draw_call_number's stride; the type and names are not the original's)
    struct NumberInstance {
        float m_size[2];  // the character's icon size
        float m_pos[2];  // x: its offset in the number, moved left by the number's width
        float m_uv[4];
        unsigned int m_color;  // 0xFFFFFFFF
    };

    // updateMeshUniformBlock calls the one m_meshInfo[3] names
    static void (LayerObjMesh::*s_pCallUniform[13])(LayerArgMdlRenInf& arg);
};
}  // namespace layer

#endif
