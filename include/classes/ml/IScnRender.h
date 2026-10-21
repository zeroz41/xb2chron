#ifndef CLASSES_ML_ISCNRENDER_H
#define CLASSES_ML_ISCNRENDER_H

namespace ml { class Scn; }
namespace ml { enum SCNPRIO_CB : int; }

namespace ml {
// table 0x7100B3A1A0
class IScnRender {
public:
    virtual ~IScnRender() {}  // slot 0
    virtual void cbPreUpdate(ml::Scn*, ml::SCNPRIO_CB) {}  // slot 2
    virtual void cbManipuPickOn(ml::Scn*, ml::SCNPRIO_CB) {}  // slot 3
    virtual void cbManipuPickOff(ml::Scn*, ml::SCNPRIO_CB) {}  // slot 4
    virtual void cbManipuPickMove(ml::Scn*, ml::SCNPRIO_CB) {}  // slot 5
    virtual void cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB) {}  // slot 6
};
}  // namespace ml

#endif
