#ifndef CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H
#define CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace fw { class Camera; }
namespace gf {
// table 0x7100B57F78
class GfPlayComGmkCameraSeq : public GfPlayCom {
public:
    static GfPlayComGmkCameraSeq* create(mm::mtl::IntrusivePtr<fw::Camera> camera);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComGmkCameraSeq();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
