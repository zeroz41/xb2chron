#ifndef LAYER_LAYEROBJUTIL_H
#define LAYER_LAYEROBJUTIL_H

namespace layer { class LayerResMatrix; }
namespace layer { class LayerResDispInfo; }
namespace layer { class LayerResRenderInfo; }

namespace layer {
// a layer uniform block's kind (its values are not known: LayerResSecTexture::resourceInit passes 10)
enum LayerUniType {};
// an object's base position data: calcMdlPos_* scale a model's size by its alignment (0 left/top; the names are not
// the original's)
class LayerBasePos {
public:
    float m_posX;  // calcPos_*_Up scale it by the screen width (the name is not the original's)
    float m_posY;  // calcPos_*_Up scale it by the screen height (the name is not the original's)
    unsigned char pad_8[0xC];
    float m_alignX;
    float m_alignY;
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
// writes a position matrix (8 floats) to buff: z at [2]; raw leaves out the LayerManager's screen scale
// the screen bounds of an object drawn with the matrix and render info
void calcDispInfo(LayerResDispInfo& disp, const LayerResMatrix& matrix, const LayerResRenderInfo& info);
void updatePosMatrixUniformBlock(float* buff, const LayerResMatrix* matrix, const LayerResMatrix& view, float z, bool raw);
}  // namespace LayerObjUtil
}  // namespace layer

#endif
