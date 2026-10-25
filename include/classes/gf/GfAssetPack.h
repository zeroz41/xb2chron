#ifndef CLASSES_GF_GFASSETPACK_H
#define CLASSES_GF_GFASSETPACK_H

namespace mm { namespace mtl { class IAllocator; } }

namespace gf {
// table 0x7100B43648
class GfAssetPack {
public:
    virtual ~GfAssetPack();  // slot 0
    void loadStart(mm::mtl::IAllocator* allocator);
};
}  // namespace gf

#endif
