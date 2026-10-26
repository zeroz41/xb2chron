#include "classes/gf/GfBdatLookAt.h"
#include "gf/MsgUnk_1000004.h"
#include "classes/gf/GfBdatLookAt.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjUtil.h"
#include "gf/MsgUnk_1000004.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/Vector.h"
#include "plugin/Bdat.h"

namespace gf {

// a character category's table: its rows by RefID from the lowest one (FixedArray<gf::CategoryTable, 16> names the
// type; the field names are not the original's)
struct CategoryTable {
    CategoryTable() : m_infos(getAllocator(ALLOCATOR(0))), m_minRefId(0), m_valid(false) {}
    mm::mtl::Vector<GfBdatLookAt::CharactorInfo> m_infos;
    unsigned int m_minRefId;
    bool m_valid;  // the category has a table
};

class GfBdatLookAt::Impl {
public:
    Impl();
    void build();
    // the look parameters of a look type and chara type, none past the tables (the name is not the original's)
    const LookInfo* getLookInfo(unsigned int lookType, unsigned int charaType) const {
        return lookType < 3 && charaType < 5 ? &m_lookInfos[lookType][charaType] : nullptr;
    }

    mm::mtl::FixedArray<CategoryTable, 16> m_categories;
    LookInfo m_lookInfos[3][5];  // by look type and chara type
    float m_maxRadius;
    float m_maxUpper;
    float m_maxLower;
};

// the BDAT table of each character category, -1 for a category with none (Proposed name, not the original's: the
// symbols leave it unnamed (lbl_71009B9A50))
static const unsigned int s_categoryBdatIds[16] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0x1D3, 0x1D4, 0xFFFFFFFF, 0x1D5, 0x1D6, 0x1D7,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
};

#line 80
GfBdatLookAt::GfBdatLookAt() {
    m_impl.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) Impl());
    m_impl->build();
}

#line 90
void GfBdatLookAt::bdatRefresh() {
    m_impl.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) Impl());
    m_impl->build();
    if (GfGameParty::get()) {
        for (unsigned int i = 0; i < 6; ++i) {
            if (GfObj* obj = GfObjUtil::getObj(GfGameParty::getHandleByHierarchy(i))) {
                MsgUnk_1000004 msg;
                sendMessage(obj, msg);
            }
        }
    }
}

const GfBdatLookAt::CharactorInfo* GfBdatLookAt::getCharactorInfo(unsigned int category, unsigned int refId) const {
    static CharactorInfo s_default;
    const CharactorInfo* info = nullptr;
    if (m_impl) {
        const CategoryTable& table = m_impl->m_categories[category];
        if (table.m_valid) {
            int index = refId - table.m_minRefId;
            if (index >= 0 && index < table.m_infos.size()) {
                info = &table.m_infos[index];
            }
        }
    }
    return info == nullptr ? &s_default : info;
}

const GfBdatLookAt::LookInfo* GfBdatLookAt::getLookInfo(unsigned int category, unsigned int refId,
                                                        unsigned int targetCategory, unsigned int targetRefId) const {
    static LookInfo s_default;
    const LookInfo* result = &s_default;
    if (targetCategory != 8) {
        const CharactorInfo* chara = getCharactorInfo(category, refId);
        const CharactorInfo* target = getCharactorInfo(targetCategory, targetRefId);
        const LookInfo* info = nullptr;
        if (m_impl) {
            info = m_impl->getLookInfo(chara->m_lookType, target->m_charaType);
        }
        if (info != nullptr) {
            result = info;
        }
    }
    return result;
}

float GfBdatLookAt::getMaxRadius() {
    if (m_impl) {
        return m_impl->m_maxRadius;
    }
    return 50.0f;
}

float GfBdatLookAt::getMaxUpper() {
    if (m_impl) {
        return m_impl->m_maxUpper;
    }
    return 5.0f;
}

float GfBdatLookAt::getMaxLower() {
    if (m_impl) {
        return m_impl->m_maxLower;
    }
    return 5.0f;
}

unsigned short GfBdatLookAt::getCharaType(unsigned int category, unsigned int refId) {
    if (m_impl) {
        return getCharactorInfo(category, refId)->m_charaType;
    }
    return 0;
}

GfBdatLookAt::Impl::Impl() : m_maxRadius(0.0f), m_maxUpper(0.0f), m_maxLower(0.0f) {}

void GfBdatLookAt::Impl::build() {
    for (unsigned int i = 0; i < 16; ++i) {
        if (s_categoryBdatIds[i] != 0xFFFFFFFF) {
            CategoryTable& table = m_categories[i];
            unsigned char* fp = GfDataBdat::getFP(s_categoryBdatIds[i]);
            unsigned int top = Bdat::getIdTop(fp);
            int count = Bdat::getIdCount(fp);
            unsigned int minRefId = 0xFFFFFFFF;
            unsigned int maxRefId = 0;
            for (unsigned int id = top; id < top + count; ++id) {
                unsigned int refId = static_cast<unsigned short>(
                    reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "RefID", id, 2)));
                minRefId = refId < minRefId ? refId : minRefId;
                maxRefId = refId > maxRefId ? refId : maxRefId;
            }
            table.m_infos.resize(maxRefId + 1 - minRefId);
            table.m_minRefId = minRefId;
            table.m_valid = true;
            for (unsigned int id = top; id < top + count; ++id) {
                unsigned int refId = static_cast<unsigned short>(
                    reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "RefID", id, 2)));
                CharactorInfo& info = table.m_infos[refId - table.m_minRefId];
                info.m_charaType =
                    static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara", id, 2)));
                if (i >= 2 && i <= 3) {
                    info.m_lookType = static_cast<unsigned short>(
                        reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "LookType", id, 2)));
                }
            }
        }
    }
    for (unsigned int bdatId = 0x1D8; bdatId < 0x1DB; ++bdatId) {
        unsigned char* fp = GfDataBdat::getFP(bdatId);
        unsigned int top = Bdat::getIdTop(fp);
        int count = Bdat::getIdCount(fp);
        for (unsigned int id = top; id < top + count; ++id) {
            unsigned short chara =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara", id, 2)));
            LookInfo& info = m_lookInfos[bdatId - 0x1D8][chara];
            union {
                unsigned int bits;
                float value;
            } radius, upper, lower, lookTime, interval;
            radius.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Radius", id, 8)));
            info.m_radius = radius.value;
            upper.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "UpperHeight", id, 8)));
            info.m_upperHeight = upper.value;
            lower.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "LowerHeight", id, 8)));
            info.m_lowerHeight = lower.value;
            lookTime.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "LookTime", id, 8)));
            info.m_lookTime = lookTime.value;
            interval.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Interval", id, 8)));
            info.m_interval = interval.value;
            info.m_priority =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Priority", id, 4)));
            m_maxRadius = m_maxRadius > info.m_radius ? m_maxRadius : info.m_radius;
            m_maxUpper = m_maxUpper > info.m_upperHeight ? m_maxUpper : info.m_upperHeight;
            m_maxLower = m_maxLower > info.m_lowerHeight ? m_maxLower : info.m_lowerHeight;
        }
    }
}

// inline: both deleting thunks of the original inline the whole deleting destructor (an out-of-line one is past
// the inliner's threshold for the thunks)
inline GfBdatLookAt::~GfBdatLookAt() {}

}  // namespace gf
