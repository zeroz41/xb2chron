#ifndef CLASSES_ML_SCNOBJMODEL_H
#define CLASSES_ML_SCNOBJMODEL_H

#include "classes/ml/ScnObj.h"

namespace ml { class DebDraw; }
namespace ml { class WinProc; }
namespace mm { class Mat44; }
namespace mm { class Quat; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77F00
class ScnObjModel : public ::ml::ScnObj {
public:
    enum RENDER_INFO : int;
    enum RENDER_OFFSET_INFO : int;
    // the offset its render applies (fw::ModelObject::update copies its added offset there; the return type is
    // not in the symbol)
    mm::Vec3& getOffsetInfo(bool);
    virtual ~ScnObjModel();  // slot 0
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void tail();  // slot 5
    virtual void getName() const;  // slot 6
    virtual void setDelete();  // slot 7
    virtual void setPos(mm::Vec3 const&);  // slot 8
    virtual void setPosWarp(mm::Vec3 const&);  // slot 9
    virtual void addPos(mm::Vec3 const&);  // slot 10
    virtual void setRot(mm::Vec3 const&);  // slot 11
    virtual void addRot(mm::Vec3 const&);  // slot 12
    virtual void addRot(mm::Quat const&);  // slot 13
    virtual void setScl(mm::Vec3 const&);  // slot 14
    virtual void addScl(mm::Vec3 const&);  // slot 15
    virtual void setMat(mm::Mat44 const&);  // slot 16
    virtual void setAlpha(float) = 0;  // slot 17
    virtual void getAlpha() const = 0;  // slot 18
    virtual void setWriteStencil(bool) = 0;  // slot 19
    virtual void setAlwaysTexStm(bool) = 0;  // slot 20
    virtual void isMdlTexStm() const = 0;  // slot 21
    virtual void isMemTexStm() const = 0;  // slot 22
    virtual void getAABBMax() const = 0;  // slot 23
    virtual void getAABBMin() const = 0;  // slot 24
    virtual void getCenter() const = 0;  // slot 25
    virtual void getLength() const = 0;  // slot 26
    virtual void setGroups(int) = 0;  // slot 27
    virtual void getGroups() = 0;  // slot 28
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*) {}  // slot 29
};
}  // namespace ml

#endif
