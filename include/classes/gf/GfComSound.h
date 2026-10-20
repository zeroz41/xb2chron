#ifndef CLASSES_GF_GFCOMSOUND_H
#define CLASSES_GF_GFCOMSOUND_H

namespace gf {
// table 0x7100B69CC0
class GfComSound {
public:
    class SoundInfo;
    class ViewerListener;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComSound();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void vf4();  // slot 4
};
}  // namespace gf

#endif
