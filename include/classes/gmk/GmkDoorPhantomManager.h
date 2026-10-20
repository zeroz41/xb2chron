#ifndef CLASSES_GMK_GMKDOORPHANTOMMANAGER_H
#define CLASSES_GMK_GMKDOORPHANTOMMANAGER_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gmk {
// table 0x7100B6CDE8
class GmkDoorPhantomManager {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GmkDoorPhantomManager();  // slot 1
};
}  // namespace gmk

#endif
