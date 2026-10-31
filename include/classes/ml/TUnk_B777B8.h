#ifndef ML_TUNK_B777B8_H
#define ML_TUNK_B777B8_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {

namespace {
// the work Device::wkStandbyLogin enters under the device ("DeviceException"); a class of the file's own (its table,
// singleton and functions are internal: the symbols leave them unnamed). The name the string suggests is not used:
// no symbol names the class.
class TUnk_B777B8 : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<TUnk_B777B8> {
public:
    TUnk_B777B8(const char* name, WorkObj* parent) : WorkObj(name, parent, 0x40) {}
    virtual ~TUnk_B777B8() {}  // slot 0
    // logs out once it has no children
    virtual bool wkStandbyLogout() {  // slot 15
        if (m_child.size() == 0) {
            return WorkObj::wkStandbyLogout();
        }
        return false;
    }
};
}  // namespace

}  // namespace ml

#endif
