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

void GfGameFlag::setLocal(GameFlag& flag, unsigned int type, int index, unsigned int value) {
    switch (type) {
    case 1:
        // the original reads the flag first: only that read's assertion is left
        flag.m_flag1[index];
        flag.m_flag1.change(index, value != 0);
        break;
    case 2: {
        unsigned int bit = index * 2;
        unsigned int word = bit >> 5;
        unsigned int shift = bit & 31;
        flag.m_flag2[word] &= ~(3 << shift);
        flag.m_flag2[word] |= value << shift;
        break;
    }
    case 4: {
        unsigned int bit = index * 4;
        unsigned int word = bit >> 5;
        unsigned int shift = bit & 31;
        flag.m_flag4[word] &= ~(15 << shift);
        flag.m_flag4[word] |= value << shift;
        break;
    }
    case 8:
        flag.m_flag8[index] = value;
        break;
    case 16:
        flag.m_flag16[index] = value;
        break;
    case 32:
        flag.m_flag32[index] = value;
        break;
    }
}

void GfGameFlag::clear() {
    memset(&GfDataManager::getDataGame()->m_gameFlag, 0, sizeof(GameFlag));
}

}  // namespace gf
