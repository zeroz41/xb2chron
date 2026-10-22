#ifndef CLASSES_FW_WINDIMPLUSE_H
#define CLASSES_FW_WINDIMPLUSE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace wnd { class LocalWind; }

namespace fw {
// table 0x710117A1E8 in 1.0.0 (the update keeps neither it nor the constructor and destructors); counted. A
// gust: a local wind that fades out over its time. Its list node base is what WindManager's impulse list links.
class WindImpluse : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNodeBase {
public:
    WindImpluse(const mm::Vec3& pos, float radius, float dampingNear, float power, float time);
    virtual ~WindImpluse();  // slot 0
    // false once its time is up (WindManager::update then releases it)
    bool update(const UpdateInfo& info);

    // the field names are not the original's
    wnd::LocalWind* m_pWind;  // 1.0.0's constructor makes it
    float m_elapsed;  // the time it has run
    float m_time;  // the constructor's: how long it blows
    float m_power;  // the constructor's: its wind's power at the start
};
}  // namespace fw

#endif
