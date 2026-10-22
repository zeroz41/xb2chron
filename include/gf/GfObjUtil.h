#ifndef GF_GFOBJUTIL_H
#define GF_GFOBJUTIL_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObj; }
namespace gf { class GfObjSetup; }

namespace gf {

// helpers for the objects behind handles (functions, by its symbols)
class GfObjUtil {
public:
    // the object behind a handle, none for an invalid handle or one with no object
    static gf::GfObj* getObj(gf::GF_OBJ_HANDLE* handle);
    static bool isValid(gf::GF_OBJ_HANDLE* handle);
    static bool isTalking(gf::GF_OBJ_HANDLE* handle);
    // the setup of the object behind a handle (its object info's), none without an info
    static gf::GfObjSetup* getObjSetup(gf::GF_OBJ_HANDLE* handle);
    // whether the object plays the DLC versions of its sounds (WaterInPlugin::onEvent prefixes their names with
    // "dlc_"): a blade-type object (DataParamAcc's type 3) whose bdat id GfDataBlade's fn_710023F9A8 accepts.
    // The name is not the original's (the symbols call it fn_7100552DF4).
    static bool isDlcSound(gf::GF_OBJ_HANDLE* handle);
};

}  // namespace gf

#endif
