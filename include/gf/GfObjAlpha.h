#ifndef GF_GFOBJALPHA_H
#define GF_GFOBJALPHA_H

namespace gf {
class GF_OBJ_HANDLE;
class GfObjAcc;

// the camera fade of objects (symbols name both functions; a class of static functions like GfObjUtil:
// the mangling does not tell a class from a namespace)
class GfObjAlpha {
public:
    // GfObjManager::updateChangeParamObjects calls it for each object
    static void updateCamera(GF_OBJ_HANDLE* handle, float rate, bool force);
    // GfGameObj::checkEnableGameObj calls it
    static bool isNearCamera(const GfObjAcc& acc);
};

}  // namespace gf

#endif
