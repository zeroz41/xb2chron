#ifndef CLASSES_ML__WROOTST_WORKROOT_H
#define CLASSES_ML__WROOTST_WORKROOT_H

#include "classes/ml/WorkObj.h"

namespace ml { namespace _wrootst {
// table 0x7100B79AB0
class WorkRoot : public ::ml::WorkObj {
public:
    virtual ~WorkRoot();  // slot 0
    virtual bool wkStandbyLogout();  // slot 15
};
}}  // namespace ml::_wrootst

#endif
