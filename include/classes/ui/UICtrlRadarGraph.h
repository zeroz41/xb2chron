#ifndef CLASSES_UI_UICTRLRADARGRAPH_H
#define CLASSES_UI_UICTRLRADARGRAPH_H

#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlSimple.h"
#include "mm/mtl/Array.h"
#include "ui/UIUtil.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectNumberPlugin; }

namespace ui {
// table 0x7100B745C0; draws number plugins' values as the corners of a simple face shape (a radar chart)
class UICtrlRadarGraph : public ::ui::UICtrlObject {
public:
    // create's; the names of its fields are not the original's
    struct Setting {
        unsigned int m_value0;
        unsigned int m_value1;
    };
    // one corner (the field names are not the original's)
    struct Value {
        int m_number;                    // the value drawn: its plugin's number, or m_ctrl's while it moves
        UIObjectNumberPlugin* m_plugin;  // setNumberPlugin
        UICtrlSimple<1> m_ctrl;
    };
    // inline: 3.0.1 has no out-of-line copy (create holds its stores)
    UICtrlRadarGraph(unsigned int handle) : UICtrlObject(handle), m_setting() {
        m_values.setAllocator(UIUtil::getProgAllocator());
    }
    virtual ~UICtrlRadarGraph();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // a graph on the simple face shape of the object, one value per corner; null for another object
    static UICtrlRadarGraph* create(unsigned int handle, const Setting& setting);
    void setNumberPlugin(unsigned int index, unsigned int handle);  // the number plugin of the object handle
    mm::mtl::Array<Value> m_values;
    Setting m_setting;
};
}  // namespace ui

#endif
