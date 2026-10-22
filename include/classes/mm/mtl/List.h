#ifndef CLASSES_MM_MTL_LIST_H
#define CLASSES_MM_MTL_LIST_H

#include "classes/mm/mtl/_ReslistBase.h"
#include <new>

namespace fw { class SoundPack; }
namespace fw { class SoundSsdBank; }
namespace fw { class SoundSsdSource; }
namespace fw { class UpdatableObject; }
namespace ml { class DrLightObjGlobalIBL; }
namespace ssd { class SoundHandle; }

namespace mm { namespace mtl {
// a template: 9 instances in the module. Its destructor is trivial (its table's slot holds _ReslistBase's)
template <typename T0>
class List : public ::mm::mtl::_ReslistBase< T0> {
    typedef typename _ReslistBase<T0>::Node Node;
    typedef typename _ReslistBase<T0>::NodeBase NodeBase;

public:
    // an iterator is its node (its copy is user-provided: 3.0.1's UpdatableGroup::tail keeps it a pointer, not an
    // integer, which drops the null test of erase's node)
    class iterator {
    public:
        iterator(Node* node) : m_node(node) {}
        iterator(const iterator& other) : m_node(other.m_node) {}
        T0& operator*() const { return m_node->m_value; }
        iterator& operator++() {
            m_node = static_cast<Node*>(m_node->m_next);
            return *this;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }
        Node* m_node;
    };

    List() {}
    explicit List(IAllocator* allocator) : _ReslistBase<T0>(allocator) {}
    virtual ~List() {}  // slot 0
    iterator begin() { return iterator(this->first()); }
    iterator end() { return iterator(this->last()); }

    void push_back(const T0& value) {
        NodeBase* pos = this->m_head;
        Node* node = this->allocNode();
        // a copy of value made in the node (fw::MessageManager::Impl::push's holder gains a reference)
        new (&node->m_value) T0(value);
        node->m_next = pos;
        node->m_prev = pos->m_prev;
        pos->m_prev->m_next = node;
        pos->m_prev = node;
        // the most elements it has held
        if (this->m_capacity < ++this->m_size) {
            this->m_capacity = this->m_size;
        }
    }
    // removes the element at it: the next one's iterator
    iterator erase(iterator it) {
        iterator e = end();
        if (it == e) {
            return e;
        }
        Node* node = it.m_node;
        NodeBase* next = node->m_next;
        NodeBase* prev = node->m_prev;
        prev->m_next = next;
        next->m_prev = prev;
        node->m_value.~T0();
        this->freeNode(node);
        --this->m_size;
        return iterator(static_cast<Node*>(next));
    }
};
}}  // namespace mm::mtl

#endif
