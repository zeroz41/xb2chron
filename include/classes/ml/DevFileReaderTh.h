#ifndef CLASSES_ML_DEVFILEREADERTH_H
#define CLASSES_ML_DEVFILEREADERTH_H

#include "classes/ml/DevFileJobTh.h"
#include "mm/mtl/FixedVector.h"

namespace ml {
class DevFileAccessor;
// table 0x7100B773F0 (DevFileTh::Impl::readFile creates it)
class DevFileReaderTh : public ::ml::DevFileJobTh {
public:
    // a medium the file can be read from (Impl::readFile fills them; the names are not the original's)
    struct Entry {
        unsigned int m_media;
        const char* m_path;
        DevFileAccessor* m_accessor;
    };

    virtual ~DevFileReaderTh() {}  // slot 0
    virtual bool asyncUpdate();  // slot 2
    virtual int getJobType() const { return 1; }  // slot 3
    virtual DevFileReaderTh* getReader() { return this; }  // slot 4

    mm::mtl::FixedVector<Entry, 32> m_entries;  // 0x20 (the name is not the original's)
};
}  // namespace ml

#endif
