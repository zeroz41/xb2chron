#ifndef CLASSES_ML_DRCALCTEXSTREAMMAN_H
#define CLASSES_ML_DRCALCTEXSTREAMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DrCalcTexStreamMan; }
namespace ml { class DrCalcStmListObj; }
namespace ml { class DrCalcTexStmObj; }

namespace ml {
// table 0x7100B7EDA8
class DrCalcTexStreamMan : public ::mm::mtl::PtrSingleton< ::ml::DrCalcTexStreamMan> {
public:
    enum { STOCK_MAX = 0x200 };  // the stock lists' length (the name is not the original's)

    virtual ~DrCalcTexStreamMan();  // slot 0

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

    unsigned char pad_8[0x50];
    DrCalcStmListObj* m_stock[2][STOCK_MAX];  // 0x58: by DrMan::s_nDblStockIdx (the name is not the original's)
    unsigned int m_stockNum[2];                       // 0x2058 (the name is not the original's)
    unsigned char pad_2060[0x430];
    // 0x2490: update zeroes it; the error waits add each list's m_readSize (the name is not the original's)
    int m_errReadSize;
    unsigned char pad_2494[0xC];
    int m_jobGroup;  // 0x24A0: WorkCpu::createGroupHandle's, set by setupMem (the name is not the original's)
};
}  // namespace ml

#endif
