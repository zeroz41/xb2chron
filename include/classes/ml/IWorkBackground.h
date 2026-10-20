#ifndef CLASSES_ML_IWORKBACKGROUND_H
#define CLASSES_ML_IWORKBACKGROUND_H

namespace ml {
// table 0x7100B3A1E8
class IWorkBackground {
public:
    virtual ~IWorkBackground();  // slot 0
    virtual void bkgHomeMenu(bool);  // slot 2
    virtual void bkgHomeMenuDenied();  // slot 3
};
}  // namespace ml

#endif
