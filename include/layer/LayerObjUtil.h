#ifndef LAYER_LAYEROBJUTIL_H
#define LAYER_LAYEROBJUTIL_H

namespace layer { class LayerResMatrix; }
namespace layer { class LayerResDispInfo; }
namespace layer { class LayerResRenderInfo; }
namespace layer { class LayerRenderView; class LayerResViewPortInfo; class LayerViewPort; }
namespace grlib { class CGLibDblUniformBlock; }
namespace mm { class Mat44; }
#include "layer/LayerAccObjBase.h"

namespace layer {
// a layer uniform block's kind (its values are not known: LayerResSecTexture::resourceInit passes 10)
enum LayerUniType {};
// an object's base position data: calcMdlPos_* scale a model's size by its alignment (0 left/top; the names are not
// the original's)
class LayerBasePos {
public:
    float m_posX;  // calcPos_*_Up scale it by the screen width (the name is not the original's)
    float m_posY;  // calcPos_*_Up scale it by the screen height (the name is not the original's)
    float m_rot;  // calcLayerTransRotScale*Matrix rotate by it (radians; the name is not the original's)
    float m_sclX;  // calcScl_*_Up multiply the scaled size by it (the name is not the original's)
    float m_sclY;  // calcScl_*_Up multiply the scaled size by it (the name is not the original's)
    float m_alignX;
    float m_alignY;
};

// a layout part's position data: calcPosData_Pixel_Up reads its pixel rectangle, calcPosData_Correction_Up its
// position and size (the field names are not the original's)
class LyrLayoutPosData {
public:
    // its rectangle in the correction coordinate (position and size) and in pixels (LayerAccLayoutBinary's
    // setLayoutPosData; the names are not the original's)
    void getCorrectionRect(float& x, float& y, float& width, float& height) const {
        x = m_posX;
        y = m_posY;
        width = m_width;
        height = m_height;
    }
    void getPixelRect(float& x, float& y, float& width, float& height) const {
        x = m_left;
        y = m_top;
        width = m_right - m_left;
        height = m_bottom - m_top;
    }

    // LayerObjTopLayout::workLayoutCreate creates an object for each record with FLAG_OBJ (the names are not the
    // original's)
    enum { FLAG_OBJ = 0x2 };
    unsigned char m_flags;
    unsigned char pad_1[0x3];
    unsigned int m_nameOfs;  // 0x4: its name's offset from the layout binary's start (LayerAccLayoutBinary::getPosIdx)
    unsigned char pad_8[0x4];
    unsigned int m_objIdx;  // 0xC: the LyrLayoutBinObj record of its object (the name is not the original's)
    unsigned char pad_10[0x8];
    float m_width;
    float m_height;
    float m_posX;
    float m_posY;
    unsigned char pad_28[0x4];
    short m_left;
    short m_top;
    short m_right;
    short m_bottom;
};

namespace LayerObjUtil {
// the size of the kind's uniform block, aligned for its offset (LayerResSecTexture::resourceInit sets one up so)
int getUniformBlockSizeAlOff(LayerUniType type);
// getUniformBlockSizeAlOff's sizes, one per LayerUniType
extern const unsigned short UNIFORM_BLOCK_SIZE[12];
// a model's offset (out) from its size and the base position's alignment; Down and Center also move pos up by the
// size (Center by half of it)
void calcMdlPos_Center_Up(float* pos, float* out, const float* size, const LayerBasePos& base);
void calcMdlPos_Center_Down(float* pos, float* out, const float* size, const LayerBasePos& base);
void calcMdlPos_Center_Center(float* pos, float* out, const float* size, const LayerBasePos& base);
// pos = the base position scaled by the LayerManager's screen calc size
void calcPos_Pixel_Up(float* pos, const LayerBasePos& base);
void calcPos_Correction_Up(float* pos, const LayerBasePos& base);
// out = the render info's size scaled by the LayerManager's screen calc scale and the base's scale (Swf: the larger
// side for both axes)
void calcScl_Pixel_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcScl_Correction_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcSwfScl_Pixel_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcSwfScl_Correction_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info);
// pos (x, y, width, height) from a layout part's data, moved by its center type
void calcPosData_Pixel_Up(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY);
void calcPosData_Correction_Up(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY);
// calls the s_CallDataPos entry of the LayerManager's coordinate
void getLayoutInfo(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY);
// the per-coordinate (pixel, correction) variants, indexed by LayerManager::m_coordinate
extern void (*s_CallScl[2])(float*, const LayerBasePos&, const LayerResRenderInfo&);
extern void (*s_CallPos[2])(float*, const LayerBasePos&);
extern void (*s_CallMdl[3])(float*, float*, const float*, const LayerBasePos&);
extern void (*s_CallSwfScl[2])(float*, const LayerBasePos&, const LayerResRenderInfo&);
extern void (*s_CallDataPos[2])(float*, const LyrLayoutPosData*, LayerCenterType, float, float);
// mtx = the base's rotation, scale and position (moved by the render info's alignment and center type); Laout
// scales by the base's scale only, SWF uses the s_CallSwfScl scale
void calcLayerTransRotScaleFontMatrix(LayerResMatrix& mtx, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcLayerTransRotScaleSWFMatrix(LayerResMatrix& mtx, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcLayerTransRotScaleMatrix(LayerResMatrix& mtx, const LayerBasePos& base, const LayerResRenderInfo& info);
void calcLayerTransRotScaleLaoutMatrix(LayerResMatrix& mtx, const LayerBasePos& base, const LayerResRenderInfo& info);
// writes a position matrix (8 floats) to buff: z at [2]; raw leaves out the LayerManager's screen scale
// the screen bounds of an object drawn with the matrix and render info
// the depth of the matrix's position: z and the sort distance LayerObj::updateDefSpace keeps (m_depth, m_posZ)
void calcMatrixToZBuffPos(float& depth, float& z, const mm::Mat44& mtx);
// uniform (created on first use) gets the world matrix mtx and the priority-derived offset
void createWorldMatrixUniform(grlib::CGLibDblUniformBlock*& uniform, const mm::Mat44& mtx, float offset);
void calcDispInfo(LayerResDispInfo& disp, const LayerResMatrix& matrix, const LayerResRenderInfo& info);
// the screen bounds of a layout drawn with the matrix and render info
void calcLayoutDispInfo(LayerResDispInfo& disp, const LayerResMatrix& matrix, const LayerResRenderInfo& info);
void updatePosMatrixUniformBlock(float* buff, const LayerResMatrix* matrix, const LayerResMatrix& view, float z, bool raw);
// the same, keeping the combined matrix (matrix then view) in out
void updatePosMatrixUniformBlock(float* buff, LayerResMatrix& out, const LayerResMatrix* matrix, const LayerResMatrix& view,
                                 float z, bool raw);
// view = parent's view drawn into info's viewport: vp moved by the matrix's translation; uniform (created on first
// use) gets the viewport's scale and offset
void calcLayerRenderView(LayerRenderView& view, LayerResViewPortInfo& info, grlib::CGLibDblUniformBlock*& uniform,
                         const LayerViewPort& vp, const LayerRenderView* parent, const LayerResMatrix* matrix);
}  // namespace LayerObjUtil
}  // namespace layer

#endif
