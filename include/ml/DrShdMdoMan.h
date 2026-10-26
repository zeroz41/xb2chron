#ifndef ML_DRSHDMDOMAN_H
#define ML_DRSHDMDOMAN_H

namespace ml {
class DrCalcStmListObj;
struct MdsMatTechnique;

// A model material's declared shader, in DrShdMdoMan's list. Only the list links are declared so far (the field
// names are not the original's).
class DrShdMdoDecShdObj {
public:
    DrShdMdoDecShdObj(const unsigned char* shdData, const unsigned char* tblData, const MdsMatTechnique* tech);
    ~DrShdMdoDecShdObj();
    void update();

    DrShdMdoDecShdObj* m_pPrev;  // 0x0
    DrShdMdoDecShdObj* m_pNext;  // 0x8
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
    void releaseShaderObj(DrShdMdoDecShdObj* obj);

    DrShdMdoDecShdObj* m_pTop;  // 0x0
    DrShdMdoDecShdObj* m_pEnd;  // 0x8
};
}  // namespace ml

#endif
