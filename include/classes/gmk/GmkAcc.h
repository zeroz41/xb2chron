#ifndef CLASSES_GMK_GMKACC_H
#define CLASSES_GMK_GMKACC_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk {
// table 0x7100B51A38
// 0x40 bytes: gf::LocatorTbox holds one at 0x18 and its byte at 0x58 follows; LocatorBat_EnemyID keeps
// mm::mtl::FixedVector<GmkAcc, 16>s with 0x40-byte elements
// a node of GmkAccManager's lists at 0x8 (its constructors link it to itself)
class GmkAcc : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // which gimmick to reach: the locators' update() build one with these values, fill it with validate() and
    // create the access when it names one (a row above 0, a kind other than 0x40)
    class CreateInfo {
    public:
        CreateInfo() : m_bdatId(-1), m_type(GmkType(0x40)), pad_8(0), pad_c(1) {}  // pad_c: a byte the original stores 1 to
        void validate(const AGmkBase& gmk);
        // the name is not the original's
        bool isValid() const {
            return m_bdatId > 0 && m_type != GmkType(0x40);
        }

        int m_bdatId;    // the name is not the original's
        GmkType m_type;  // the name is not the original's
        unsigned int pad_8;
        unsigned char pad_c;
    };
    // a gimmick named by its type and BDAT row (GfAutoTalk::create reaches its MOBID's mob so: type 0x12; the
    // names are not the original's)
    struct CreateInfoByBdatId {
        // GmkAcc's constructors store these (the default: none)
        CreateInfoByBdatId() : m_type(GmkType(0x40)), m_bdatId(-1), m_flag(true) {}
        // the name is not the original's (the copy constructor's test before create)
        bool isValid() const {
            return m_type != GmkType(0x40) && m_bdatId > 0;
        }
        GmkType m_type;
        int m_bdatId;
        bool m_flag;  // GfAutoTalk::create passes true
    };
    GmkAcc();
    GmkAcc(const CreateInfo& info);
    GmkAcc(const GmkAcc& other);
    // inline: the locators' destructors (gf_field_locator) store this table and call dispose() in place; the
    // out-of-line copies gf_field_gimmick holds are the weak ones its table needs
    virtual ~GmkAcc() {  // slot 0
        dispose();
    }
    void dispose();
    bool isValid() const;
    // finds the gimmick (create calls it when the info's byte at 0xc is set)
    void update();
    void create(const CreateInfo& info);
    void create(const CreateInfoByBdatId& info);

    CreateInfo m_info;  // 0x18: what the locators test before creating it again; the name is not the original's
    CreateInfoByBdatId m_infoByBdatId;  // 0x28: the copy constructor creates from it (the name is not the original's)
    AGmkBase* m_gmk;  // the gimmick reached (the locators read its position); the name is not the original's
};
}  // namespace gmk

#endif
