#ifndef IDCOLI_IDCOLIINPUTUTIL_H
#define IDCOLI_IDCOLIINPUTUTIL_H

namespace idcoli { class IDColiInput; }
namespace idcoli { class IDCmfPosData; }

namespace idcoli {

// builds a query input (defined in IDColiUtilColiSimple's unit). The PosData forms take a source input into the
// space of a grand part's position record (IDColiObjGrdChar::test* call them before the part's IDColiGrandObj test).
class IDColiInputUtil {
public:
    static void getLine(IDColiInput& out, const IDColiInput& input, const IDCmfPosData* posData, bool);
    static void getRay(IDColiInput& out, const IDColiInput& input, const IDCmfPosData* posData, bool);
    static void getSphere(IDColiInput& out, const IDColiInput& input, const IDCmfPosData* posData, bool);
    static void getCapsule(IDColiInput& out, const IDColiInput& input, const IDCmfPosData* posData, bool);
};

}  // namespace idcoli

#endif
