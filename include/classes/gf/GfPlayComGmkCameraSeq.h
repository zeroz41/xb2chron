#ifndef CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H
#define CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"
#include "classes/gf/GfGameScene.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace fw { class Camera; }
namespace gf {
// table 0x7100B57F78
class GfPlayComGmkCameraSeq : public GfPlayCom {
public:
    // the field names are not the original's
    GfPlayComGmkCameraSeq(mm::mtl::IntrusivePtr<fw::Camera> camera) : GfPlayCom(31, false), m_camera() {
        m_camera = camera;
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            m_pause = scene->createPlayerPause();
        }
        s_activate++;
    }
    static GfPlayComGmkCameraSeq* create(mm::mtl::IntrusivePtr<fw::Camera> camera);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComGmkCameraSeq();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComGmkCameraSeq";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the symbol's own name
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // create's; update waits while it is pushed
    unsigned int m_pause;                        // GfGameScene::createPlayerPause's, destroyed by end()
};
}  // namespace gf

#endif
