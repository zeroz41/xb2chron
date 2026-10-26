#ifndef CLASSES_ML_DRGLOBALIBLPACK_H
#define CLASSES_ML_DRGLOBALIBLPACK_H

namespace ml {
// The start of a global IBL file as checkFileType reads it (the type and field names are not the original's).
struct GlobalIBLFileHeader {
    unsigned int m_magic;
    unsigned int m_version;
};

// table 0x7100B7AD98
class DrGlobalIBLPack {
public:
    virtual ~DrGlobalIBLPack();  // slot 0

    // true for a global IBL file: the "GIBL" magic and version 10100 or 20000
    static bool checkFileType(const void* data);
    enum {
        FLAG_HIDE = 0x1,  // ScnObjIBLDr::apply sets it while the IBL is not displayed (the name is not the original's)
    };
    unsigned char pad_8[0x48];
    unsigned int m_flags;  // 0x50 (the name is not the original's)
    unsigned char pad_54[0x4];
    // 0x58, ScnObjIBLDr::setFromCaptureTool sets 2 (the name is not the original's)
    unsigned char m_captureMode;
};
}  // namespace ml

#endif
