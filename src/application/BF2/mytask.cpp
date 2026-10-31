#include "classes/minigame/tora/mytask.h"
#include "classes/gf/GfAllocator.h"

namespace minigame { namespace tora {

void mytask::reset() {
    m_free = static_cast<_sTask*>(m_buf);
    m_head = nullptr;
    m_tail = nullptr;
    if (m_free != nullptr) {
        _sTask* task = m_free;
        for (int i = 0; i < m_count - 1; i++) {
            task->m_next = reinterpret_cast<_sTask*>(reinterpret_cast<long>(task) + m_size);
            task = task->m_next;
        }
        task->m_next = nullptr;
    }
}

mytask::mytask(int size, int count) {
    m_buf = gf::getAllocator(gf::ALLOCATOR(0))->allocate(size * count, 0x40);
    m_size = size;
    m_count = count;
    reset();
}

mytask::~mytask() {
    gf::getAllocator(gf::ALLOCATOR(0))->deallocate(m_buf);
}

// takes a node off the free list and links it after the last live one
void* mytask::entry() {
    _sTask* task = m_free;
    if (task != nullptr) {
        _sTask* prev = m_tail;
        m_free = task->m_next;
        task->m_prev = prev;
        if (prev == nullptr) {
            task->m_next = nullptr;
            m_head = task;
            m_tail = task;
        } else {
            task->m_next = prev->m_next;
            if (task->m_next == nullptr) {
                m_tail = task;
            } else {
                task->m_next->m_prev = task;
            }
            prev->m_next = task;
        }
    }
    return task;
}

// unlinks a live node and gives it back to the free list
void mytask::remove(void* p) {
    _sTask* task = static_cast<_sTask*>(p);
    if (task == m_cur) {
        m_cur = task->m_next;
    }
    if (task->m_next == nullptr) {
        m_tail = task->m_prev;
    } else {
        task->m_next->m_prev = task->m_prev;
    }
    if (task->m_prev == nullptr) {
        m_head = task->m_next;
    } else {
        task->m_prev->m_next = task->m_next;
    }
    task->m_next = m_free;
    m_free = task;
    task->m_move = nullptr;
    task->m_draw = nullptr;
}

void mytask::executeMove() {
    _sTask* task = m_head;
    while (task != nullptr) {
        m_cur = task->m_next;
        if (task->m_move != nullptr) {
            task->m_move(task);
        }
        task = m_cur;
    }
}

void mytask::executeDraw() {
    _sTask* task = m_head;
    while (task != nullptr) {
        m_cur = task->m_next;
        if (task->m_draw != nullptr) {
            task->m_draw(task);
        }
        task = m_cur;
    }
}

// the live node after task, or the first one when task is null
void* mytask::enum_next(void* task) {
    if (task == nullptr) {
        return m_head;
    }
    return static_cast<_sTask*>(task)->m_next;
}

}}  // namespace minigame::tora
