#ifndef CLASSES_FW_SPHERICALCOORDINATESIKSOLVER_H
#define CLASSES_FW_SPHERICALCOORDINATESIKSOLVER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41BF8
class SphericalCoordinatesIkSolver {
public:
    virtual ~SphericalCoordinatesIkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual void isEnable() const;  // slot 4
};
}  // namespace fw

#endif
