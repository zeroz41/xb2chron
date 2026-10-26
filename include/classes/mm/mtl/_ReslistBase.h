#ifndef CLASSES_MM_MTL__RESLISTBASE_H
#define CLASSES_MM_MTL__RESLISTBASE_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

// mm_lib's list.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_LIST_PATH "../../../mcl/mm_lib/source\\mm_mtl/list.h"
#else
#define MM_MTL_LIST_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/list.h"
#endif

namespace mm { namespace mtl {
// a template: 9 instances in the module. mm_lib's list.h (its assertion `m_allocator && "yet setAllocator"` cites
// mm_mtl/list.h): a doubly linked list of T whose nodes come one at a time from an allocator; the list's end is a
// node of its own (gf::GfComSound's list destroys that node's value last). fw::UpdatableGroup's code shows every
// member; the names are not the original's but m_allocator, which the assertion names.
template <typename T0>
class _ReslistBase;
// a list's iterator, its node (GfComSound::eraseCache's mangled parameter names the template: the value, its
// reference and pointer types)
template <typename T0, typename Ref, typename Ptr>
class _reslist_iterator {
public:
    typedef typename _ReslistBase<T0>::Node Node;
    _reslist_iterator(Node* node) : m_node(node) {}
    _reslist_iterator(const _reslist_iterator& other) : m_node(other.m_node) {}
    Ref operator*() const { return m_node->m_value; }
    Ptr operator->() const { return &m_node->m_value; }
    _reslist_iterator& operator++() {
        m_node = static_cast<Node*>(m_node->m_next);
        return *this;
    }
    bool operator==(const _reslist_iterator& other) const { return m_node == other.m_node; }
    bool operator!=(const _reslist_iterator& other) const { return m_node != other.m_node; }
    Node* m_node;
};
template <typename T0>
class _ReslistBase {
public:
    // the links (the end is reached as one)
    struct NodeBase {
        NodeBase* m_next;
        NodeBase* m_prev;
    };
    struct Node : NodeBase {
        T0 m_value;
    };

    _ReslistBase() : m_capacity(0), m_size(0), m_alignment(8), m_allocator(nullptr) {
        m_head = &m_end;
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }
    // the same with its allocator set (fw::MessageManager::Impl's constructor stores it with the alignment, no
    // clear between)
    explicit _ReslistBase(IAllocator* allocator) : m_capacity(0), m_size(0), m_alignment(8), m_allocator(allocator) {
        m_head = &m_end;
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }
    // with its allocator and node alignment set (GfComSound's constructor stores 16, no reserve: no assertion)
    _ReslistBase(IAllocator* allocator, unsigned long alignment)
        : m_capacity(0), m_size(0), m_alignment(alignment), m_allocator(allocator) {
        m_head = &m_end;
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }
    virtual ~_ReslistBase() { clear(); }  // slot 0

    // destroys every element and frees its node (fw::MessageManager::Impl's list releases each message's holder)
    void clear() {
        Node* node = first();
        while (node != last()) {
            Node* next = static_cast<Node*>(node->m_next);
            node->m_value.~T0();
            freeNode(node);
            node = next;
        }
        node->m_next = node;
        m_head->m_prev = m_head;
        m_capacity = 0;
        m_size = 0;
    }
    // frees every node like clear() but keeps the count reserve set (fw::SoundSsdBank's destructor stores only the
    // size before its clear(); the name is not the original's)
    void freeNodes() {
        Node* node = first();
        while (node != last()) {
            Node* next = static_cast<Node*>(node->m_next);
            node->m_value.~T0();
            freeNode(node);
            node = next;
        }
        node->m_next = node;
        m_head->m_prev = m_head;
        m_size = 0;
    }
    // the allocator the nodes come from: a different one frees the nodes first
    void setAllocator(IAllocator* allocator) {
        if (m_allocator != allocator) {
            clear();
            m_allocator = allocator;
        }
    }
    // the size the list expects to reach and the alignment its nodes are allocated at (nodes come one at a time)
    void reserve(int capacity, unsigned long alignment = 8) {
#line 169 MM_MTL_LIST_PATH
        MM_ASSERT(m_allocator && "yet setAllocator");
        if (m_capacity < capacity) {
            m_alignment = alignment;
            m_capacity = capacity;
        }
    }

protected:
    Node* first() const { return static_cast<Node*>(m_head->m_next); }
    Node* last() const { return static_cast<Node*>(m_head); }  // the end
    Node* allocNode() { return static_cast<Node*>(m_allocator->allocate(sizeof(Node), m_alignment)); }
    void freeNode(Node* node) {
        if (node != nullptr && last() != node) {
            m_allocator->deallocate(node);
        }
    }

public:
    NodeBase* m_head;  // the end: the first node is its next, the last its prev
    Node m_end;  // the end's node (its value unused)
    int m_capacity;  // reserve's count, or the most elements it has held since
    int m_size;
    unsigned long m_alignment;  // what the nodes' allocations ask the allocator for
    IAllocator* m_allocator;
};
}}  // namespace mm::mtl

#endif
