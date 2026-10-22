#ifndef CLASSES_GF_GFASSETRESOURCE_H
#define CLASSES_GF_GFASSETRESOURCE_H

#include "classes/fw/CommonResource.h"
#include "classes/ml/DrStmReadCheck.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace gf {
// table 0x7100B43668: one asset's data, held in a buffer the caller gives (create(..., void*, unsigned int)) or
// requested as a fw::CommonResource (create(..., IAllocator*, int))
class GfAssetResource {
public:
    // inline: this build has no copy of it, nor of destroy, destroyResource and importSample (1.0.0 has all four)
    GfAssetResource()
        : pad_8(0), m_type(0), m_requestArg(0), m_resource(nullptr), m_allocator(nullptr), m_data(nullptr),
          m_size(0), m_stream(nullptr), m_sampleHead(0x19283746), m_sampleTail(0x19283746) {}
    virtual ~GfAssetResource();  // slot 0
    static GfAssetResource* create(const char* label, const char* name, void* data, unsigned int size);
    static GfAssetResource* create(const char* label, const char* name, mm::mtl::IAllocator* allocator, int arg);
    void* getAssetData() const;
    unsigned int getAssetSize() const;
    const char* getAssetName() const;
    bool isFinishLoad() const;
    bool isValidData() const;
    void setupStreamObject();

    void destroy() {
        destroyResource();
        m_name = "";
        m_allocator = nullptr;
        m_size = 0;
        m_type = 0;
    }
    // what it holds, released: a buffer of the caller's (m_type 3) is only forgotten
    void destroyResource() {
        if (m_type == 3) {
            m_data = nullptr;
        }
        if (m_stream != nullptr) {
            m_stream->release();
            m_stream = nullptr;
        }
        if (m_data != nullptr) {
            mtl::MemManager::deallocate(m_data, 0, false);
            m_data = nullptr;
        }
        if (m_resource != nullptr) {
            m_resource->release();
            m_resource = nullptr;
        }
    }
    // the data's first and last words, kept to be checked against
    void importSample() {
        m_sampleHead = *static_cast<unsigned int*>(m_data);
        m_sampleTail = *reinterpret_cast<unsigned int*>(static_cast<char*>(m_data) + m_size - 4);
    }

    unsigned int pad_8;  // cleared by the constructor; nothing here reads it
    // where the data is: 1 a requested fw::CommonResource, 2 a buffer of its own, 3 the caller's buffer, 0 none
    // (the field names are not the original's)
    int m_type;
    int m_requestArg;  // what create passes on to fw::CommonResource::request
    fw::CommonResource* m_resource;
    mm::mtl::IAllocator* m_allocator;  // the allocator the resource was requested from
    mtl::ALLOC_HANDLE m_allocHandle;  // 1.0.0's reloadPost requests from it when it is set
    void* m_data;
    unsigned int m_size;
    mm::mtl::FixStr<128> m_name;  // getAssetName's: the path
    const char* m_label;  // create's first argument; the constructor leaves it
    ml::DrStmReadCheck* m_stream;  // setupStreamObject's
    unsigned int m_sampleHead;  // importSample's: the data's first word, 0x19283746 before
    unsigned int m_sampleTail;  // importSample's: the data's last word, 0x19283746 before
};
}  // namespace gf

#endif
