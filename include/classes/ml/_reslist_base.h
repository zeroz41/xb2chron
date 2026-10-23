#ifndef CLASSES_ML__RESLIST_BASE_H
#define CLASSES_ML__RESLIST_BASE_H

namespace ml {
// a template: 10 instances in the module. A doubly linked list of T in a node buffer of m_capacity nodes (a node
// with no next is free) around an end node of its own; _wrootst::WorkRoot's destructor inlines the clear and the
// buffer's release (the member names are not the original's)
template <typename T0>
class _reslist_base {
public:
    struct Node {
        Node* m_next;
        Node* m_prev;
        T0 m_value;
    };
    class iterator {
    public:
        iterator(Node* node) : m_node(node) {}
        T0& operator*() const { return m_node->m_value; }
        iterator& operator++() {
            m_node = m_node->m_next;
            return *this;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }
        Node* m_node;
    };

    virtual ~_reslist_base();  // slot 0

    iterator begin() { return iterator(m_pEnd->m_next); }
    iterator end() { return iterator(m_pEnd); }
    int size() const { return m_size; }

    void push_back(const T0& value) {
        int i;
        for (i = 0; i < m_capacity; i++) {
            if (m_pBuffer[i].m_next == nullptr) {
                break;
            }
        }
        Node* node = &m_pBuffer[i];
        node->m_value = value;
        node->m_next = m_pEnd;
        node->m_prev = m_pEnd->m_prev;
        m_pEnd->m_prev->m_next = node;
        m_pEnd->m_prev = node;
        m_size++;
    }
    void pop_front() {
        Node* node = m_pEnd->m_next;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        node->m_next = nullptr;
        m_size--;
    }
    void clear() {
        Node* node = m_pEnd->m_next;
        while (node != m_pEnd) {
            Node* next = node->m_next;
            node->m_next = nullptr;
            node = next;
        }
        m_pEnd->m_next = m_pEnd;
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
