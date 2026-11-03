#ifndef MM_MTL_FIXEDLIST_H
#define MM_MTL_FIXEDLIST_H

#include <new>
#include "mm/MMStdBase.h"

// the category its iterator states (defined in <algorithm>, which the users of std::lower_bound include)
namespace std { inline namespace __1 { struct bidirectional_iterator_tag; } }

// mm_lib's fixed_list.h, as the including file's include path named it (see mm/mtl/IntrusiveList.h)
#if defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's own files (ml::WorkCpu::addBackgroundListener's push_back cites it so)
#define MM_MTL_FIXED_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/fixed_list.h"
#elif defined(MM_LIB_FROM_LIBS)
#define MM_MTL_FIXED_LIST_PATH "../../../mcl/mm_lib/source\\mm_mtl/fixed_list.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (ml::DrIBLObj's list erase cites it so)
#define MM_MTL_FIXED_LIST_PATH "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/fixed_list.h"
#else
#define MM_MTL_FIXED_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_list.h"
#endif

namespace mm { namespace mtl {

// the word a FixedList's node storage is declared in: an unsigned integer as wide as the node's alignment, up to
// eight bytes (the name is not the original's). The original's storage is no byte array: its end node's links,
// which sit inside such a word, are addressed from the list's storage register while its index, at a word's start,
// is folded to the owner's base + constant (GfGameObj::addInObj, WorkCpu::addBackgroundListener)
template <unsigned long Align>
struct FixedListWord {
    typedef unsigned long type;
};
template <>
struct FixedListWord<1> {
    typedef unsigned char type;
};
template <>
struct FixedListWord<2> {
    typedef unsigned short type;
};
template <>
struct FixedListWord<4> {
    typedef unsigned int type;
};

// the type of a FixedList's node indices (the name is not the original's)
template <bool Wide>
struct FixedListIndex {
    typedef unsigned char type;
};
template <>
struct FixedListIndex<true> {
    typedef unsigned short type;
};

// mm_lib's fixed_list.h (its assertions cite mm_mtl/fixed_list.h and name m_free_index_top, m_num_nodes,
// it.node()->in_list() and it.list() == this): a doubly linked list of up to N elements kept in N + 1 nodes in
// place, node 0 being the list's own end; nodes link by index, and the free ones are a stack of indices
template <typename T, unsigned long N>
class FixedList {
public:
    // the nodes' indices: a byte up to 255 nodes, two bytes past that (GfGameSearchObj's lists of 256 keep
    // their count at 0x1218) (the name is not the original's)
    typedef typename FixedListIndex<(N > 255)>::type index_type;
    struct ListNode {
        alignas(T) unsigned char m_value[sizeof(T)];
        index_type m_index;  // this node's own index; next == index while it is in no list (in_list())
        index_type m_next;
        index_type m_prev;

        bool in_list() const {
            return m_index != m_next;
        }
    };

    // an iterator is a node and its list (1.0.0's FixedList<...>::erase(node_iterator<T, ListNode*>) takes the
    // two in x1 and x2 and asserts it.list() == this)
    template <typename V, typename NodePtr>
    class node_iterator {
    public:
        // bidirectional: mtl::AssetAllocator<N>::addFreeList finds a run's place with std::lower_bound, whose advance
        // steps back for a negative count
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef V value_type;
        typedef long difference_type;
        typedef V* pointer;
        typedef V& reference;

        node_iterator(NodePtr node, FixedList* list) : m_node(node), m_list(list) {}
        V& operator*() const {
#line 84 MM_MTL_FIXED_LIST_PATH
            MM_ASSERT(m_node != 0);
            return *reinterpret_cast<V*>(m_node->m_value);
        }
        // no assertion: GfMountManager::getMount's walk reads its elements' fields with no `m_node != 0` check
        V* operator->() const { return reinterpret_cast<V*>(m_node->m_value); }
        node_iterator& operator++() {
            m_node = m_list->node(m_node->m_next);
            return *this;
        }
        // GfSizeAlloc::alloc's walk from the tail
        node_iterator& operator--() {
            m_node = m_list->node(m_node->m_prev);
            return *this;
        }
        bool operator==(const node_iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const node_iterator& other) const { return m_node != other.m_node; }
        NodePtr node() const { return m_node; }
        FixedList* list() const { return m_list; }

        NodePtr m_node;
        FixedList* m_list;
    };
    typedef node_iterator<T, ListNode*> iterator;

    FixedList() {
        m_num_nodes = 0;
        init_free_index();
        unlink_end();
    }
    ~FixedList() {
        clear();
    }

    // a node's address from its index, in the raw storage: the walks compare node addresses as offsets from the
    // storage and keep their null checks (an array of ListNode lets the compiler fold both)
    ListNode* node(unsigned long index) {
        return reinterpret_cast<ListNode*>(m_nodes) + index;
    }

