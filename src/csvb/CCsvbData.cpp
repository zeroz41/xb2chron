#include "mtl/MemManager.h"
#include "csvb/CsvbData.h"

#include "classes/mm/mtl/IAllocator.h"
#include "string.h"

namespace csvb {

CCsvbData::CCsvbData()
    : m_rowCount(0), m_pRows(nullptr), m_dataCount(0), m_pData(nullptr), m_stringSize(0), m_pStrings(nullptr),
      m_pAllocator(nullptr) {}

CCsvbData::~CCsvbData() {
    Clear();
}

// the rows, the cells and the strings back to where they came from
void CCsvbData::Clear() {
    if (m_pRows != nullptr) {
        if (m_pAllocator != nullptr) {
            m_pAllocator->deallocate(m_pRows);
        } else {
            mtl::MemManager::deallocate(m_pRows, 0, false);
        }
        m_pRows = nullptr;
    }
    m_rowCount = 0;
    if (m_pData != nullptr) {
        if (m_pAllocator != nullptr) {
            m_pAllocator->deallocate(m_pData);
        } else {
            mtl::MemManager::deallocate(m_pData, 0, false);
        }
        m_pData = nullptr;
    }
    m_dataCount = 0;
    if (m_pStrings != nullptr) {
        if (m_pAllocator != nullptr) {
            m_pAllocator->deallocate(m_pStrings);
        } else {
            mtl::MemManager::deallocate(m_pStrings, 0, false);
        }
        m_pStrings = nullptr;
    }
    m_stringSize = 0;
    m_pAllocator = nullptr;
}

bool CCsvbData::Load(mtl::ALLOC_HANDLE handle, const char* path) {
    unsigned int size = 0;
    void* pData = nullptr;
    bool result = false;
    if (CCsvbUtility::LoadFile(path, &pData, &size)) {
        result = Load(handle, pData, size);
        mtl::MemManager::deallocate(pData, 0, false);
    }
    return result;
}

bool CCsvbData::Load(mtl::ALLOC_HANDLE handle, const void* pData, unsigned int size) {
    Clear();
    if (CCsvbUtility::GetCsvbFormat(pData) != 0) {
        return false;
    }
    stCsvbInfo info = {};
    if (!CCsvbUtility::GetCsvbInfo(info, pData, size, false)) {
        return false;
    }
    m_rowCount = info.rowCount;
    if (m_rowCount != 0) {
        m_pRows = CCsvbUtility::CreateCsvbRows(handle, info.pRowInfo, info.rowCount, false);
    }
    m_dataCount = info.dataCount;
    if (m_dataCount != 0) {
        m_stringSize = info.stringSize;
        if (m_stringSize != 0) {
            m_pStrings = static_cast<char*>(mtl::MemManager::allocate(handle, m_stringSize, 4, false, "no name", 0));
            memcpy(m_pStrings, info.pStrings, m_stringSize);
        }
        m_pData = CCsvbUtility::CreateCsvbData(handle, info.pDataInfo, m_dataCount, info.pValues, m_pStrings, false);
    }
    return true;
}

bool CCsvbData::Load(mm::mtl::IAllocator* allocator, const char* path) {
    unsigned int size = 0;
    void* pData = nullptr;
    bool result = false;
    if (CCsvbUtility::LoadFile(path, &pData, &size)) {
        result = Load(allocator, pData, size);
        mtl::MemManager::deallocate(pData, 0, false);
    }
    return result;
}

bool CCsvbData::Load(mm::mtl::IAllocator* allocator, const void* pData, unsigned int size) {
    Clear();
    if (CCsvbUtility::GetCsvbFormat(pData) != 0) {
        return false;
    }
    stCsvbInfo info = {};
    if (!CCsvbUtility::GetCsvbInfo(info, pData, size, false)) {
        return false;
    }
    m_pAllocator = allocator;
    m_rowCount = info.rowCount;
    if (m_rowCount != 0) {
        m_pRows = CCsvbUtility::CreateCsvbRows(allocator, info.pRowInfo, info.rowCount, false);
    }
    m_dataCount = info.dataCount;
    if (m_dataCount != 0) {
        m_stringSize = info.stringSize;
        if (m_stringSize != 0) {
            m_pStrings = static_cast<char*>(allocator->allocate(m_stringSize, 8));
            memcpy(m_pStrings, info.pStrings, m_stringSize);
        }
        m_pData = CCsvbUtility::CreateCsvbData(allocator, info.pDataInfo, m_dataCount, info.pValues, m_pStrings, false);
    }
    return true;
}

unsigned short CCsvbData::GetRowCount() const {
    return m_rowCount;
}

unsigned short CCsvbData::GetColumCount(unsigned short row) const {
    return m_pRows[row].columnCount;
}

// the cell's value as an int: a float one truncated, 0 for a string
int CCsvbData::GetInt(unsigned short row, unsigned short column) const {
    const stCsvbData& data = m_pData[m_pRows[row].dataIndex + column];
    switch (data.type) {
    case CSVB_TYPE_INT:
        return data.intValue;
    case CSVB_TYPE_FLOAT:
        return static_cast<int>(data.floatValue);
    default:
        return 0;
    }
}

// the cell's value as a float: an int one converted, 0 for a string
float CCsvbData::GetFloat(unsigned short row, unsigned short column) const {
    const stCsvbData& data = m_pData[m_pRows[row].dataIndex + column];
    switch (data.type) {
    case CSVB_TYPE_FLOAT:
        return data.floatValue;
    case CSVB_TYPE_INT:
        return static_cast<float>(data.intValue);
    default:
        return 0.0f;
    }
}

// the cell's string; null for another type
const char* CCsvbData::GetString(unsigned short row, unsigned short column) const {
    const stCsvbData& data = m_pData[m_pRows[row].dataIndex + column];
    if (data.type == CSVB_TYPE_STRING) {
        return data.stringValue;
    }
    return nullptr;
}

}  // namespace csvb
