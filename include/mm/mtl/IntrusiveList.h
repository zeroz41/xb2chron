#ifndef MM_MTL_INTRUSIVELIST_H
#define MM_MTL_INTRUSIVELIST_H

#include "mm/MMStdBase.h"

// the category its iterator states (defined in <algorithm>, which the users of std::lower_bound include)
namespace std { inline namespace __1 { struct bidirectional_iterator_tag; } }

// mm_lib's intrusive_list.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_INTRUSIVE_LIST_PATH "../../../mcl/mm_lib/source\\mm_mtl/intrusive_list.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's (mtl::CallStackManager::remove cites it so)
#define MM_MTL_INTRUSIVE_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/intrusive_list.h"
#else
#define MM_MTL_INTRUSIVE_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/intrusive_list.h"
#endif

namespace mm { namespace mtl {

// the links an element of an intrusive list carries; unlinked, both point at the node itself (the constructor
// sets m_prev first: AreaWind's constructor stores its node's that way round)
class IntrusiveListNodeBase {
public:
    IntrusiveListNodeBase() { m_next = m_prev = this; }
    bool intoNode() const {
        return m_next != this;
    }

    IntrusiveListNodeBase* m_next;
    IntrusiveListNodeBase* m_prev;
};

// a node that knows the element it belongs to, for an element in several lists (a member per list, not a base):
// a list of these finds each element through m_pOwner (wnd::WindWorld's lists of its winds and of the objects it
// releases). The names are not the original's.
template <typename T>
class IntrusiveListNode : public IntrusiveListNodeBase {
public:
    IntrusiveListNode() {}
    // one that starts with its owner given (fw::Camera's constructor passes none)
    explicit IntrusiveListNode(T* owner) : m_pOwner(owner) {}

    T* m_pOwner;  // the element's constructor sets it to the element
};

// a circular list through its elements' nodes, closed by its own
class IntrusiveListBase {
public:
    IntrusiveListBase();
    static void linkNode(IntrusiveListNodeBase* node, IntrusiveListNodeBase* next);
    static void unlinkNode(IntrusiveListNodeBase* node);

    IntrusiveListNodeBase m_root;  // its next is the first element, its prev the last
    int m_size;  // intrusive_list.h asserts `m_size >= 0` as it removes one
};

// an intrusive list of T, which carries the links as its IntrusiveListNodeBase base: an element is found from its
// node by the base's offset (1.0.0's wnd::Dispatcher::dispatchAll walks an IntrusiveList<wnd::WindProbe> so, its
// end the list's own node taken as an element). The members are 1.0.0's inlined code; the names of push_back's
// and operator*'s are the standard ones, pop_front's and empty's are not known to be the original's.
template <typename T>
class IntrusiveList : public IntrusiveListBase {
public:
    class iterator {
    public:
        // bidirectional: fw::CameraLayer::push finds a camera's place with std::lower_bound, whose advance steps
        // back for a negative count
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef long difference_type;
        typedef T* pointer;
        typedef T& reference;

        explicit iterator(T* node) : m_node(node) {}
        T& operator*() const {
#line 71 MM_MTL_INTRUSIVE_LIST_PATH
            MM_ASSERT(m_node);
            return *m_node;
        }
        // unchecked (fw::ReflectionValueStruct::writeDefault calls each value's through it)
        T* operator->() const { return m_node; }
        iterator& operator++() {
            m_node = static_cast<T*>(static_cast<IntrusiveListNodeBase*>(m_node)->m_next);
            return *this;
        }
        iterator& operator--() {
            m_node = static_cast<T*>(static_cast<IntrusiveListNodeBase*>(m_node)->m_prev);
            return *this;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }

        T* m_node;
    };

    // ptr linked last (1.0.0's createReflection functions inline it)
    void push_back(T* ptr) {
#line 231 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(ptr);
        linkNode(ptr, &m_root);
        ++m_size;
    }
    // an element linked last, by reference: no assertion (1.0.0's GmkPhantom constructor links itself so, with no
    // check; the overload is inferred, its name is not known to be the original's)
    void push_back(T& ref) {
        linkNode(&ref, &m_root);
        ++m_size;
    }
    // ptr linked first (fw::CameraLayer::pushPlugin)
    void push_front(T* ptr) {
#line 243 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(ptr);
        linkNode(ptr, m_root.m_next);
        ++m_size;
    }
    // ptr linked before pos, asserted (fw::CameraLayer::push links a camera before the first one of a higher
    // order so; the name is not the original's: insert above is another function)
    void insert_before(iterator pos, T* ptr) {
#line 256 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(ptr);
        linkNode(ptr, pos.m_node);
        ++m_size;
    }
    // the first element, still linked (the name is not known to be the original's)
    T* front() const { return static_cast<T*>(m_root.m_next); }
    // the first element, unlinked
    T* pop_front() {
        IntrusiveListNodeBase* node = m_root.m_next;
        T* front = static_cast<T*>(node);
        unlinkNode(node);
        --m_size;
#line 170 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(m_size >= 0);
        return front;
    }
    // ptr unlinked (fw::SensorManager's remove functions; the name is not known to be the original's)
    void remove(T* ptr) {
        unlinkNode(ptr);
        --m_size;
#line 170 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(m_size >= 0);
    }
    bool empty() const { return m_root.m_next == &m_root; }
    // ptr linked before pos (UIInputManager::registInputLayer keeps its layers sorted so; the name is not known to
    // be the original's). The original compares the root first (`cmp root, pos`) and keeps the test after its
    // search loop: `end() == pos` with a push_back arm gives that; `pos == end()` lets the loop exits skip the test.
    void insert(iterator pos, T* ptr) {
        if (end() == pos) {
            push_back(ptr);
        } else {
            linkNode(ptr, pos.m_node);
            ++m_size;
        }
    }
    // it unlinked; the element after it (the name is not known to be the original's)
    iterator erase(iterator it) {
#line 268 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(!empty());
#line 269 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(it != end());
        iterator next(static_cast<T*>(static_cast<IntrusiveListNodeBase*>(it.m_node)->m_next));
        unlinkNode(it.m_node);
        --m_size;
#line 170 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(m_size >= 0);
        return next;
    }

    // every element unlinked (GfMenuAdapterManager's destructor calls it out of line; the name is not known to be
    // the original's)
    // the elements from first up to last unlinked (the name is not known to be the original's)
    iterator erase(iterator first, iterator last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }
    void clear() { erase(begin(), end()); }

    iterator begin() const { return iterator(static_cast<T*>(m_root.m_next)); }
    iterator end() const { return iterator(static_cast<T*>(const_cast<IntrusiveListNodeBase*>(&m_root))); }
};

}}  // namespace mm::mtl

#endif
