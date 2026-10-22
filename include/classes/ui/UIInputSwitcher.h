#ifndef CLASSES_UI_UIINPUTSWITCHER_H
#define CLASSES_UI_UIINPUTSWITCHER_H

#include "mm/mtl/Array.h"

namespace ui {
// table 0x7100B74C30; one of several UI objects' input layers enabled at a time (the names of its fields are not
// the original's)
class UIInputSwitcher {
public:
    explicit UIInputSwitcher(unsigned int num);
    virtual ~UIInputSwitcher();  // slot 0
    void clearInputObject();
    bool setInputObject(unsigned int index, unsigned int handle);
    unsigned int getInputObject(unsigned int index);
    void disable();
    void enable(unsigned int index);

    mm::mtl::Array<unsigned int> m_objects;  // the UI objects' handles, by index
    int m_active;                            // the index enable enabled, -1 for none
};
}  // namespace ui

#endif
