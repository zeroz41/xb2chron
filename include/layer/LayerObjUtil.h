#ifndef LAYER_LAYEROBJUTIL_H
#define LAYER_LAYEROBJUTIL_H

namespace layer { class LayerResMatrix; }

namespace layer {
// a layer uniform block's kind (its values are not known: LayerResSecTexture::resourceInit passes 10)
enum LayerUniType {};

namespace LayerObjUtil {
// the size of the kind's uniform block, aligned for its offset (LayerResSecTexture::resourceInit sets one up so)
int getUniformBlockSizeAlOff(LayerUniType type);
// writes a position matrix (8 floats) to buff: z at [2]; raw leaves out the LayerManager's screen scale
void updatePosMatrixUniformBlock(float* buff, const LayerResMatrix* matrix, const LayerResMatrix& view, float z, bool raw);
}  // namespace LayerObjUtil
}  // namespace layer

#endif
