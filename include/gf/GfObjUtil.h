#ifndef GF_GFOBJUTIL_H
#define GF_GFOBJUTIL_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObj; }

namespace gf {

// helpers for the objects behind handles (functions, by its symbols)
class GfObjUtil {
public:
    // the object behind a handle, none for an invalid handle or one with no object
    static gf::GfObj* getObj(gf::GF_OBJ_HANDLE* handle);
    static bool isTalking(gf::GF_OBJ_HANDLE* handle);
};

}  // namespace gf

#endif
