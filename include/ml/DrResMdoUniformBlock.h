#ifndef ML_DRRESMDOUNIFORMBLOCK_H
#define ML_DRRESMDOUNIFORMBLOCK_H

namespace ml {
// The byte sizes of the model shaders' uniform blocks (callers pass them to CGLibDblUniformBlock::setup).
class DrResMdoUniformBlock {
public:
    static int getStaticUniformBlockSize();
    static int getMdlUniformBlockSize();
    static int getAVACharUniformBlockSize();
    static int getToonUniformBlockSize();
    static int getToon2UniformBlockSize();
    static int getLightUniformBlockSize();
    static int getVolTexCalcUniformBlockSize();
    static int getRimBloomCalcUniformBlockSize();
    static int getMpfMaterialUniformBlockSize();
};
}  // namespace ml

#endif
