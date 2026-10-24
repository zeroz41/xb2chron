#ifndef CLASSES_GF_IFIELDSEQ_H
#define CLASSES_GF_IFIELDSEQ_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B52470; a field sequence GfPlayComFieldSeq runs on an object (GfSequentialPlay::addMapGimmick,
// addGrave, addJump and addWarp pass their singletons)
class IFieldSeq {
public:
    // the class's name: each derived class answers its getIdStr's s_classId
    virtual const char* getIdStr() const = 0;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*) = 0;  // slot 1
    virtual void dispose() = 0;  // slot 2
    virtual bool isEnd() const = 0;  // slot 3
    virtual bool cancel() = 0;  // slot 4
};
}  // namespace gf

#endif
