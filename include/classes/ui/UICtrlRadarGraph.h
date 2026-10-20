#ifndef CLASSES_UI_UICTRLRADARGRAPH_H
#define CLASSES_UI_UICTRLRADARGRAPH_H

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B745C0
class UICtrlRadarGraph {
public:
    virtual ~UICtrlRadarGraph();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif
