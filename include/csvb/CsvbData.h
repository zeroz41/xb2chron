#ifndef CSVB_CSVBDATA_H
#define CSVB_CSVBDATA_H

#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; }}

// a csvb file's rows and cells as stored (CCsvbUtility::GetCsvbInfo points at them; CreateCsvbRows and
// CreateCsvbData read them, swapping their bytes when asked). The contents are not known here.
struct stCsvbRowInfo;
struct stCsvbDataInfo;

// what CCsvbUtility::GetCsvbInfo reads of a csvb file (CCsvbData::Load zeroes one first). The names are not the
// original's.
struct stCsvbInfo {
    unsigned int pad_0;
    unsigned short rowCount;   // CCsvbData::Load builds as many rows
    unsigned short dataCount;  // and as many cells
    unsigned int pad_8;
    unsigned int stringSize;  // the bytes of the file's strings, which CCsvbData::Load copies
    const stCsvbRowInfo* pRowInfo;
    const stCsvbDataInfo* pDataInfo;
    const unsigned char* pValues;  // the cells' values (CreateCsvbData reads them by the cells' types)
    const char* pStrings;
};

namespace csvb {
// a row as CCsvbUtility::CreateCsvbRows builds it: its cells are dataCount from dataIndex on (each row's index is the
// sum of the counts before it). The names are not the original's.
struct stCsvbRow {
    unsigned short columnCount;
    unsigned short dataIndex;
};

// a cell's type (CCsvbUtility::CreateCsvbData's); the names are not the original's
enum CsvbType {
    CSVB_TYPE_INT = 0,
    CSVB_TYPE_FLOAT = 1,
    CSVB_TYPE_STRING = 3,
};

// a cell as CCsvbUtility::CreateCsvbData builds it, 0x10 bytes: its type and value. The names are not the original's.
struct stCsvbData {
    int type;  // a CsvbType
    union {
        int intValue;
        float floatValue;
        const char* stringValue;  // into CCsvbData's copy of the file's strings
    };
};

// csvb's reading of a csvb file (csvb_utility.cpp's functions, by their symbols)
class CCsvbUtility {
public:
    // the file's bytes from the file system and their size; the buffer is the caller's to give back
    static bool LoadFile(const char* path, void** ppData, unsigned int* pSize);
    // 0 for a csvb file this reads (CCsvbData::Load stops on anything else)
    static int GetCsvbFormat(const void* pData);
    static bool GetCsvbInfo(stCsvbInfo& info, const void* pData, unsigned int size, bool swap);
    static stCsvbRow* CreateCsvbRows(mtl::ALLOC_HANDLE handle, const stCsvbRowInfo* pRowInfo, unsigned short count,
                                     bool swap);
    static stCsvbRow* CreateCsvbRows(mm::mtl::IAllocator* allocator, const stCsvbRowInfo* pRowInfo,
                                     unsigned short count, bool swap);
    static stCsvbData* CreateCsvbData(mtl::ALLOC_HANDLE handle, const stCsvbDataInfo* pDataInfo, unsigned short count,
                                      const unsigned char* pValues, const char* pStrings, bool swap);
    static stCsvbData* CreateCsvbData(mm::mtl::IAllocator* allocator, const stCsvbDataInfo* pDataInfo,
                                      unsigned short count, const unsigned char* pValues, const char* pStrings,
                                      bool swap);
};

// a csvb file's table, loaded: its rows, its cells and a copy of its strings, from monolib's memory manager or
// from an allocator (which Clear gives them back to). The field names are not the original's.
class CCsvbData {
public:
    CCsvbData();
    ~CCsvbData();
    void Clear();
    bool Load(mtl::ALLOC_HANDLE handle, const char* path);
    bool Load(mtl::ALLOC_HANDLE handle, const void* pData, unsigned int size);
    bool Load(mm::mtl::IAllocator* allocator, const char* path);
    bool Load(mm::mtl::IAllocator* allocator, const void* pData, unsigned int size);
    unsigned short GetRowCount() const;
    unsigned short GetColumCount(unsigned short row) const;
    int GetInt(unsigned short row, unsigned short column) const;
    float GetFloat(unsigned short row, unsigned short column) const;
    const char* GetString(unsigned short row, unsigned short column) const;

    unsigned short m_rowCount;
    stCsvbRow* m_pRows;
    unsigned short m_dataCount;
    stCsvbData* m_pData;
    unsigned int m_stringSize;
    char* m_pStrings;
    mm::mtl::IAllocator* m_pAllocator;  // the allocator Load took, or none for the memory manager's
};
}  // namespace csvb

#endif
