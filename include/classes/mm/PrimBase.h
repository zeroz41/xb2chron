#ifndef CLASSES_MM_PRIMBASE_H
#define CLASSES_MM_PRIMBASE_H

namespace mm { class Aabb; }
namespace mm { class Obb; }

namespace mm {
// table none (its derived classes')
class PrimBase {
public:
    virtual ~PrimBase() {}  // slot 0
    virtual void getOBB(mm::Obb&) const = 0;  // slot 2
    virtual void getAABB(mm::Aabb&) const = 0;  // slot 3
    virtual void getPos() const;  // slot 4
    virtual void getRot() const;  // slot 5
};
}  // namespace mm

#endif
