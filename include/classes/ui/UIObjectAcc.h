#ifndef CLASSES_UI_UIOBJECTACC_H
#define CLASSES_UI_UIOBJECTACC_H

namespace ui { class UIObject; }
namespace mm { class Mat44; }

namespace ui {
// table 0x7100B75718
class UIObjectAcc {
public:
    UIObjectAcc(unsigned int handle);
    UIObjectAcc(unsigned int handle, const char* child);  // the child UIUtil::searchChild finds, if one is named
    virtual ~UIObjectAcc();  // slot 0
    void setDispChild(bool disp, const char* child);
    bool isTerm() const;
    void setMatrix(const mm::Mat44& matrix);
    UIObject* m_object;      // UIUtil::getObject(m_handle): isTerm reads its flags, setTerm calls its setTerm
    unsigned int m_handle;   // what the constructor is given (or its named child's)
};
}  // namespace ui

#endif
