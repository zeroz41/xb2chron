#include "classes/ml/DevFileTh.h"
#include "classes/mm/mtl/IAllocator.h"
#include "csvb/CsvbData.h"
#include "ml/DevFileParamTh.h"
#include "ml/MlMem.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"

// csvb_utility.cpp's functions sit at the start of this unit's range.
// Not written yet: GetCsvbInfo, both CreateCsvbData, and ssd::Delegate::MultiCast's
// Clear, AddDelegate, RemoveDelegate, FindDelegate, ExecuteDelegateImpl and Array<Handle*>::SetArraySize.
namespace csvb {

bool CCsvbUtility::LoadFile(const char* path, void** ppData, unsigned int* pSize) {
    mm::mtl::FixStr<256> name;
    ml::DevFileTh::normalizeDvdFileName(name, path);
    int size = 0;
    ml::DevFileParamTh param;
    param.m_hMem = ml::MlMem::getProductMem();
    param.m_path = name.m_str;
    param.pad_58 = 0;
    *ppData = ml::DevFileTh::readFileBlock(param, &size, nullptr);
    *pSize = size;
    return true;
}

int CCsvbUtility::GetCsvbFormat(const void* pData) {
    // the file's first word, its bytes in memory order
    unsigned int magic = *static_cast<const unsigned int*>(pData);
    unsigned char c0 = magic & 0xFF;
    unsigned char c1 = (magic >> 8) & 0xFF;
    unsigned char c2 = (magic >> 16) & 0xFF;
    unsigned char c3 = magic >> 24;
    if (c0 == 'C' && c1 == 'S' && c2 == 'V' && c3 == 'B') {
        return 0;
    }
    if (c0 == 'B' && c1 == 'V' && c2 == 'S' && c3 == 'C') {
        return 1;
    }
    return 2;
}

stCsvbRow* CCsvbUtility::CreateCsvbRows(mtl::ALLOC_HANDLE handle, const stCsvbRowInfo* pRowInfo, unsigned short count,
                                        bool swap) {
    if (count == 0) {
        return nullptr;
    }
    stCsvbRow* rows = static_cast<stCsvbRow*>(mtl::MemManager::allocate(handle, count * sizeof(stCsvbRow), 4, false, "no name", 0));
    unsigned short index = 0;
    for (unsigned int i = 0; i < count; i++) {
        rows[i].columnCount = pRowInfo[i].columnCount;
        rows[i].dataIndex = index;
        if (swap) {
            EndianSwap2(&rows[i].columnCount);
        }
        index += rows[i].columnCount;
    }
    return rows;
}

stCsvbRow* CCsvbUtility::CreateCsvbRows(mm::mtl::IAllocator* allocator, const stCsvbRowInfo* pRowInfo,
                                        unsigned short count, bool swap) {
    if (count == 0) {
        return nullptr;
    }
    stCsvbRow* rows = static_cast<stCsvbRow*>(allocator->allocate(count * sizeof(stCsvbRow), 8));
    unsigned short index = 0;
    for (unsigned int i = 0; i < count; i++) {
        rows[i].columnCount = pRowInfo[i].columnCount;
        rows[i].dataIndex = index;
        if (swap) {
            EndianSwap2(&rows[i].columnCount);
        }
        index += rows[i].columnCount;
    }
    return rows;
}

}  // namespace csvb
