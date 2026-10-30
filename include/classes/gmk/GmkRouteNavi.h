#ifndef CLASSES_GMK_GMKROUTENAVI_H
#define CLASSES_GMK_GMKROUTENAVI_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "mm/Vec3.h"

namespace gmk {
class GmkRoute;
// Moves along a route's points (GmkRoutedNpc keeps one on the heap at 0x70; GmkRoutedEnemy/GmkRoutedMob keep a
// Vector<std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>>). No table. 0xb0 bytes: GmkRoutedNpc::create allocates 0xb0;
// 16-aligned (the pair's GmkRouteNavi sits at 0x10, stride 0xc0) by its Vec3 at 0x90.
// Field names are not the original's.
class GmkRouteNavi {
public:
    class InitResult;
    class UpdateInfo;
    // 0x28 bytes: create copies it whole (memcpy 0x28) into m_info
    class CreateInfo {
    public:
        // dispose and create reset m_info to these defaults; with a route, fills its row, kind and index
        CreateInfo(const GmkRoute* route = nullptr);
        bool isValid() const;

        int m_bdatId;              // 0x0: the route's BDAT row (-1: none)
        GmkType m_type;            // 0x4: the route's kind (0x40: none)
        unsigned int m_routeIndx;  // 0x8: the route's index in its list
        float m_offset;            // 0xC: GmkRoutedNpc::create passes mtRandf1(-1, 1)
        float pad_10;              // 1.0f
        float pad_14;              // 2.0f
        int pad_18;                // 0x10; isValid wants it non-zero
        InitResult* m_initResult;  // 0x20: create calls initAtRandom(*m_initResult) when set
    };

    GmkRouteNavi(const CreateInfo* info);
    ~GmkRouteNavi() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void initAtRandom(InitResult& result);
    void seqInit(const UpdateInfo& info);
    void init(InitResult& result, unsigned int index, float offset);
    void getPosDirOnCurve(mm::Vec3& pos, mm::Vec3& dir, unsigned int index, float t) const;
    void getPosDirOnLine(mm::Vec3& pos, mm::Vec3& dir, unsigned int index, float t) const;
    void update(const UpdateInfo& info);
    void updateNextPos();
    bool isArrived(const mm::Vec3& pos, const mm::Vec3& target) const;
    void updateNextPointIndx();
    void seqUpdateOnCurve(const UpdateInfo& info);
    void seqUpdateOnLine(const UpdateInfo& info);

    CreateInfo m_info;  // 0x0
    GmkAcc m_acc;       // 0x28: the route it follows (create fills it from m_info)
    float pad_68;       // 0x68: create copies m_info.pad_10
    float pad_6c;       // 0x6c: create copies m_info.pad_14
    void (GmkRouteNavi::*m_seq)(const UpdateInfo&);  // 0x70: create sets seqInit
    bool pad_80;
    mm::Vec3 pad_90;
    int pad_a0;            // create stores 1
    bool pad_a4;
    int pad_a8;
    int pad_ac;
};
}  // namespace gmk

#endif
