#ifndef CLASSES_GF_AFIELDLOCATOR_H
#define CLASSES_GF_AFIELDLOCATOR_H

namespace gf {
// table none (its derived classes')
class AFieldLocator {
public:
    virtual ~AFieldLocator();  // slot 0
    virtual void getIconBdatId() const;  // slot 2
    virtual void getPosNum() const = 0;  // slot 3
    virtual void getPos(unsigned int) const = 0;  // slot 4
    virtual void getMapBdatId() const;  // slot 5
    unsigned char pad_8[0x10];  // fields: size from its derived classes
};
}  // namespace gf

#endif
