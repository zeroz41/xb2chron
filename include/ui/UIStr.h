#ifndef UI_UISTR_H
#define UI_UISTR_H

namespace ui {

// a UI text (0x18 bytes: UIObjectTextPlugin keeps one at 0x80 of its 0x98)
class UIStr {
public:
    UIStr();
    UIStr(unsigned char* bdat, unsigned int id);  // the text a message table has at that id
    UIStr(const char* text, bool);  // a text as it is (GfMenuGameAdapter passes false)
    UIStr(const UIStr& other);  // out of line: GfMenuStrLinker::addSelectString calls it
    ~UIStr();
    unsigned int size() const;
    bool isValid() const;
    bool compare(const UIStr& other);  // true when they are the same text
    void copy(const UIStr& other);
    void release();  // frees the text (GfMenuStrLinker::delString)
    const char* c_str() const;
    void deepcopy(const UIStr& other);  // a copy of the other's text of its own
    unsigned short getStyle() const;  // the font style its text names
    unsigned char pad_00[0x10];
    unsigned short m_type;  // 1: a message table's text (the (bdat, id) constructor's; getMsgID answers only then)
    // what the text belongs to: GfMenuEnhanceAdapter::getEnhanceCaption stores the enhancement's id, copy copies it;
    // the name is not the original's
    unsigned short m_ownerId;
    unsigned char pad_14[4];
};

}  // namespace ui

#endif
