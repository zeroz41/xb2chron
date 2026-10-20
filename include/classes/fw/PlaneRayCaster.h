#ifndef CLASSES_FW_PLANERAYCASTER_H
#define CLASSES_FW_PLANERAYCASTER_H

namespace mm { class Vec3; }

namespace fw {
// table 0x7100B419C8
class PlaneRayCaster {
public:
    virtual ~PlaneRayCaster();  // slot 0
    virtual void castRay(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3*, mm::Vec3*);  // slot 2
};
}  // namespace fw

#endif
