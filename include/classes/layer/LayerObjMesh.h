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
    unsigned int* m_dispFlags;  // bit 0 set when the mesh draws
    grlib::CGLibDblUniformBlock* m_uniformBlock;  // m_buff starts at its getBuff()
    const LayerResMatrix* m_matrix;  // updatePosMatrixUniformBlock's first matrix
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

    // updateMeshUniformBlock calls the one m_meshInfo[3] names
    static void (LayerObjMesh::*s_pCallUniform[13])(LayerArgMdlRenInf& arg);
};
}  // namespace layer

#endif
