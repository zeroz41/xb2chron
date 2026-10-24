#ifndef CLASSES_GF_GFFIELDGRAVE_H
#define CLASSES_GF_GFFIELDGRAVE_H

#include "classes/gf/IFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; class GfSetupParam; class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B52318; the base at 0x8 is mm::mtl::PtrSingleton<gf::GfFieldGrave> (its destructor stores that
// table and clears the instance). Asks at a grave (a gmk::GmkGrave) through the common window whether to call its
// enemy out, and has the grave pop it when the answer is the first choice.
class GfFieldGrave : public ::gf::IFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldGrave> {
public:
    GfFieldGrave(const GfSetupParam& param);
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldGrave";
        return s_classId;
    }
    virtual void create(gf::GF_OBJ_HANDLE* handle);  // slot 1
    virtual void dispose();  // slot 2
    virtual bool isEnd() const { return m_isEnd; }  // slot 3
    virtual bool cancel() {  // slot 4
        dispose();
        return true;
    }
    virtual ~GfFieldGrave() {}  // slot 5
    void gevMapjump(GEV ev, const MapjumpCallbackInfo& info);
    void update(float dt);
    void seqWaitToSelect(float dt);

    GF_OBJ_HANDLE* m_handle;  // the grave's object, (GF_OBJ_HANDLE*)-1 for none
    bool m_isEnd;  // set once the common window has answered
    void (GfFieldGrave::*m_seq)(float dt);  // the step update runs, none when done
};
}  // namespace gf

#endif
