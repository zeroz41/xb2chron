#ifndef ML_DRSHDMDOMAN_H
#define ML_DRSHDMDOMAN_H

#include "classes/grlib/CGLibShdListBase.h"
#include "ml/DrShdMdoDecExtTbl.h"

namespace ml {
class DrCalcStmListObj;
struct MdsMatTechnique;

// A model material's declared shaders, in DrShdMdoMan's list (the field names are not the original's).
class DrShdMdoDecShdObj {
public:
    DrShdMdoDecShdObj(const unsigned char* shdData, const unsigned char* tblData, const MdsMatTechnique* tech);
    ~DrShdMdoDecShdObj();
    void update();
    void changeMemShader(const unsigned char* shdData, const unsigned char* tblData, const MdsMatTechnique* tech);

    DrShdMdoDecShdObj* m_pPrev;  // 0x0
    DrShdMdoDecShdObj* m_pNext;  // 0x8
    // 0x10, the shader package the list is built from; DrShdMdoMan::createShaderObj finds an object by it (the
    // stream overload compares it with the stream object)
    const void* m_pShdData;
    int m_refCount;  // 0x18, DrShdMdoMan::releaseShaderObj deletes the object at 0
    DrCalcStmListObj* m_pStmObj;  // 0x20, the stream whose shader resource update moves the programs to
    grlib::CGLibShdListBase<DrShdMdoDecRes> m_shdList;  // 0x28
};

// DrShdMan's list of model shaders (0x10 bytes). 1.0.0 has its constructor, destructor and update out of line;
// 3.0.1 inlines them. The field names are not the original's.
class DrShdMdoMan {
public:
    DrShdMdoMan() : m_pTop(nullptr), m_pEnd(nullptr) {}
    ~DrShdMdoMan() {
        DrShdMdoDecShdObj* obj = m_pTop;
        while (obj != nullptr) {
            DrShdMdoDecShdObj* next = obj->m_pNext;
            delete obj;
            obj = next;
        }
    }
    void update() {
        for (DrShdMdoDecShdObj* obj = m_pTop; obj != nullptr; obj = obj->m_pNext) {
            obj->update();
        }
    }
    // the object of the shader package (a new one, or the listed one with another reference)
    DrShdMdoDecShdObj* createShaderObj(const unsigned char* shdData, const unsigned char* tblData, const MdsMatTechnique* tech);
    DrShdMdoDecShdObj* createShaderObj(DrCalcStmListObj* stmObj, const unsigned char* tblData, const MdsMatTechnique* tech);
    void releaseShaderObj(DrShdMdoDecShdObj* obj);
    // appends obj to the list (inline; the name is not the original's)
    void append(DrShdMdoDecShdObj* obj) {
        if (m_pEnd == nullptr) {
            m_pTop = obj;
            m_pEnd = obj;
            obj->m_pPrev = nullptr;
        } else {
            m_pEnd->m_pNext = obj;
            obj->m_pPrev = m_pEnd;
            m_pEnd = obj;
        }
        obj->m_pNext = nullptr;
    }

    DrShdMdoDecShdObj* m_pTop;  // 0x0
    DrShdMdoDecShdObj* m_pEnd;  // 0x8
};
}  // namespace ml

#endif
