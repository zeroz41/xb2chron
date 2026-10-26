#ifndef CLASSES_SSD_SOUNDLISTENER_H
#define CLASSES_SSD_SOUNDLISTENER_H

#include "classes/ssd/Object.h"
#include "ssd/Math.h"

namespace ssd {
// table 0x7100B81CF0: where the 3D sound is heard from. The constructor registers it with SoundCore::instance_
// (AddSoundListener); the destructor removes it again.
class SoundListener : public Object {
public:
    // a listener's placement (the names are not the original's)
    struct Placement {
        Vec3 position;
        Vec3 front;
        Vec3 up;
        // the last frame's position minus this one (UpdateGameFrame)
        Vec3 velocity;
    };

    SoundListener();
    virtual ~SoundListener();  // slot 0

    void Init();
    void SetPosition(const Vec3& position);
    void SetOrientation(const Vec3& front, const Vec3& up);
    bool IsEnableDoppler() const;
    void UpdateGameFrame(float frameTime);
    void Vec3Transform(const Vec3* v, Vec3* out);

    // the field names are not the original's
    Placement placement_;
    // the placement the matrix was last built from
    Placement applied_;
    // set while the listener is registered with SoundCore::instance_
    bool registered_;
    // set by SetPosition and SetOrientation; UpdateGameFrame recomputes the velocity
    bool moved_;
    // set by SetPosition and SetOrientation; UpdateGameFrame rebuilds the matrix
    bool changed_;
    // set when the velocity changed; UpdateGameFrame rebuilds the matrix
    bool velocityChanged_;
    // set once UpdateGameFrame built the matrix
    bool updated_;
    bool enableDoppler_;
    // 1.0 from the constructor; nothing here reads it
    float scale_;
    unsigned char pad_84[4];
    // the listener's view (Mat34LookAt from the applied placement)
    Mat34 matrix_;
};
}  // namespace ssd

#endif
