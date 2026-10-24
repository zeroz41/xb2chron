#ifndef CLASSES_ML_SCNDEBUGMANIPU_H
#define CLASSES_ML_SCNDEBUGMANIPU_H

#include "classes/ml/IWorkEvent.h"

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77C48
class ScnDebugManipu : public ::ml::IWorkEvent {
public:
    void createTrans(const mm::Mat44* mtx, const mm::Vec3* pos);
    void createRot(const mm::Mat44* mtx, const mm::Vec3* pos);
    virtual ~ScnDebugManipu();  // slot 0
};
}  // namespace ml

#endif
