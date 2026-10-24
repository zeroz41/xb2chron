#ifndef CLASSES_GF_AFIELDSEQ_H
#define CLASSES_GF_AFIELDSEQ_H

#include "classes/gf/IFieldSeq.h"
namespace gf { class GF_OBJ_HANDLE; class GfSetupParam; class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B52248; slots 0-4 are IFieldSeq's (GfSequentialPlay::addMapGimmick, addJump and addWarp pass their
// singletons to GfPlayComFieldSeq::create(IFieldSeq*) unadjusted). A sequence of steps (m_seq) run on one object:
// create starts with seqCheckFs (the row's field skill check, FSID), then seqWaitUIEnd waits for the field skill
// menu and calls onFsSucceeded or onFsFailed.
class AFieldSeq : public IFieldSeq {
public:
    AFieldSeq(const GfSetupParam& param);
    virtual const char* getIdStr() const = 0;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE* handle);  // slot 1
    virtual void dispose();  // slot 2
    virtual bool isEnd() const;  // slot 3
    virtual bool cancel();  // slot 4
    virtual ~AFieldSeq() {  // slot 5
        m_isEnd = false;
        m_isFsSucceeded = false;
        m_seq = nullptr;
        m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    virtual void onFsSucceeded() = 0;  // slot 7
    virtual void onFsFailed();  // slot 8
    void gevMapjump(GEV ev, const MapjumpCallbackInfo& info);
    void update(float dt);
    void seqCheckFs(float dt);
    void seqWaitUIEnd(float dt);

    GF_OBJ_HANDLE* m_handle;  // the object create was given, (GF_OBJ_HANDLE*)-1 for none
    void (AFieldSeq::*m_seq)(float dt);  // the step update runs, none when done
    bool m_isEnd;  // isEnd's answer: set once seqWaitUIEnd has called onFsSucceeded or onFsFailed
    bool m_isFsSucceeded;  // the field skill check's result (no FSID passes)
};
}  // namespace gf

#endif
