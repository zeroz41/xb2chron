#ifndef CLASSES_UI_UILISTINFOBASE_H
#define CLASSES_UI_UILISTINFOBASE_H

namespace ui {
// table 0x7100B74CD0
class UIListInfoBase {
public:
    class SetupParam;
    virtual ~UIListInfoBase();  // slot 0
    virtual void clear();  // slot 2
    virtual void update();  // slot 3
};
}  // namespace ui

#endif
