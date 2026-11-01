#include "fw/PadData.h"
#include "fw/PadRelay.h"
#include "classes/fw/PadResEvent.h"
#include "classes/fw/PadResEventManager.h"
#include "classes/fw/PadManager.h"
#include "bin/BinaryResolver.h"
#include <string.h>

namespace fw {
namespace {

// the head of a pad event binary, as bin::BinaryResolver resolves it (the names are not the original's)
struct PadEventHeader {
    unsigned int m_version;  // 1
    char m_magic[4];         // "PADD"
    PadResEvent* m_event;
};

}  // namespace

PadResEvent* PadEventImporter::create(void* binary, const char* name) {
    PadEventHeader* header = static_cast<PadEventHeader*>(bin::BinaryResolver::resolve(binary));
    if (header == nullptr) {
        return nullptr;
    }
    if (memcmp(header->m_magic, "PADD", 4) != 0) {
        return nullptr;
    }
    if (header->m_version != 1) {
        return nullptr;
    }
    new (header->m_event) PadResEvent;
    return header->m_event;
}

}  // namespace fw
