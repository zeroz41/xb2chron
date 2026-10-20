#ifndef CLASSES_ML_DEBDRAW_H
#define CLASSES_ML_DEBDRAW_H

#include "classes/ml/DevGraphCB.h"

namespace mm { class Col3; }
namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B761D0
class DebDraw : public ::ml::DevGraphCB {
public:
    enum PRM_DATA : int;
    virtual ~DebDraw();  // slot 0
    virtual void fastSetup() = 0;  // slot 7
    virtual void restoreShader() = 0;  // slot 8
    virtual void begin(unsigned int, unsigned int) = 0;  // slot 9
    virtual void end() = 0;  // slot 10
    virtual void add(mm::Vec3 const&, mm::Vec3 const&) = 0;  // slot 11
    virtual void add(mm::Pnt<int> const&, mm::Pnt<int> const&) = 0;  // slot 12
    virtual void add(int, int, int, int) = 0;  // slot 13
    virtual void add(mm::Vec3 const&) = 0;  // slot 14
    virtual void add(mm::Pnt<int> const&) = 0;  // slot 15
    virtual void add(float, float, float) = 0;  // slot 16
    virtual void add(int, int, int) = 0;  // slot 17
    virtual void add(int, int) = 0;  // slot 18
    virtual void add(mm::Vec3 const&, mm::Col4 const&) = 0;  // slot 19
    virtual void add(mm::Vec3 const&, mm::Col3 const&) = 0;  // slot 20
    virtual void add(int, int, mm::Col4 const&) = 0;  // slot 21
    virtual void add(int, int, mm::Col3 const&) = 0;  // slot 22
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Col4 const&) = 0;  // slot 23
    virtual void add(mm::Rect<int> const&) = 0;  // slot 24
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3 const&) = 0;  // slot 25
    virtual void setPerspective(float, float, float, mm::Mat44 const&, mm::Vec3 const*);  // slot 26
    virtual void setOrtho();  // slot 27
    virtual void clear();  // slot 28
};
}  // namespace ml

#endif
