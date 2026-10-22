#ifndef ML_SCNOBJACCSTMREADOBJ_H
#define ML_SCNOBJACCSTMREADOBJ_H

namespace ml { class DrStmReadCheck; }

namespace ml {
// a scene's access to a stream reader
class ScnObjAccStmReadObj {
public:
    // a reader of the named stream: DrCreator::createStmLoadObj's, which makes an ml::DrStmReadCheck
    static DrStmReadCheck* create(const char* name);
};
}  // namespace ml

#endif
