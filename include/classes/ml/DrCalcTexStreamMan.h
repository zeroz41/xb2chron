#ifndef CLASSES_ML_DRCALCTEXSTREAMMAN_H
#define CLASSES_ML_DRCALCTEXSTREAMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "classes/ml/DrCalcTexStmObj.h"

namespace ml { class DrCalcTexStreamMan; }
namespace ml { class DrCalcStmListObj; }
namespace ml { class CriticalSection; }

namespace ml {
// table 0x7100B7EDA8
class DrCalcTexStreamMan : public ::mm::mtl::PtrSingleton< ::ml::DrCalcTexStreamMan> {
public:
    enum { STOCK_MAX = 0x200 };  // the stock lists' length (the name is not the original's)

    DrCalcTexStreamMan();
    virtual ~DrCalcTexStreamMan();  // slot 0

    // the lock of the stream lists (1.0.0 has it out of line; 3.0.1 inlines it everywhere)
    static CriticalSection& getCriticalSection();
    // num memory objects (the first one covering all of the size bytes allocated) and the job thread
    // (the parameter names are not the original's)
    void setupMem(int num, unsigned int size, unsigned int);

    // the stream list of the named texture stream (DrStmReadCheck's constructor; the parameter name is not the
    // original's)
    DrCalcStmListObj* createTexStmListObj(const char* name);
    void release();
    // the job thread's function (setupMem hands it and the manager to WorkCpu::entryJobThread)
    static unsigned int jobUpdate(void* man, void* arg);
    void update();
    // the job group's threads started and waited for
    void entryJob();
    void jobWait();
    // the stream lists stocked this frame (s_nDblStockIdx's) run their API updates, the stock emptied
    void apiUpdate();
    void clearMemObj(DrCalcTexStmObj* obj);
    // while bit 0 of pad_2068 is set: the m_memCache entries not in use (bit 1 of their flags) given back
    void cntMemUpdate();

    // (the list names are not the original's) 0x8: the memory objects covering m_mem; 0x18: the spare ones
    DrResChankList<DrCalcTexStmObj> m_memList;
    DrResChankList<DrCalcTexStmObj> m_spareList;
    // 0x28: lists of stream lists (update walks the first; the name is not the original's)
    DrResChankList<DrCalcStmListObj> m_stmLists[3];
    DrCalcStmListObj* m_stock[2][STOCK_MAX];  // 0x58: by DrMan::s_nDblStockIdx (the name is not the original's)
    unsigned int m_stockNum[2];                       // 0x2058 (the name is not the original's)
    unsigned int m_memSize;   // 0x2060: setupMem's size (the name is not the original's)
    unsigned int pad_2064;    // 0x2064: setupMem's third argument
    unsigned int pad_2068;    // 0x2068: flags (update tests bit 1, cntMemUpdate bit 0)
    int pad_206C;             // 0x206C: zeroed by setupMem and release
    unsigned int m_memObjNum;  // 0x2070: setupMem's num (the name is not the original's)
    DrCalcTexStmObj* m_memObjs;  // 0x2078: the m_memObjNum memory objects (the name is not the original's)
    void* m_mem;              // 0x2080: the memory the objects share (the name is not the original's)
    DrCalcTexStmObj* m_memCache[0x40];  // 0x2088: zeroed by setupMem (the name is not the original's)
    unsigned char pad_2288[0x200];
    int pad_2488;             // 0x2488: zeroed by setupMem, counted up by cntMemUpdate
    int pad_248C;             // 0x248C: zeroed by setupMem, the m_memCache entries cntMemUpdate tests
    // 0x2490: update zeroes it; the error waits add each list's m_readSize (the name is not the original's)
    int m_errReadSize;
    short pad_2494;           // 0x2494: zeroed by the constructor
    unsigned char pad_2496[0x2];
    int pad_2498;             // 0x2498: 3 from the constructor; the stream states lower it
    int pad_249C;             // 0x249C: 3 from the constructor; update copies 0x2498 here
    int m_jobGroup;  // 0x24A0: WorkCpu::createGroupHandle's, set by setupMem (the name is not the original's)
};
}  // namespace ml

#endif
