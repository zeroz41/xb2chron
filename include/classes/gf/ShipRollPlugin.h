#ifndef CLASSES_GF_SHIPROLLPLUGIN_H
#define CLASSES_GF_SHIPROLLPLUGIN_H

namespace fw { class Camera; }

namespace gf {
// table 0x7100B45EE8
class ShipRollPlugin {
public:
    virtual ~ShipRollPlugin();  // slot 0
    virtual void update(fw::Camera*);  // slot 2
};
}  // namespace gf

#endif
