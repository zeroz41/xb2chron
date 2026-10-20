#ifndef CLASSES_FW_EFFECTCASTERSEND_H
#define CLASSES_FW_EFFECTCASTERSEND_H

namespace mm { class Mat44; }

namespace fw {
// table 0x7100B413D0
class EffectCasterSend {
public:
    virtual ~EffectCasterSend();  // slot 0
    virtual void getMdl();  // slot 2
    virtual void getStateName();  // slot 3
    virtual void getBindData(unsigned int&);  // slot 4
    virtual void getMdlFrame();  // slot 5
    virtual void getMdlScl();  // slot 6
    virtual void getMdlMat(mm::Mat44&);  // slot 7
    virtual void getEfpMat(mm::Mat44&, char const*);  // slot 8
};
}  // namespace fw

#endif
