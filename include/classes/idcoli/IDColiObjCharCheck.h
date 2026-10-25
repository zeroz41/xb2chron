#ifndef CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H

#include "classes/idcoli/IDColiObjChar.h"

namespace idcoli { class IDColiTreeTop; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

namespace idcoli {
// table 0x7100B7F138
class IDColiObjCharCheck : public ::idcoli::IDColiObjChar {
public:
    IDColiObjCharCheck(IDColiTreeTop* tree);
    bool testResultLine(IDColiResult& result, const IDColiInput& input);
    bool testResultRay(IDColiResult& result, const IDColiInput& input);
    bool testResultSphere(IDColiResult& result, const IDColiInput& input);
    bool testResultCapsule(IDColiResult& result, const IDColiInput& input);
    bool testCheckLine(IDColiResult& result, const IDColiInput& input);
    bool testCheckRay(IDColiResult& result, const IDColiInput& input);
    bool testCheckSphere(IDColiResult& result, const IDColiInput& input);
    bool testCheckCapsule(IDColiResult& result, const IDColiInput& input);
    bool testCheckBox(IDColiResult& result, const IDColiInput& input);
    virtual ~IDColiObjCharCheck() {}  // slot 0
};
}  // namespace idcoli

#endif
