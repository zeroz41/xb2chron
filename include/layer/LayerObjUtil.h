#ifndef LAYER_LAYEROBJUTIL_H
#define LAYER_LAYEROBJUTIL_H

namespace layer { class LayerResMatrix; }

namespace layer {
namespace LayerObjUtil {
// writes a position matrix (8 floats) to buff: z at [2]; raw leaves out the LayerManager's screen scale
void updatePosMatrixUniformBlock(float* buff, const LayerResMatrix* matrix, const LayerResMatrix& view, float z, bool raw);
}  // namespace LayerObjUtil
}  // namespace layer

#endif
