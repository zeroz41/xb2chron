#ifndef ML_DRSHDUNIFORMBLOCKMAN_H
#define ML_DRSHDUNIFORMBLOCKMAN_H

namespace grlib { class CGLibTriUniformBlock; }

namespace ml {
// Builds the model uniform blocks (its members take no object).
class DrShdUniformBlockMan {
public:
    static void createUniformBoneObj(grlib::CGLibTriUniformBlock* block, int num);
};
}  // namespace ml

#endif
