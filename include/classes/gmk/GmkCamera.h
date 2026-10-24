#ifndef CLASSES_GMK_GMKCAMERA_H
#define CLASSES_GMK_GMKCAMERA_H

#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gmk {
// table 0x7100B52548; 0x160 bytes on a 16-byte boundary (GfFieldMapGimmick holds one at 0xB0, after its GmkAcc
// ends at 0xA8)
class alignas(16) GmkCamera {
public:
    class CreateInfo;
    explicit GmkCamera(const CreateInfo* info);
    // inline: GfFieldMapGimmick's destructor stores this table and calls dispose() in place, then releases m_camera
    virtual ~GmkCamera() {  // slot 0
        dispose();
    }
    void dispose();
    bool isLoaded() const;
    bool isEnd() const;
    void update(float dt);
    void play();
    unsigned char pad_8[0x138];
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // released by the destructor (the name is not the original's)
    unsigned char pad_148[0x18];
};
}  // namespace gmk

#endif
