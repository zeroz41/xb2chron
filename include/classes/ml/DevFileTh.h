#ifndef CLASSES_ML_DEVFILETH_H
#define CLASSES_ML_DEVFILETH_H

#include "classes/ml/DevBase.h"

namespace ml { class CERR_STRUCT; }
namespace ml { enum ERR_DECIDE : int; }

namespace ml {
// a base of ml::DevFileTh no evidence names yet
class TUnk_B76D68 {
public:
    virtual ~TUnk_B76D68();
};
// a base of ml::DevFileTh no evidence names yet
class TUnk_B76D88 {
public:
    virtual ~TUnk_B76D88();
    virtual void icbError(ml::CERR_STRUCT*) = 0;
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) = 0;
};
// table 0x7100B76CC0; base at 0x1B0 unknown (TUnk_B76D68), base at 0x1B8 unknown (TUnk_B76D88)
class DevFileTh : public ::ml::DevBase, public TUnk_B76D68, public TUnk_B76D88 {
public:
    virtual ~DevFileTh();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void icbError(ml::CERR_STRUCT*);  // slot 17
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE);  // slot 18
};
}  // namespace ml

#endif
