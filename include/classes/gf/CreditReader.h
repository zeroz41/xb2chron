#ifndef CLASSES_GF_CREDITREADER_H
#define CLASSES_GF_CREDITREADER_H

namespace gf {
// table 0x7100B5E458: reads the staff roll's credit file ("CRT" magic: a row count, then 0x40-byte rows and the
// strings they point into, both by offset from the file); GfMenuObjStaffroll binds and reads it
class CreditReader {
public:
    // one column of a row as getRow hands it out (the field names are not the original's)
    struct Column {
        bool m_enable;      // the file's word is positive
        int m_param0;
        int m_param1;
        const char* m_text;  // null when the file's offset is -1
    };
    // a row as getRow hands it out (the field names are not the original's)
    struct Row {
        int m_id;
        bool m_skip;  // the file's word is positive; the columns are then cleared
        int m_param;
        Column m_columns[3];
    };
    // the file's layout (the type and field names are not the original's)
    struct FileColumn {
        int m_enable;
        int m_param0;
        int m_param1;
        int m_textOffset;  // into the strings, or -1
    };
    struct FileRow {
        int m_id;
        int m_skip;
        int m_param;
        int pad_0C;
        FileColumn m_columns[3];
    };
    struct FileHeader {
        int m_magic;  // 'CRT'
        int m_rowCount;
        int m_rowOffset;
        int m_textOffset;
    };

    CreditReader();
    virtual ~CreditReader();  // slot 0
    void bind(void* data, int size);
    int getRowCount();
    bool getRow(int index, Row& row);

    // the bound file, its row count, rows and strings (the names are not the original's)
    FileHeader* m_data;
    int m_rowCount;
    FileRow* m_rows;
    const char* m_text;
};
}  // namespace gf

#endif
