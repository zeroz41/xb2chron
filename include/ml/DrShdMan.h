#ifndef ML_DRSHDMAN_H
#define ML_DRSHDMAN_H

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdFetchMan;
class DrShdLgtMan;
class DrShdMdoMan;

// The renderer's shader manager (DrMan::m_shdMan): its constructor news the members below. Field names are not
// the original's.
class DrShdMan {
public:
    DrShdMan(DrMan* drMan);
    ~DrShdMan();
    void beginUpdate();
    void setupCate(int cateIdx);
    void beforeUpdateCate(int cateIdx);
    void updateCate(int cateIdx);
    void addViewInfo(int viewIdx);
    void delViewInfo(int viewIdx);
    void resetColorBuff(int viewIdx);

    DrShdDataList* m_dataList;  // 0x0
    DrShdMdoMan* m_mdoMan;      // 0x8
    DrShdFetchMan* m_fetchMan;  // 0x10
    DrShdLgtMan* m_lgtMan;      // 0x18
    DrMan* m_pDrMan;            // 0x20
};
}  // namespace ml

#endif
