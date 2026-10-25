#ifndef ML_SCNOBJACCPARTSPOS_H
#define ML_SCNOBJACCPARTSPOS_H

#include "classes/ml/DrResMdoInstPartsObj.h"

namespace mm { class Mat44; }

namespace ml {
// access to one instanced part (ScnObjAccSeamPos::getObj returns it by value, through memory: not trivially copyable)
class ScnObjAccPartsPos {
public:
    explicit ScnObjAccPartsPos(DrResMdoInstPartsObj* obj) : m_obj(obj) {}
    ~ScnObjAccPartsPos() {}
    void setMatrix(const mm::Mat44& mat);
    void getMatrix(mm::Mat44& mat);
    const char* getName() const;
    unsigned int getID() const;
    bool isPosAnm() const;
    bool isNodeAnm() const;
    bool isPosMatrix() const;
    bool isRandomStart() const;
    bool isSwitch() const;
    bool isColiOff() const;
    bool isColiSkipData() const;
    void setAlpha(float alpha);
    bool isLoop() const;
    void setPosFrame(float frame);
    float getPosFrame() const;
    float getPosMaxFrame() const;
    float getPosStartFrame() const;
    void setNodeFrame(float frame);
    float getNodeFrame() const;
    float getNodeMaxFrame() const;
    float getNodeStartFrame() const;
    void getAnmMatrix(mm::Mat44* mat) const;
    unsigned char getSwitchID() const;
    void setSwitchID(unsigned int id);

    DrResMdoInstPartsObj* m_obj;  // the name is not the original's
};
}  // namespace ml

#endif
