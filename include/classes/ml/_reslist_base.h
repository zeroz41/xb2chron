#ifndef CLASSES_ML__RESLIST_BASE_H
#define CLASSES_ML__RESLIST_BASE_H

#include "mtl/MemManager.h"

namespace ml {
// a template: 10 instances in the module. A doubly linked list of T in a node buffer of m_capacity nodes (a node
// with no next is free) around an end node of its own; _wrootst::WorkRoot's destructor inlines the clear and the
// buffer's release (the member names are not the original's)
template <typename T0>
class _reslist_base {
public:
    // a node's links, a base of its own as in mm_lib's list.h (mm::mtl::_ReslistBase): clear()'s store of the end's
    // next through the node the walk stops on comes out as the original's only with the link a base pointer
    struct NodeBase {
        NodeBase* m_next;
        NodeBase* m_prev;
    };
    struct Node : NodeBase {
        T0 m_value;
    };
    class iterator {
    public:
        iterator(Node* node) : m_node(node) {}
        T0& operator*() const { return m_node->m_value; }
        iterator& operator++() {
            m_node = static_cast<Node*>(m_node->m_next);
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            m_node = static_cast<Node*>(m_node->m_next);
            return old;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }
        Node* m_node;
    };

    // empty, with no node buffer (ml::WorkObj's constructor then gives its children's list one)
    // (mm_lib's list.h shape: the end set in the body, its links through it)
    _reslist_base() : m_pBuffer(nullptr), m_capacity(0), m_size(0), m_isExternal(false) {
        m_pEnd = &m_end;
        m_pEnd->m_next = m_pEnd;
        m_pEnd->m_prev = m_pEnd;
    }
    // clears the list, then releases the node buffer unless it is external (inline: every owner's destructor
    // inlines it; the out-of-line copies are the weak instances in the owners' units)
    virtual ~_reslist_base() {  // slot 0
        clear();
        if (!m_isExternal && m_pBuffer != nullptr) {
            delete[] m_pBuffer;
            m_pBuffer = nullptr;
        }
    }

    // a buffer of capacity free nodes from mem (inline: WorkObj's constructor and wkReplaceHasChild inline it; the
    // name is not the original's)
    void create(int capacity, mtl::ALLOC_HANDLE mem) {
        m_pBuffer = new (mem, nullptr, 0, 4, false) Node[capacity];
        for (int i = 0; i < capacity; i++) {
            m_pBuffer[i].m_next = nullptr;
        }
        m_capacity = capacity;
    }

    iterator begin() { return iterator(static_cast<Node*>(m_pEnd->m_next)); }
    iterator end() { return iterator(m_pEnd); }
    // a const list's walk (WinViewRoot::isCurrentChild walks a const work's children)
    iterator begin() const { return iterator(static_cast<Node*>(m_pEnd->m_next)); }
    iterator end() const { return iterator(m_pEnd); }
    int size() const { return m_size; }

    void push_back(const T0& value) { insert(end(), value); }
    // enters the value before pos in the first free node (entrySwap's push_back reads the end node before it looks
    // for a free one; the name is not the original's)
    void insert(iterator pos, const T0& value) {
        int i;
        for (i = 0; i < m_capacity; i++) {
            if (m_pBuffer[i].m_next == nullptr) {
                break;
            }
        }
        Node* node = &m_pBuffer[i];
        node->m_value = value;
        node->m_next = pos.m_node;
        node->m_prev = pos.m_node->m_prev;
        pos.m_node->m_prev->m_next = node;
        pos.m_node->m_prev = node;
        m_size++;
    }
    // empties the list and releases its node buffer unless it is external, leaving no room (inline:
    // WorkObj::wkReplaceHasChild inlines it before create; the name is not the original's)
    void release() {
        clear();
        if (!m_isExternal && m_pBuffer != nullptr) {
            delete[] m_pBuffer;
            m_pBuffer = nullptr;
        }
        m_capacity = 0;
    }
    void pop_front() { erase(begin()); }
    // unlinks every node (a free node has no next); the end's next is stored through the node the walk stops on,
    // as mm_lib's list.h clear() does
    // unlinks every node (a free node has no next) and empties the list; the walk ends on the end node, whose next
    // is stored through it (inlined in every _reslist_base destructor, e.g. 0x71006BE514)
    // unlinks the node it names and frees it (WorkObj::wkRemoveChild, WorkCpu::removeSwap)
    void erase(iterator it) {
        Node* node = it.m_node;
        NodeBase* next = node->m_next;
        NodeBase* prev = node->m_prev;
        prev->m_next = next;
        next->m_prev = prev;
        node->m_next = nullptr;
        m_size--;
    }
    void clear() {
        Node* node = static_cast<Node*>(m_pEnd->m_next);
        while (node != m_pEnd) {
            Node* next = static_cast<Node*>(node->m_next);
            node->m_next = nullptr;
            node = next;
        }
        node->m_next = node;
        m_pEnd->m_prev = m_pEnd;
        m_size = 0;
    }

    Node* m_pEnd;       // 0x08 &m_end
    Node m_end;         // 0x10
    Node* m_pBuffer;    // 0x28
    int m_capacity;     // 0x30
    int m_size;         // 0x34
    bool m_isExternal;  // 0x38 the buffer is not the list's own: the destructor keeps it
};
}  // namespace ml

#endif
