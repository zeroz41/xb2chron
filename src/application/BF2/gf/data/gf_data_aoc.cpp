#include "classes/gf/TUnk_B4C840.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/ml/FileResTh.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include "nn/aoc.h"

namespace gf {

// the add-on indices the singleton's 6 entries stand for (lbl_71009B9B30; the name is not the original's)
static const unsigned char s_aocIndices[6] = {1, 2, 3, 4, 5, 6};
// each add-on's key values, 0-terminated: key.bin's first int is looked up in them (lbl_71009B9B38..lbl_71009B9BC4;
// the names are not the original's)
static const int s_keys1[] = {1503545751, -666488277, 0};
static const int s_keys2[] = {-1074102453, 626530907, 781296066, -109063973, 1891936294, 0};
static const int s_keys3[] = {-2019638389, -575822572, 1444816444, -1003992065, 1124245377, 0};
static const int s_keys4[] = {-1175555372, -1055415262, 0};
static const int s_keys5[] = {-1284728608, 81062730,   825346520,  2060022505, -936017782, -1863310795,
                       -1661520270, -182272903, 1798160555, 2081225074, 48144082,   1585620894,
                       709211687,   -1813024520, 1138667815, -298767597, 0};
static const int s_keys6[] = {1523903846, 0};
// lbl_7100B4C860 (the name is not the original's)
static const int* s_keyTables[6] = {s_keys1, s_keys2, s_keys3, s_keys4, s_keys5, s_keys6};

void TUnk_B4C840::fn_71002226F4() {
    for (int i = 0; i < 6; i++) {
        m_ids[i] = -1;
    }
    int list[16];
    int count = nn::aoc::ListAddOnContent(list, 0, 16);
    list[count] = 0;
    for (int i = 0; i < 6; i++) {
        int found = -1;
        for (int j = 0; list[j] > 0; j++) {
            if (list[j] == s_aocIndices[i]) {
                found = j;
                break;
            }
        }
        if (found < 0) {
            continue;
        }
        mm::mtl::FixStr<16> path;
        path.format("aoc%d:/key.bin", s_aocIndices[i]);
        ml::FileResTh* res = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) ml::FileResTh;
        if (res == nullptr) {
            continue;
        }
        if (res->load(fw::FrameworkMemory::getMem(5), path.m_str, 0, ml::FILE_PRIO(10))) {
            while (res->m_handle != nullptr) {
                GfSleep(1);
            }
            if (res->m_size != -2) {
                m_ids[i] = 0;
                const int* keys = s_keyTables[i];
                for (int j = 0; keys[j] != 0; j++) {
                    if (keys[j] == *static_cast<const int*>(res->m_data)) {
                        m_ids[i] = j;
                        break;
                    }
                }
                res->release();
            }
        }
        res->Release();
    }
    m_ready = true;
}

TUnk_B4C840::~TUnk_B4C840() {}

void TUnk_B4C840::fn_7100222908(const GfSetupParam&) {
#line 43
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_B4C840;
}

void TUnk_B4C840::fn_710022299C() {
    TUnk_B4C840* data = get();
    data->m_ready = false;
    delete data;
}

int TUnk_B4C840::fn_71002229C0(unsigned int index) {
    TUnk_B4C840* data = get();
    if (data == nullptr) {
        return -1;
    }
    return data->m_ids[index];
}

}  // namespace gf
