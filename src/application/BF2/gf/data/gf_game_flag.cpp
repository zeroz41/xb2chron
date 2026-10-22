#include <string.h>
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/SDataGame.h"

namespace gf {

GfGameFlag::~GfGameFlag() {}

void GfGameFlag::build(const GfSetupParam& param) {
#line 58
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameFlag(param);
}

void GfGameFlag::destroy() {
    GfGameFlag* flag = get();
    flag->finalize();
    delete flag;
}

unsigned int GfGameFlag::getLocal(const GameFlag& flag, unsigned int type, int index) {
    switch (type) {
    case 1:
        return flag.m_flag1[index];
    case 2: {
        unsigned int bit = index * 2;
        unsigned int word = bit >> 5;
        unsigned int shift = bit & 31;
        return (flag.m_flag2[word] & (3 << shift)) >> shift;
    }
    case 4: {
        unsigned int bit = index * 4;
        unsigned int word = bit >> 5;
        unsigned int shift = bit & 31;
        return (flag.m_flag4[word] & (15 << shift)) >> shift;
    }
    case 8:
        return flag.m_flag8[index];
    case 16:
        return flag.m_flag16[index];
    case 32:
        return flag.m_flag32[index];
    }
    return 0;
}

void GfGameFlag::clear() {
    memset(&GfDataManager::getDataGame()->m_gameFlag, 0, sizeof(GameFlag));
}

}  // namespace gf
