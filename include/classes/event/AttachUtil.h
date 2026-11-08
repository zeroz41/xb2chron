#ifndef CLASSES_EVENT_ATTACHUTIL_H
#define CLASSES_EVENT_ATTACHUTIL_H

enum EVT_attachtype : int;
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace event {
// effect mount helpers (no table; the symbols name the class and its function)
class AttachUtil {
public:
    // mounts the effect id at the named point of the object's effect caster (on), else removes that mount;
    // nothing for handle -1 (AttachActorCS and AttachActorGf::setEffectMount; the parameter names are not the
    // original's)
    static void setMount(bool on, gf::GF_OBJ_HANDLE* handle, unsigned int id, const char* name, const mm::Vec3& pos,
                         bool flag, EVT_attachtype type);
};
}  // namespace event

#endif
