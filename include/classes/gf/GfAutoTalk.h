#ifndef CLASSES_GF_GFAUTOTALK_H
#define CLASSES_GF_GFAUTOTALK_H

#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/DistHvCond.h"

class CBdatWrapper;
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B537F8: one row of a gimmick set's autoTalk table, a balloon a mob shows when the party comes near
// (0x88 bytes: GfAutoTalkList keeps a mm::mtl::Vector of them). The members are 1.0.0's.
class GfAutoTalk {
public:
    // which row of which table (GfAutoTalkList::create passes its tables and each row id)
    struct CreateInfo {
        CreateInfo() : m_fp(nullptr), m_fpMs(nullptr), m_id(-1) {}
        unsigned char* m_fp;    // the autoTalk table (the names are not the original's)
        unsigned char* m_fpMs;  // its texts (autoTalk_ms)
        int m_id;               // the row
    };
    // the row's columns (12 bytes); create follows BeforeID to the first row of the chain for Range and Condition
    struct BdatInfo {
        BdatInfo() : m_mobId(0), m_range(0), m_condition(0), m_text(0), m_ontime(0), m_beforeId(0) {}
        void create(const CBdatWrapper& bdat, int id);
        void dispose() { m_mobId = 0; }

        unsigned short m_mobId;  // the names are the columns'
        unsigned short m_range;
        unsigned short m_condition;
        unsigned short m_text;
        unsigned short m_ontime;
        unsigned short m_beforeId;
    };

    GfAutoTalk(const CreateInfo* info = nullptr)
        : m_info(), m_bdatInfo(), m_dist(), m_context(nullptr), m_disp(false),
          m_dispTime(0.0f) {
        if (info != nullptr) {
            create(*info);
        }
    }
    virtual ~GfAutoTalk();  // slot 0
    void create(const CreateInfo& info);
    bool isValid() const {
        return m_info.m_fp != nullptr && m_info.m_fpMs != nullptr && m_info.m_id > 0 && m_gmkAcc.isValid();
    }
    bool isDispEnd() const {
        return m_disp && !(m_dispTime > 0.0f);
    }
    void dispose() {
        disposeMenuObj();
        m_dispTime = 0.0f;
        m_disp = false;
        m_gmkAcc.dispose();
        m_bdatInfo.dispose();
        m_info = CreateInfo();
    }
    void disposeMenuObj();
    void update(float dt);
    void updateMenuObj();
    bool canDispText() const;
    void createMenuObj();

    CreateInfo m_info;
    BdatInfo m_bdatInfo;   // 0x20
    // 0x2c: Range squared on both axes (canDispText calls gmk::DistHvCond::isMatch on it with the mob's position;
    // the name is not the original's)
    gmk::DistHvCond m_dist;
    unsigned char pad_34[0x4];
    gmk::GmkAcc m_gmkAcc;  // 0x38: the MOBID's mob
    GfMenuCallContext* m_context;  // 0x78: the balloon's call context (the name is not the original's)
    bool m_disp;           // 0x80: shown (the names are not the original's)
    float m_dispTime;      // 0x84: how long it stays, from Ontime
};
}  // namespace gf

#endif
