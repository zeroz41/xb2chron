#ifndef GF_PLUGINMANAGER_H
#define GF_PLUGINMANAGER_H

namespace mm { namespace mtl { class IAllocator; } }

namespace gf {
// a behavior component's plugins (GfComBehavior holds one at 0x10): three vectors on one allocator
// (its destructor asserts mm_mtl/vector.h's `m_allocator` for each) and a flag at 0x80
class PluginManager {
public:
    PluginManager(mm::mtl::IAllocator* allocator);
    ~PluginManager();

    unsigned char pad_0[0x88];
};
}  // namespace gf

#endif
