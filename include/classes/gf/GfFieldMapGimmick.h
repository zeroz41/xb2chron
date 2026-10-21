#ifndef CLASSES_GF_GFFIELDMAPGIMMICK_H
#define CLASSES_GF_GFFIELDMAPGIMMICK_H

#include "classes/gf/AFieldSeq.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfFieldMapGimmick no evidence names yet
class TUnk_B522F8 {
public:
    virtual ~TUnk_B522F8();
};
// table 0x7100B522A0; base at 0x28 unknown (TUnk_B522F8)
class GfFieldMapGimmick : public ::gf::AFieldSeq, public TUnk_B522F8 {
public:
    virtual void getIdStr() const;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void dispose();  // slot 2
    virtual bool isEnd() const;  // slot 3
    virtual ~GfFieldMapGimmick();  // slot 5
    virtual void onFsSucceeded();  // slot 7
    virtual void onFsFailed();  // slot 8
};
}  // namespace gf

#endif
