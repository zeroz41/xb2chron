#ifndef CLASSES_GF_IFIELDSEQ_H
#define CLASSES_GF_IFIELDSEQ_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B52470
class IFieldSeq {
public:
    virtual void getIdStr() const = 0;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*) = 0;  // slot 1
    virtual void dispose() = 0;  // slot 2
    virtual void isEnd() const = 0;  // slot 3
    virtual bool cancel() = 0;  // slot 4
};
}  // namespace gf

#endif
