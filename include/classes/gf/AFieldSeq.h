#ifndef CLASSES_GF_AFIELDSEQ_H
#define CLASSES_GF_AFIELDSEQ_H

#include "classes/gf/IFieldSeq.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B52248; slots 0-4 are IFieldSeq's (GfSequentialPlay::addMapGimmick, addJump and addWarp pass their
// singletons to GfPlayComFieldSeq::create(IFieldSeq*) unadjusted)
class AFieldSeq : public IFieldSeq {
public:
    virtual void getIdStr() const = 0;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void dispose();  // slot 2
    virtual bool isEnd() const;  // slot 3
    virtual bool cancel();  // slot 4
    virtual ~AFieldSeq();  // slot 5
    virtual void onFsSucceeded() = 0;  // slot 7
    virtual void onFsFailed();  // slot 8
    unsigned char pad_8[0x20];  // fields: size from its derived classes
};
}  // namespace gf

#endif
