#ifndef CLASSES_ML_DEBDRAWCMD_H
#define CLASSES_ML_DEBDRAWCMD_H

#include "classes/ml/DebDraw.h"

namespace mm { class Col3; }
namespace mm { class Col4; }
namespace mm { class Vec3; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B762C8
class DebDrawCmd : public ::ml::DebDraw {
public:
    virtual ~DebDrawCmd();  // slot 0
    virtual void fastSetup();  // slot 7
    virtual void restoreShader() {}  // slot 8
    virtual void begin(unsigned int, unsigned int);  // slot 9
    virtual void end();  // slot 10
    virtual void add(mm::Vec3 const&, mm::Vec3 const&);  // slot 11
    virtual void add(mm::Pnt<int> const&, mm::Pnt<int> const&);  // slot 12
    virtual void add(int, int, int, int);  // slot 13
    virtual void add(mm::Vec3 const&);  // slot 14
    virtual void add(mm::Pnt<int> const&);  // slot 15
    virtual void add(float, float, float);  // slot 16
    virtual void add(int, int, int);  // slot 17
    virtual void add(int, int);  // slot 18
    virtual void add(mm::Vec3 const&, mm::Col4 const&);  // slot 19
    virtual void add(mm::Vec3 const&, mm::Col3 const&);  // slot 20
    virtual void add(int, int, mm::Col4 const&);  // slot 21
    virtual void add(int, int, mm::Col3 const&);  // slot 22
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Col4 const&);  // slot 23
    virtual void add(mm::Rect<int> const&);  // slot 24
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3 const&);  // slot 25
};
}  // namespace ml

#endif
