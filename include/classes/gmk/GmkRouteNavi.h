#ifndef CLASSES_GMK_GMKROUTENAVI_H
#define CLASSES_GMK_GMKROUTENAVI_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkRoute.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace gmk {
class GmkRoute;
// Moves along a route's points (GmkRoutedNpc keeps one on the heap at 0x70; GmkRoutedEnemy/GmkRoutedMob keep a
// Vector<std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>>). No table. 0xb0 bytes: GmkRoutedNpc::create allocates 0xb0;
// 16-aligned (the pair's GmkRouteNavi sits at 0x10, stride 0xc0) by its Vec3 at 0x90.
// Field names are not the original's.
class GmkRouteNavi {
public:
    // where init puts the mover: the position and direction on the route at the chosen point (the class and
    // field names are not the original's)
    class InitResult {
    public:
        // inline: StateFieldWalk::seqWaitTakeOffEnd stores these before init (position zero, direction +z)
        InitResult() : m_pos(0.0f, 0.0f, 0.0f), m_dir(0.0f, 0.0f, 1.0f) {}
        mm::Vec3 m_pos;  // 0x0
        mm::Vec3 m_dir;  // 0x10
    };
    // what update takes: the mover's position as three floats, zero by default (12 bytes: the field states copy the
    // three components; the field's name is not the original's)
    class UpdateInfo {
    public:
        UpdateInfo() { m_pos.x = 0.0f; m_pos.y = 0.0f; m_pos.z = 0.0f; }
        mm::Vec3NA m_pos;
    };
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
        unsigned int pad_18;       // 0x10; isValid wants it non-zero (init scales it by a float: unsigned)
        InitResult* m_initResult;  // 0x20: create calls initAtRandom(*m_initResult) when set
    };

    GmkRouteNavi(const CreateInfo* info = nullptr);  // the default: Vector<pair<GF_OBJ_HANDLE*, GmkRouteNavi>>::resize
    ~GmkRouteNavi() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    bool initAtRandom(InitResult& result);
    void seqInit(const UpdateInfo& info);
    bool init(InitResult& result, unsigned int index, float offset);
    bool getPosDirOnCurve(mm::Vec3& pos, mm::Vec3& dir, unsigned int index, float t) const;
    bool getPosDirOnLine(mm::Vec3& pos, mm::Vec3& dir, unsigned int index, float t) const;
    void update(const UpdateInfo& info);
    void updateNextPos();
    bool isArrived(const mm::Vec3& pos, const mm::Vec3& target) const;
    void updateNextPointIndx();
    void seqUpdateOnCurve(const UpdateInfo& info);
    void seqUpdateOnLine(const UpdateInfo& info);
    // inline (no symbol; the names are not the original's): its info names a route kind and the route it reached
    // is valid
    bool isValid() const { return m_info.isValid() && m_acc.isValid(); }
    const GmkRoute* getRoute() const { return static_cast<const GmkRoute*>(m_acc.m_gmk); }
    // the sideways offset of its points (along each point's pad_10) by the route's offset mode (inline; the name is
    // not the original's)
    float getPointOffset() const {
        float offset = 0.0f;
        const GmkRoute* route = getRoute();
        if (route != nullptr) {
            switch (route->getData()->m_offsetMode) {
            case 0:
                offset = m_info.m_offset;
                break;
            case 1:
                offset = m_info.m_offset > 0.0f ? m_info.m_offset : -m_info.m_offset;
                if (pad_a4) {
                    offset = -offset;
                }
                break;
            case 2:
                offset = m_info.m_offset > 0.0f ? -m_info.m_offset : m_info.m_offset;
                if (pad_a4) {
                    offset = -offset;
                }
                break;
            }
        }
        return offset;
    }
    // a point index brought back onto the route: a closed route goes round, an open one turns back at its ends
    // (reverse: going backwards; inline, the name is not the original's)
    int wrapPointIndx(int indx, bool& reverse) const {
        const GmkRoute* route = getRoute();
        bool closed = route->isClosed();
        int num = route->getRoutePointNum();
        if (indx < 0) {
            indx %= num;
            if (closed) {
                indx += num;
            } else {
                indx = -indx;
                reverse = (indx / num) & 1;
            }
        }
        if (num <= indx) {
            if (closed) {
                indx %= num;
            } else {
                indx = num - 2;
                reverse = !((indx / num) & 1);
            }
        }
        return indx;
    }

    CreateInfo m_info;  // 0x0
    GmkAcc m_acc;       // 0x28: the route it follows (create fills it from m_info)
    float pad_68;       // 0x68: create copies m_info.pad_10
    float pad_6c;       // 0x6c: create copies m_info.pad_14
    void (GmkRouteNavi::*m_seq)(const UpdateInfo&);  // 0x70: create sets seqInit
    bool pad_80;
    mm::Vec3 pad_90;
    int pad_a0;            // create stores 1
    bool pad_a4;
    unsigned int pad_a8;  // init: pad_18 scaled by its offset, plus 1
    int pad_ac;
};
}  // namespace gmk

#endif
