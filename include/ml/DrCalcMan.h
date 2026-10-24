#ifndef ML_DRCALCMAN_H
#define ML_DRCALCMAN_H

namespace ml {
class DrCalcViewWork;
class DrCalcClipMan;

// The renderer's calculation manager. Only what begin/end use is declared so far (the field names are not the
// original's).
class DrCalcMan {
public:
    void begin();
    void end();

    unsigned char pad_0[0x8];
    int m_viewIdx;  // 0x8: begin passes it to DrCalcViewWork::begin
    DrCalcViewWork* m_pViewWork;  // 0x10
    DrCalcClipMan* m_pClipMan;  // 0x18
};
}  // namespace ml

#endif
