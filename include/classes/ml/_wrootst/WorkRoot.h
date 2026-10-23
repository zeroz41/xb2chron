#ifndef CLASSES_ML__WROOTST_WORKROOT_H
#define CLASSES_ML__WROOTST_WORKROOT_H

#include "classes/ml/WorkObj.h"

namespace ml { namespace _wrootst {
// table 0x7100B79AB0
class WorkRoot : public ::ml::WorkObj {
public:
    WorkRoot(const char* name, WorkObj* parent);
    virtual ~WorkRoot();  // slot 0
    virtual bool wkStandbyLogout();  // slot 15
    // the works WorkRootState::requestParent queued moved under their new parents
    void procParent();

    reslist<WorkObj*> m_requestWork;    // 0x1A8 (the name is not the original's)
    reslist<WorkObj*> m_requestParent;  // 0x1E8 (the name is not the original's)
};
}}  // namespace ml::_wrootst

#endif
