#ifndef MM_MTL_FIXEDLIST_H
#define MM_MTL_FIXEDLIST_H

#include <new>
#include "mm/MMStdBase.h"

// mm_lib's fixed_list.h, as the including file's include path named it (see mm/mtl/IntrusiveList.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_FIXED_LIST_PATH "../../../mcl/mm_lib/source\\mm_mtl/fixed_list.h"
#else
#define MM_MTL_FIXED_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_list.h"
#endif

namespace mm { namespace mtl {

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
    bool empty() const { return m_num_nodes == 0; }

    void clear() {
        for (unsigned long i = node(0)->m_next; node(i) != node(0); i = node(i)->m_next) {
            reinterpret_cast<T*>(node(i)->m_value)->~T();
        }
        unlink_end();
        m_num_nodes = 0;
        init_free_index();
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
    alignas(ListNode) unsigned char m_nodes[sizeof(ListNode) * (N + 1)];  // N + 1 ListNodes
    index_type m_free_index[N + 1];
    int m_free_index_top;
    int m_num_nodes;
};

}}  // namespace mm::mtl

#endif
