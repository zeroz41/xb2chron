#ifndef GF_GFOBJUTIL_H
#define GF_GFOBJUTIL_H

#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_MOUNT_HANDLE; }
#include "gf/GFATTACH.h"
namespace gf { class GfAppendHandles; }
namespace gf { class GfComProperty; }
namespace gf { class GfObj; }
namespace gf { class GfObjSetup; }

namespace gf {

// a fade an animation annotation describes ("fadein_<frames>" or "fadeout_<frames>[_<numbers>]"), as
// GfObjUtil::parseFadeParam reads it (the field names are not the original's)
struct GfFadeInfo {
    int m_type;              // 1 "fadeout", 0 "fadein"
    unsigned int m_frames;   // the fade's length in frames
    mm::mtl::FixedVector<int, 6> m_values;  // the numbers after the length
};

// helpers for the objects behind handles (functions, by its symbols)
class GfObjUtil {
public:
    // the object behind a handle, none for an invalid handle or one with no object
    static gf::GfObj* getObj(gf::GF_OBJ_HANDLE* handle);
    // sets obj's m_execUpdate: whether its components are to be updated
    static void applyExecUpdate(gf::GfObj* obj);
    static bool isValid(gf::GF_OBJ_HANDLE* handle);
    // what the object behind handle has mounted at a point (its info's mount's), -1 without
    static gf::GF_MOUNT_HANDLE* getMountHandle(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    // the objects appended to an object's mount point 1 (GfMountManager::getAppendHandles)
    static gf::GfAppendHandles* getExtraMountObject(gf::GF_OBJ_HANDLE* handle);
    static void destroy(gf::GF_OBJ_HANDLE* handle);
    // attaches the object behind child to the one behind parent, and detaches it again
    static void attachGfObj(gf::GF_OBJ_HANDLE* parent, gf::GF_OBJ_HANDLE* child);
    static void dettachGfObject(gf::GF_OBJ_HANDLE* parent, gf::GF_OBJ_HANDLE* child);
    // the kind of the object behind a handle (its info's setup's), 0 without one; 5 is what isActiveRangeLure lures
    static int getObjType(gf::GF_OBJ_HANDLE* handle);
    // the property of the object behind a handle (its object info's), none without an info
    static gf::GfComProperty* getProperty(gf::GF_OBJ_HANDLE* handle);
    static bool isTalking(gf::GF_OBJ_HANDLE* handle);
    // the setup of the object behind a handle (its object info's), none without an info
    static gf::GfObjSetup* getObjSetup(gf::GF_OBJ_HANDLE* handle);
    // whether the object plays the DLC versions of its sounds (WaterInPlugin::onEvent prefixes their names with
    // "dlc_"): a blade-type object (DataParamAcc's type 3) whose bdat id GfDataBlade's fn_710023F9A8 accepts.
    // The name is not the original's (the symbols call it fn_7100552DF4).
    static bool isDlcSound(gf::GF_OBJ_HANDLE* handle);
    // the object's motion resource name (its data's), none without one
    static const char* getMotionResourceName(gf::GF_OBJ_HANDLE* handle);
    // reads a fade annotation's text into info: false when it is not one
    static bool parseFadeParam(const char* text, gf::GfFadeInfo* info);
};

}  // namespace gf

#endif
