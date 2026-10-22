#ifndef CLASSES_GF_GFFIELDLODCOLIANIM_H
#define CLASSES_GF_GFFIELDLODCOLIANIM_H

namespace fw { class UpdateInfo; }

namespace gf {
// a class with no table: what is declared inside it
class GfFieldLodColiAnim {
public:
    class ColiUserData;
    // an object's user data 1 (GfComBehaviorMapLodAnim updates it each frame)
    class PosInfo {
    public:
        void update(fw::UpdateInfo const& info);
    };
};
}  // namespace gf

#endif
