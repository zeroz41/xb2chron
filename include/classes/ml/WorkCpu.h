#ifndef CLASSES_ML_WORKCPU_H
#define CLASSES_ML_WORKCPU_H

#include "classes/ml/WorkObj.h"
namespace ml {
class IWorkInfomation; class IWorkBackground; class IThreadValue; }

namespace ml {
// a base of ml::WorkCpu no evidence names yet
class TUnk_B78EA0 {
public:
    virtual ~TUnk_B78EA0();
};
// table 0x7100B78E08; base at 0x1A8 unknown (TUnk_B78EA0)
class WorkCpu : public ::ml::WorkObj, public TUnk_B78EA0 {
public:
    virtual ~WorkCpu();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // its object made and every CPU thread logged in
    static bool isInitialized();
    // a listener told of the HOME menu no more (fw::MovieManager's destructor)
    static void removeBackgroundListener(IWorkBackground* listener);
    // a listener of system information (operation and performance mode) no more (ml::DevPerfNx's destructor)
    static void removeSystemInfoListener(IWorkInfomation* listener);
    // a value swapped every frame no more (threadval's destructor)
    static void removeSwap(IThreadValue* value);
};
}  // namespace ml

#endif
