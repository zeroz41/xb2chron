#ifndef CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H

#include "classes/idcoli/IDColiObjChar.h"

namespace idcoli { class IDColiTreeTop; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

// the kind of test IDColiMove and IDColiObjCharCheck::testType* make; testType* treats 1 and 2 specially (only with
// flag 0x400 / only without it). The enumerators are not known.
enum ColiCheckType : int {};

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
    bool testTypeLine(IDColiResult& result, const IDColiInput& input, ColiCheckType type);
    bool testTypeSphere(IDColiResult& result, const IDColiInput& input, ColiCheckType type);
    bool testTypeCapsule(IDColiResult& result, const IDColiInput& input, ColiCheckType type);
    virtual ~IDColiObjCharCheck() {}  // slot 0
};
}  // namespace idcoli

#endif
