#ifndef GF_GFOBJUPDATE_H
#define GF_GFOBJUPDATE_H

namespace fw { class UpdateInfo; }
namespace gf { class GfObj; }

namespace gf {
// an object's per-frame updates (functions, by its symbols)
class GfObjUpdate {
public:
    // runs obj's components' updates while its m_execUpdate is set
    static void updateComponent(GfObj* obj, const fw::UpdateInfo& info);
};
}  // namespace gf

#endif
