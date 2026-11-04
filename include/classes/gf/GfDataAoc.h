#ifndef CLASSES_GF_TUNK_B4C840_H
#define CLASSES_GF_TUNK_B4C840_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfDataAoc; }
namespace gf { class GfSetupParam; enum AOC_TYPE : unsigned int; }  // unsigned: getContentVersion zero-extends it

namespace gf {
// table 0x7100B4C840, no RTTI: the add-on content data of gf_data_aoc.cpp (inferred: "the add-on data"; new in 3.0.1,
// nothing in 1.0.0 names it), built by GfDataManager's constructor after GfDataStore::build
class GfDataAoc : public mm::mtl::PtrSingleton<GfDataAoc> {
public:
    // inline: build constructs it in place and tail-calls the loader (initialize leaves the parameter unused, so
    // build passes it as undefined)
    GfDataAoc(const GfSetupParam& param) : m_ready(false) {
        initialize(param);
    }
    virtual ~GfDataAoc();  // slot 0 (the key function)

    // allocates (gf_data_aoc.cpp line 43) the singleton (GfDataManager's constructor passes its setup parameter;
    // 2.0.0's symbols name it)
    static void build(const GfSetupParam& param);
    // clears m_ready and deletes the singleton (GfDataManager::destroy calls it after GfDataBdat::destroy;
    // 2.0.0's symbols name it)
    static void destroy();
    // m_ids[index], -1 while there is no singleton (GfMenuManager::getGiftNumber passes 4, the gift box menu 5;
    // 2.0.0's symbols name it)
    static int getContentVersion(AOC_TYPE index);
    // for each of the 6 add-ons: when nn::aoc lists it, reads "aoc<n>:/key.bin" and stores the index of the file's
    // first int in that add-on's key list (0 when absent from it); m_ready is set at the end (2.0.0's symbols name
    // it; the parameter is unused)
    void initialize(const GfSetupParam& param);

    bool m_ready;  // the names are not the original's
    int m_ids[6];  // -1 while an add-on is not installed or its key file was not read
};
}  // namespace gf

#endif
