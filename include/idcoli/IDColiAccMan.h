#ifndef IDCOLI_IDCOLIACCMAN_H
#define IDCOLI_IDCOLIACCMAN_H

namespace idcoli { class IDColiObj; }

namespace idcoli {
// the access to the collision manager's objects: one on the stack creates them
class IDColiAccMan {
public:
    IDColiAccMan();
    IDColiObj* createColiCharacter();  // an IDColiObjCharCheck
    // fw::RenderParam::setCloudSea hands it the cloud sea's number (the parameter name is not the original's)
    void setSubNum(unsigned int num);
};
}  // namespace idcoli

#endif
