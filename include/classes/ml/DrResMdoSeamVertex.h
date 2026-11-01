#ifndef CLASSES_ML_DRRESMDOSEAMVERTEX_H
#define CLASSES_ML_DRRESMDOSEAMVERTEX_H

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoVertex;

// table 0x7100B7DAD0
// A streamed seam vertex set: a DrResMdoVertex built on a DrResMdoSeamMemObj block. The field and parameter names are
// not the original's.
class DrResMdoSeamVertex {
public:
    DrResMdoSeamVertex(int no);
    virtual ~DrResMdoSeamVertex();  // slot 0
    void release();
    bool update();
    void createVertex();
    void changeMemVertex();

    static int SEAMRES_CNTMAX;

    DrResMdoSeamVertex* m_prev;    // 0x08: list links, zeroed by the constructor
    DrResMdoSeamVertex* m_next;    // 0x10
    DrResMdoSeamMemObj* m_memObj;  // 0x18: the vertex data
    DrResMdoVertex* m_vertex;      // 0x20: built by createVertex
    short m_no;                    // 0x28: the constructor's argument
    short m_cnt;                   // 0x2A: frames since created, against SEAMRES_CNTMAX
    unsigned short m_dataIdx;      // 0x2C: its entry in the seam map's vertex table; zeroed by the constructor
    short m_readIn;                // 0x2E: set by update when the memory block is read in
};
}  // namespace ml

#endif
