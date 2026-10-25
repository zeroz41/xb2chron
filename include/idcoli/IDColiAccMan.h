#ifndef IDCOLI_IDCOLIACCMAN_H
#define IDCOLI_IDCOLIACCMAN_H

namespace idcoli { class IDColiObj; }
namespace mm { class Vec3; }

namespace idcoli {
// the access to the collision manager's objects: one on the stack creates them
class IDColiAccMan {
public:
    IDColiAccMan();
    IDColiObj* createColiGrand(const void* data);
    IDColiObj* createColiCharacter();  // an IDColiObjCharCheck
    IDColiObj* createColiPhantom();
    // the bounds of every grand object; false (and a 100-unit box) when there is none (the names are not the
    // original's)
    bool getGrandAABB(mm::Vec3& max, mm::Vec3& min) const;
    // fw::RenderParam::setCloudSea hands it the cloud sea's number (the parameter name is not the original's)
    void setSubNum(unsigned int num);
};
}  // namespace idcoli

#endif
