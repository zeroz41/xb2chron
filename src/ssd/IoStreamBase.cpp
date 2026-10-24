#include "nn/os.h"
#include "nn/fs.h"
#include "ssd/Debug.h"
#include "classes/ssd/Allocator.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/IoStreamBase.h"
#include "classes/ssd/FileStream.h"
#include "classes/ssd/MemoryStream.h"
#include "ssd/AudioContents.h"
#include <string.h>

namespace ssd {

Result IoStreamBase::Open(const TextRef& path, OpenMode mode) {
    return Result(-1);
}

Result IoStreamBase::Open(void* data, unsigned long size, OpenMode mode) {
    return Result(-1);
}

Result IoStreamBase::GetData(unsigned long offset, unsigned long size, void* buffer, unsigned long* readSize) {
    Result result = Seek(SeekMode_Begin, offset, nullptr);
    if (result < 0) {
        return result;
    }
    return Read(size, buffer, readSize);
}

}  // namespace ssd
