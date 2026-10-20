#ifndef CLASSES_GF_AFIELDSEQ_H
#define CLASSES_GF_AFIELDSEQ_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B52248
class AFieldSeq {
public:
    virtual void getIdStr() const = 0;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void dispose();  // slot 2
    virtual void isEnd() const;  // slot 3
    virtual void cancel();  // slot 4
    virtual ~AFieldSeq();  // slot 5
    virtual void onFsSucceeded() = 0;  // slot 7
    virtual void onFsFailed();  // slot 8
    unsigned char pad_8[0x20];  // fields: size from its derived classes
};
}  // namespace gf

#endif
