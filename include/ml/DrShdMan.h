#ifndef ML_DRSHDMAN_H
#define ML_DRSHDMAN_H

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdLgtMan;

// The renderer's shader manager (DrMan::m_shdMan). Only what DrMdoSetup reads is declared; the constructor
// (ml/DrShdDataList unit) stores the members below. Field names are not the original's.
class DrShdMan {
public:
    DrShdMan(DrMan* drMan);
    ~DrShdMan();

    DrShdDataList* m_dataList;  // 0x0, the constructor news a DrShdDataList
    unsigned char pad_8[0x10];
    DrShdLgtMan* m_lgtMan;      // 0x18, the constructor news a DrShdLgtMan
    DrMan* m_pDrMan;            // 0x20
};
}  // namespace ml

#endif
