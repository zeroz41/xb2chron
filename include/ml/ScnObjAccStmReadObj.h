#ifndef ML_SCNOBJACCSTMREADOBJ_H
#define ML_SCNOBJACCSTMREADOBJ_H

namespace ml { class DrStmReadCheck; }
namespace ml { class DrStmReadObj; }

namespace ml {
// a scene's access to a stream reader
class ScnObjAccStmReadObj {
public:
    // what readType stores in the reader (the enumerator names are not the original's)
    enum ReadType { READ_TYPE_0, READ_TYPE_1, READ_TYPE_2 };
    explicit ScnObjAccStmReadObj(DrStmReadObj* obj);
    void readType(ReadType type);
    // a reader of the named stream: DrCreator::createStmLoadObj's, which makes an ml::DrStmReadCheck
    static DrStmReadCheck* create(const char* name);
    DrStmReadObj* m_obj;  // the constructor's
};
}  // namespace ml

#endif
