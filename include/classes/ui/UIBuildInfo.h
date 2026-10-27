#ifndef CLASSES_UI_UIBUILDINFO_H
#define CLASSES_UI_UIBUILDINFO_H

namespace ui {
// table none (its derived classes')
class UIBuildInfo {
public:
    // one object of a layout: UIBuildInfoBdat::getObjectData fills it from a BDAT table's row (the column names are
    // the original's strings; the field names are not the original's), UIBuildInfoUIO's copies one of its 0xc0-byte
    // records. Fields no reader in this file writes keep descriptive placeholders.
    struct ObjectData {
        const char* m_name;          // "name"
        const char* m_parent;        // "parent"
        const char* m_attachLayout;  // "attach_layout"
        const char* m_layoutFile;    // not read from the BDAT table (not the original's)
        const char* m_layoutName;    // not read from the BDAT table (not the original's)
        const char* m_resourceFile;  // the "file" of the "resource" row in the type's resource table
        unsigned char m_type;        // "type"
        short m_offsX;               // "offs_x"
        short m_offsY;               // "offs_y"
        unsigned int m_attr;         // 0 by default; an integer (its store is not merged with the floats')
                                     // (not the original's)
        float m_scaleX;              // 1 by default (not the original's)
        float m_scaleY;              // 1 by default (not the original's)
        float m_alpha;               // 1 by default (not the original's)
        unsigned short m_priority;   // "priority"
        unsigned char m_flagA;       // 0 by default (not the original's)
        bool m_defUndisp;            // "def_undisp" == 1
        bool m_resourceIsFile;       // set for type 9's resource (not the original's)
        unsigned char m_flagB;       // 0 by default (not the original's)
        unsigned short m_flagC;      // 0 by default (not the original's)
        const char* m_strA;          // 0 by default (not the original's)
        const char* m_strB;          // 0 by default (not the original's)
        unsigned char m_inputType;   // "input_type"
        unsigned short m_inputId;    // "input_id"
        unsigned char m_inputFlag;   // 0 by default (not the original's)
        const char* m_strC;          // 0 by default (not the original's)
        int m_index;                 // -1 by default (not the original's)
        unsigned char m_textFlag;    // 0 by default (not the original's)
        unsigned int m_textA;        // 0 by default (not the original's)
        unsigned int m_textB;        // 0 by default (not the original's)
        unsigned short m_textC;      // 0 by default (not the original's)
        unsigned char m_textD;       // 0 by default (not the original's)
        int m_textId;                // "text_id" when not 0
        unsigned char m_textAlignH;  // "text_align_h"
        unsigned char m_textAlignV;  // "text_align_v"
        unsigned char m_textProp;    // "text_prop"
        unsigned int m_extA;         // 0 by default (not the original's)
        unsigned int m_extB;         // 0 by default (not the original's)
        const char* m_extC;          // 0 by default (not the original's)
        const char* m_extD;          // 0 by default (not the original's)
        unsigned char m_extE;        // 0 by default (not the original's)
        unsigned short m_extF;       // 0 by default (not the original's)
        unsigned int m_extG;         // 0 by default (not the original's)
        unsigned short m_extH;        // 0 by default (not the original's)
        const char* m_extI;          // 0 by default (not the original's)

        ObjectData()
            : m_name(0), m_parent(0), m_attachLayout(0), m_layoutFile(0), m_layoutName(0), m_resourceFile(0),
              m_type(0), m_offsX(0), m_offsY(0), m_attr(0), m_scaleX(1.0f), m_scaleY(1.0f), m_alpha(1.0f),
              m_priority(0), m_flagA(0), m_defUndisp(false), m_resourceIsFile(false), m_flagB(0), m_flagC(0),
              m_strA(0), m_strB(0), m_inputType(0), m_inputId(0), m_inputFlag(0), m_strC(0), m_index(-1),
              m_textFlag(0), m_textA(0), m_textB(0), m_textC(0), m_textD(0), m_textId(0),
              m_textAlignH(0), m_textAlignV(0), m_textProp(0), m_extA(0), m_extB(0), m_extC(0), m_extD(0),
              m_extE(0), m_extF(0), m_extG(0), m_extH(0), m_extI(0) {}
    };
    virtual ~UIBuildInfo() {}  // slot 0
    virtual void update() {}  // slot 2
    virtual bool isReady() const { return true; }  // slot 3
    virtual bool isValid() const { return true; }  // slot 4
    virtual unsigned int getObjectNum() const = 0;  // slot 5
    virtual void getObjectData(unsigned int index, ObjectData& data) const = 0;  // slot 6
    virtual const char* getName() const = 0;  // slot 7
};
}  // namespace ui

#endif