    iterator begin() { return iterator(node(node(0)->m_next), this); }
    iterator end() { return iterator(node(0), this); }
    // a const list's walk (GfSequentialPlay::isExistEvent)
    typedef node_iterator<const T, ListNode*> const_iterator;
    const_iterator begin() const {
        FixedList* self = const_cast<FixedList*>(this);
        return const_iterator(self->node(self->node(0)->m_next), self);
    }
    const_iterator end() const {
        FixedList* self = const_cast<FixedList*>(this);
        return const_iterator(self->node(0), self);
    }
    // the first element equal to value, or end() (WorkCpu::removeBackgroundListener and unregistErrorCB walk with
    // the iterator's assertion and hand erase whichever of the two iterators the walk stopped on) (the name is not
    // the original's)
    template <typename U>
    iterator find(const U& value) {
        iterator it = begin();
        iterator last = end();
        for (; it != last; ++it) {
            if (*it == value) {
                return it;
            }
        }
        return last;
    }
    // the first element pred holds for, or end(): the walk stops on it and hands back that one iterator
    // (GfGameScene::getAppendControl and destroyDriverAppendModelControl compare it with end() again after the walk)
    // (the name is not the original's)
    template <typename Pred>
    iterator find_if(Pred pred) {
        iterator it = begin();
        for (; it != end(); ++it) {
            if (pred(*it)) {
                break;
            }
        }
        return it;
    }
    bool empty() const { return m_num_nodes == 0; }
    unsigned long size() const { return m_num_nodes; }
    // the first element, read without the iterator's assertion (GfFobjManager::registFiledObj reads its full
    // list's oldest item so) (the name is not the original's)
    T& front() { return *reinterpret_cast<T*>(node(node(0)->m_next)->m_value); }

    void clear() {
        for (unsigned long i = node(0)->m_next; node(i) != node(0); i = node(i)->m_next) {
            reinterpret_cast<T*>(node(i)->m_value)->~T();
        }
        unlink_end();
        m_num_nodes = 0;
        init_free_index();
    }

    // the first element unlinked and its node back on the free stack (the assertion's line 230, `!empty()`, with
    // no in_list check: GfQuestManager::destroyEvent) (the name is not the original's)
    void pop_front() {
#line 230 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(!empty());
        ListNode* erased = node(node(0)->m_next);
        reinterpret_cast<T*>(erased->m_value)->~T();
        m_free_index[++m_free_index_top] = erased->m_index;
        node(erased->m_prev)->m_next = erased->m_next;
        node(erased->m_next)->m_prev = erased->m_prev;
        erased->m_prev = erased->m_index;
        erased->m_next = erased->m_index;
        --m_num_nodes;
    }

    // value linked last, in a node off the free stack
    void push_back(const T& value) {
#line 241 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(m_free_index_top > 0);
        index_type index = m_free_index[m_free_index_top--];
        ListNode* added = node(index);
        new (added->m_value) T(value);
        added->m_index = index;
        ++m_num_nodes;
#line 246 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(m_num_nodes <= N + 1);
        ListNode* pos = node(0);
        added->m_prev = pos->m_prev;
        node(added->m_prev)->m_next = added->m_index;
        pos->m_prev = added->m_index;
        added->m_next = pos->m_index;
    }

    // value linked first, in a node off the free stack (GfSequentialPlay::addCommand and postUpdate inline it:
    // the assertions' lines 220 and 224, `m_num_nodes <= N`)
    void push_front(const T& value) {
#line 220 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(m_free_index_top > 0);
        index_type index = m_free_index[m_free_index_top--];
        ListNode* added = node(index);
        new (added->m_value) T(value);
        added->m_index = index;
        ++m_num_nodes;
#line 224 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(m_num_nodes <= N);
        ListNode* pos = node(node(0)->m_next);
        added->m_prev = pos->m_prev;
        node(added->m_prev)->m_next = added->m_index;
        pos->m_prev = added->m_index;
        added->m_next = pos->m_index;
    }

    // value linked before it, in a node off the free stack (GfSizeAlloc::free: the assertion's line 263)
    iterator insert(iterator it, const T& value) {
#line 263 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(m_free_index_top > 0);
        index_type index = m_free_index[m_free_index_top--];
        ListNode* added = node(index);
        new (added->m_value) T(value);
        added->m_index = index;
        ListNode* pos = it.node();
        added->m_prev = pos->m_prev;
        node(added->m_prev)->m_next = added->m_index;
        pos->m_prev = added->m_index;
        added->m_next = pos->m_index;
        ++m_num_nodes;
        return iterator(added, this);
    }

    // it unlinked and its node back on the free stack; the iterator after it
    iterator erase(iterator it) {
#line 274 MM_MTL_FIXED_LIST_PATH
        MM_ASSERT(!empty());
        MM_ASSERT(it.node()->in_list());
        MM_ASSERT(it.list() == this);
        iterator next = it;
        ++next;
        ListNode* erased = it.node();
        reinterpret_cast<T*>(erased->m_value)->~T();
        m_free_index[++m_free_index_top] = erased->m_index;
        node(erased->m_prev)->m_next = erased->m_next;
        node(erased->m_next)->m_prev = erased->m_prev;
        erased->m_prev = erased->m_index;
        erased->m_next = erased->m_index;
        --m_num_nodes;
        return next;
    }

private:
    void init_free_index() {
        for (int i = 0; i < N + 1; i++) {
            m_free_index[i] = i;
        }
        m_free_index_top = N;
    }
    void unlink_end() {
        node(0)->m_prev = 0;
        node(0)->m_next = 0;
        node(0)->m_index = 0;
    }

public:
    // N + 1 ListNodes, in words of the node's alignment (the name is not the original's)
    typedef typename FixedListWord<alignof(ListNode)>::type word_type;
    alignas(ListNode) word_type m_nodes[sizeof(ListNode) * (N + 1) / sizeof(word_type)];
    index_type m_free_index[N + 1];
    int m_free_index_top;
    int m_num_nodes;
};

}}  // namespace mm::mtl

#endif
