#ifndef CLASSES_ML_DRGLOBALIBLPACK_H
#define CLASSES_ML_DRGLOBALIBLPACK_H

#include "grlib/CGLibVtlMemPool.h"
#include "mm/mtl/Vector.h"

namespace ml {
class DrLightObjGlobalIBL;

// The start of a global IBL file as checkFileType reads it (the type and field names are not the original's).
struct GlobalIBLFileHeader {
    unsigned int m_magic;
    unsigned int m_version;
};

// table 0x7100B7AD98
class DrGlobalIBLPack {
public:
    // data is the global IBL file; viewIdx the view whose DrShdLgtGlobalIBL takes the lights
    DrGlobalIBLPack(const void* data, int viewIdx);
    virtual ~DrGlobalIBLPack();  // slot 0
    // takes the lights out of the view's DrShdLgtGlobalIBL
    void release();

    // true for a global IBL file: the "GIBL" magic and version 10100 or 20000
    static bool checkFileType(const void* data);
    enum {
        FLAG_HIDE = 0x1,  // ScnObjIBLDr::apply sets it while the IBL is not displayed (the name is not the original's)
    };
    DrGlobalIBLPack* m_prev;  // 0x8, DrGlobalIBLMan's list links (the names are not the original's)
    DrGlobalIBLPack* m_next;  // 0x10
    // the names are not the original's
    int m_viewIdx;  // 0x18, DrShdLgtGlobalIBL::addObj/removeObj's view
    unsigned char pad_1c[0x4];
    const void* m_data;  // 0x20, the file
    mm::mtl::Vector<DrLightObjGlobalIBL*> m_lights;  // 0x28, resourceInit makes one per object of the file
    unsigned int m_flags;  // 0x50 (the name is not the original's)
    unsigned int m_prevFlags;  // 0x54, update keeps the frame's m_flags in it (the name is not the original's)
    // 0x58, ScnObjIBLDr::setFromCaptureTool sets 2 (the name is not the original's)
    unsigned char m_captureMode;
    unsigned char pad_59[0x7];
    grlib::CGLibVtlMemPool m_memPool;  // 0x60, resourceInit sets it up on the file's vertex data (the name is not the original's)
};
}  // namespace ml

#endif
