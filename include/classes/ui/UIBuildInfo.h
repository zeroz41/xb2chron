#ifndef CLASSES_UI_UIBUILDINFO_H
#define CLASSES_UI_UIBUILDINFO_H

namespace ui {
// table none (its derived classes')
class UIBuildInfo {
public:
    class ObjectData;
    virtual ~UIBuildInfo();  // slot 0
    virtual void update();  // slot 2
    virtual void isReady() const;  // slot 3
    virtual void isValid() const;  // slot 4
};
}  // namespace ui

#endif
