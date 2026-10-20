#ifndef CLASSES_GF_IEVENTZONE_H
#define CLASSES_GF_IEVENTZONE_H

namespace gf {
// table none (its derived classes')
class IEventZone {
public:
    virtual ~IEventZone();  // slot 0
    virtual void changeZone(unsigned int, unsigned int);  // slot 2
    virtual void changeZoneLock(unsigned int, unsigned int);  // slot 3
    virtual void recreateZone(unsigned int);  // slot 4
    virtual void changeRoom(bool);  // slot 5
};
}  // namespace gf

#endif
