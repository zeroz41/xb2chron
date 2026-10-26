#ifndef LAYER_LAYERLINKLIST_H
#define LAYER_LAYERLINKLIST_H

namespace layer {
// a doubly linked list of the layer managers' shared objects: T holds its own m_prev (0x0) and m_next (0x8).
// deleteList is the one out-of-line member (layer::LayerLinkList<layer::LayerTextureObj>::deleteList); addList and
// removeList are inline in LayerTextureMan::createTextureObj, LayerVertexMan::createVertexObj and
// LayerVertexObj::release (their names are not the original's)
template <class T>
class LayerLinkList {
public:
    LayerLinkList() : m_head(nullptr), m_tail(nullptr), m_num(0) {}
    ~LayerLinkList() {
        m_head = nullptr;
        m_tail = nullptr;
        m_num = 0;
    }

    void addList(T* obj) {
        if (obj != nullptr) {
            if (m_tail != nullptr) {
                m_tail->m_next = obj;
                obj->m_prev = m_tail;
                m_tail = obj;
            } else {
                m_head = obj;
                m_tail = obj;
                obj->m_prev = nullptr;
            }
            obj->m_next = nullptr;
            m_num++;
        }
    }
    void removeList(T* obj) {
        if (obj->m_prev != nullptr) {
            if (obj->m_next != nullptr) {
                obj->m_prev->m_next = obj->m_next;
                obj->m_next->m_prev = obj->m_prev;
            } else {
                m_tail = obj->m_prev;
                m_tail->m_next = nullptr;
            }
        } else if (obj->m_next != nullptr) {
            m_head = obj->m_next;
            m_head->m_prev = nullptr;
        } else {
            m_head = nullptr;
            m_tail = nullptr;
        }
        obj->m_prev = nullptr;
        obj->m_next = nullptr;
        m_num--;
    }
    // takes obj out of the list and deletes it
    void deleteList(T* obj) {
        removeList(obj);
        delete obj;
    }

    T* m_head;  // 0x0
    T* m_tail;  // 0x8
    int m_num;  // 0x10
};
}  // namespace layer

#endif
