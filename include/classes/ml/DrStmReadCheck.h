#ifndef CLASSES_ML_DRSTMREADCHECK_H
#define CLASSES_ML_DRSTMREADCHECK_H

namespace ml { class DrCalcStmListObj; }

namespace ml {
// table 0x7100B7D728
// a reader of a named texture stream: DrMdlMan::createStmLoadObj makes it and links it into its list (m_prev,
// m_next). The field and flag names are not the original's.
class DrStmReadCheck {
public:
    DrStmReadCheck(const char* name);
    virtual ~DrStmReadCheck();  // slot 0
    virtual void release();  // slot 2
    virtual bool update();  // slot 3: true once release() reached this buffer
    virtual void* getAdder();  // slot 4: calls the list's getAdder and returns null

    enum {
        FLAG_RELEASE = 1 << 0,  // release(), shifted by DrMan::s_nDblStockIdx
        FLAG_READY = 1 << 2,    // update leaves the use mode alone; getAdder asks the list
    };

    DrStmReadCheck* m_prev;      // 0x8
    DrStmReadCheck* m_next;      // 0x10
    int m_mode;                  // 0x18, 1 and 2 pass on as the list's use mode, others as 0
    unsigned int m_flags;        // 0x1C
    DrCalcStmListObj* m_list;    // 0x20, DrCalcTexStreamMan::createTexStmListObj's
};
}  // namespace ml

#endif
