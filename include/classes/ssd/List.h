// not proven yet: its table differs from the original's (word 2: _ZN3ssd4ListINS_11VoiceHandleEED1Ev where the original has _ZN3ssd4ListINS_11VoiceHandleEED0Ev)
#ifndef CLASSES_SSD_LIST_H
#define CLASSES_SSD_LIST_H

#include "classes/ssd/Allocator.h"

namespace ssd {
// a template: 9 instances in the module. An intrusive doubly linked list of T, which derives from Node:
// a sentinel node and the count (List<MemoryManager::BlockNode>: MemoryManager's constructor, 1.0.0). The
// member names other than Delete are not the original's.
template <typename T0>
class List {
public:
    // a link: the previous and the next node (a lone node links to itself)
    class Node {
    public:
        Node() : prev(this), next(this) {}
        virtual ~Node() {}  // slot 0

        Node* prev;
        Node* next;
    };

    List() : count_(0) {}
    // gives every node back as Delete does, written out here: ~List<SoundEntry> (SoundBank) has the loop in
    // its own body, which keeps it out of SoundBank's destructor
    virtual ~List() {  // slot 0
        if (count_ != 0) {
            T0* item = static_cast<T0*>(head_.next);
            while (item != static_cast<T0*>(&head_)) {
                T0* next = static_cast<T0*>(static_cast<Node*>(item)->next);
                Remove(item);
                SoundMemory::allocator_->DeleteInstance(item);
                item = next;
            }
        }
    }

    // links node in at the end
    void PushBack(Node* node) {
        node->prev = head_.prev;
        node->next = &head_;
        head_.prev = node;
        node->prev->next = node;
        ++count_;
    }

    // unlinks node
    void Remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = node;
        node->next = node;
        --count_;
    }

    // unlinks every node, keeping none
    void Clear() {
        Node* node = head_.next;
        while (node != &head_) {
            Node* next = node->next;
            Remove(node);
            node = next;
        }
    }

    // unlinks every node and gives it back to SoundMemory::allocator_ (each one heads an instance block)
    List* Delete() {
        T0* item = static_cast<T0*>(head_.next);
        while (item != static_cast<T0*>(&head_)) {
            T0* next = static_cast<T0*>(static_cast<Node*>(item)->next);
            Remove(item);
            SoundMemory::allocator_->DeleteInstance(item);
            item = next;
        }
        return this;
    }

    Node head_;
    int count_;
};

}  // namespace ssd

#endif
