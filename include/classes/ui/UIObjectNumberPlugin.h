#ifndef CLASSES_UI_UIOBJECTNUMBERPLUGIN_H
#define CLASSES_UI_UIOBJECTNUMBERPLUGIN_H

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75160
class UIObjectNumberPlugin {
public:
    virtual ~UIObjectNumberPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif
