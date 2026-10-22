#ifndef CLASSES_UI_UITEXTFILE_H
#define CLASSES_UI_UITEXTFILE_H

namespace ui {
// table 0x7100B75538; a message table UITextManager hands texts out of (0x58 bytes: create's allocation)
class UITextFile {
public:
    virtual ~UITextFile();  // slot 0
    static UITextFile* create(unsigned char* data);  // one for the table data, named after its sheet
    void reload();  // the table again, by its name (Bdat::getFP)
    const char* getText(unsigned int id) const;  // null without a table
    unsigned short getStyle(unsigned int id) const;  // 0xFFFF without a table

    unsigned char* m_data;  // the table (the name is not the original's)
    char m_name[0x40];      // its sheet's name, which reload looks it up by (the name is not the original's)
    int m_nameLength;       // strlen of m_name (the name is not the original's)
};
}  // namespace ui

#endif
