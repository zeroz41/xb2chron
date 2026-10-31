#ifndef ML_DRSHDUNIFORMBLOCKMAN_H
#define ML_DRSHDUNIFORMBLOCKMAN_H

namespace grlib {
class CGLibTriUniformBlock;
class CGLibTriUniformArray;
class CGLibDblUniformArray;
}

namespace ml {
struct MdsMpfMatTopHeader;

// Builds the model uniform blocks (its members take no object).
class DrShdUniformBlockMan {
public:
    static void createUniformBoneObj(grlib::CGLibTriUniformBlock* block, int num);
    static void createUniformMdlObj(grlib::CGLibTriUniformArray* array, int num);
    static void createUniformVolTexCalcObj(grlib::CGLibDblUniformArray* array, unsigned int num);
    static void createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray* array);
    static void createUniformMpfMaterialObj(grlib::CGLibDblUniformArray* array, const MdsMpfMatTopHeader* header);
};
}  // namespace ml

#endif
