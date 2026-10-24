#ifndef ML_DRSHDLGTMAN_H
#define ML_DRSHDLGTMAN_H

namespace ml {
class DrShdLgtHybrid;
class DrShdLgtGlobalIBL;
class DrShdLgtClustered;

// The light shader manager. Only what stockBegin/stockEnd use is declared so far; the constructor creates the
// three light renderers below (the field names are not the original's).
class DrShdLgtMan {
public:
    void stockBegin();
    void stockEnd();

    unsigned char pad_0[0x50];
    DrShdLgtHybrid* m_pHybrid;  // 0x50
    DrShdLgtGlobalIBL* m_pGlobalIBL;  // 0x58
    DrShdLgtClustered* m_pClustered;  // 0x60
};
}  // namespace ml

#endif
