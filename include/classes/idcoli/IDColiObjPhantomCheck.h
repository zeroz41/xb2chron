#ifndef CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H

#include "classes/idcoli/IDColiObjPhantom.h"

namespace idcoli { class IDColiTreeTop; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

namespace idcoli {
// table 0x7100B7F258
class IDColiObjPhantomCheck : public ::idcoli::IDColiObjPhantom {
public:
    IDColiObjPhantomCheck(IDColiTreeTop* tree);
    bool testResultLine(IDColiResult& result, const IDColiInput& input);
    bool testResultSphere(IDColiResult& result, const IDColiInput& input);
    bool testResultCapsule(IDColiResult& result, const IDColiInput& input);
    bool testCheckLine(IDColiResult& result, const IDColiInput& input);
    bool testCheckSphere(IDColiResult& result, const IDColiInput& input);
    bool testCheckCapsule(IDColiResult& result, const IDColiInput& input);
    virtual ~IDColiObjPhantomCheck() {}  // slot 0
};
}  // namespace idcoli

#endif
