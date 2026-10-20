#ifndef CLASSES_GF_GFMENUOBJECT_H
#define CLASSES_GF_GFMENUOBJECT_H

namespace gf {
// table 0x7100B5EE40
class GfMenuObject {
public:
    virtual ~GfMenuObject();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void reloadParam();  // slot 5
    virtual void eventHudSceneChange(unsigned int);  // slot 6
    unsigned char pad_8[0x20];  // fields: size from its derived classes
};
}  // namespace gf

#endif
