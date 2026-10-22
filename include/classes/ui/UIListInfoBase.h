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
    unsigned int getRowSize() const;
    unsigned int getPageRowSize() const;  // the rows a page shows
    unsigned int getRowOffset() const;    // the first row shown
};
}  // namespace ui

#endif
