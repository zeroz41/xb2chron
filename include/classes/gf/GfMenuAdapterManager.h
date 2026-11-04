#ifndef CLASSES_GF_GFMENUADAPTERMANAGER_H
#define CLASSES_GF_GFMENUADAPTERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gf/GfMenuAdapter.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuAdapterManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B59CA8; owns the menu adapters: postUpdate updates them and deletes those whose plugin only they
// still hold. The field names are not the original's.
class GfMenuAdapterManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuAdapterManager> {
public:
    typedef mm::mtl::IntrusiveList<GfMenuAdapter> AdapterList;
    explicit GfMenuAdapterManager(const GfSetupParam& param);
    virtual ~GfMenuAdapterManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static void postUpdateAfter(const fw::UpdateInfo& info);
    static bool isAdapterFull();
    // the category adapters made from now on belong to (0 after endCategory), and the categories that update
    static void beginCategory(unsigned int category);
    static void endCategory();
    // adapters made from now on update after the others (postUpdateAfter)
    static void beginAddAfter();
    static void endAddAfter();
    static void addActiveCategory(unsigned int category);
    static void delActiveCategory(unsigned int category);
    // 2.0.0's symbols name it. What it does: deletes, from every list (the five categories, the uncategorized one and
    // the after one), each adapter whose plugin is gone or held by it alone, without updating the others.
    static void cleanup();
    // the list an adapter joins (GfMenuAdapter's constructor): uncategorized when there is no category and
    // the flag is set, else the category's, or the after list between beginAddAfter and endAddAfter
    void addAdapter(GfMenuAdapter* adapter, bool uncategorized);
    void setAfterUpdate(GfMenuAdapter* adapter);  // moves it from its category's list to the after list

    AdapterList m_categoryLists[5];  // updated by postUpdate while their bit of m_activeCategories is set
    AdapterList m_list;              // uncategorized: postUpdate updates up to 200 a frame from m_cursor
    AdapterList m_afterList;         // postUpdateAfter's
    unsigned int m_activeCategories;
    unsigned int m_category;
    bool m_addAfter;
    AdapterList::iterator m_cursor;
};
}  // namespace gf

#endif
