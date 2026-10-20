#ifndef CLASSES_UI_UIOBJECTPLUGIN_H
#define CLASSES_UI_UIOBJECTPLUGIN_H

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B757B8
class UIObjectPlugin {
public:
    virtual ~UIObjectPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif
