#ifndef CLASSES_GF_IGFOBJLISTENER_H
#define CLASSES_GF_IGFOBJLISTENER_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// what gf::GfObjManager::addListener registers and callGfObjListener calls (gf::GfObjManager::addListener(
// gf::IGfObjListener*, gf::IGfObjListener::OBJEVT)); no table of its own in the module
class IGfObjListener {
public:
    enum OBJEVT : int {};
    virtual void listenerGfObj(OBJEVT, GF_OBJ_HANDLE*, unsigned int) = 0;  // slot 0
};
}  // namespace gf

#endif
