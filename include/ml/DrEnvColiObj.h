#ifndef ML_DRENVCOLIOBJ_H
#define ML_DRENVCOLIOBJ_H
namespace ml {
// a view's environment collision object (DrCreator::createEnvColi makes it; ScnObjEnvColiDr keeps one)
class DrEnvColiObj {
public:
    void release();
};
}  // namespace ml
#endif
