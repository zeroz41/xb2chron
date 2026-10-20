#ifndef CLASSES_ML_DRRESMDOINSTPARTSOBJ_H
#define CLASSES_ML_DRRESMDOINSTPARTSOBJ_H

namespace mm { class Mat44; }

namespace ml {
// table 0x7100B7D7F8
class DrResMdoInstPartsObj {
public:
    virtual ~DrResMdoInstPartsObj();  // slot 0
    virtual void setPosFrame(float);  // slot 2
    virtual void getPosFrame() const;  // slot 3
    virtual void getPosMaxFrame() const;  // slot 4
    virtual void getPosStartFrame() const;  // slot 5
    virtual void setNodeFrame(float);  // slot 6
    virtual void getNodeFrame() const;  // slot 7
    virtual void getCalcNodeFrame() const;  // slot 8
    virtual void getCalcOldNodeFrame() const;  // slot 9
    virtual void getNodeMaxFrame() const;  // slot 10
    virtual void getNodeStartFrame() const;  // slot 11
    virtual void getSwitchID() const;  // slot 12
    virtual void setSwitchID(unsigned char);  // slot 13
    virtual void getSwitchMax() const;  // slot 14
    virtual void getSwitchIndex(unsigned int) const;  // slot 15
    virtual void update();  // slot 16
    virtual void getMatrix(mm::Mat44&) const;  // slot 17
    virtual void getAnmMatrix(mm::Mat44&) const;  // slot 18
    virtual void setMatrix(mm::Mat44 const&);  // slot 19
};
}  // namespace ml

#endif
