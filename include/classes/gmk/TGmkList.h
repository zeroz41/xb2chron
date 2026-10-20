// not proven yet: does not compile: no member named 'BdatInfo' in 'gmk::TGmkFormPc<24, gmk::TGmkFormPcnpc<25> >'
#ifndef CLASSES_GMK_TGMKLIST_H
#define CLASSES_GMK_TGMKLIST_H

#include "classes/gmk/IGmkList.h"

namespace gmk {
// a template: 55 instances in the module
template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
class TGmkList : public ::gmk::IGmkList {
public:
    virtual ~TGmkList();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void getCreateInfo() const;  // slot 4
    virtual void getInstNum() const;  // slot 5
    virtual void getInst(unsigned int) const;  // slot 6
    virtual void getBindedBdatFp() const;  // slot 7
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual void updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
    virtual void disposeGmk();  // slot 17
    virtual void onResetUpdateGmkIndex();  // slot 18
};
}  // namespace gmk

#endif
