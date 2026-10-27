#ifndef MM_MTL_MAP_H
#define MM_MTL_MAP_H

#include <new>
#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

// mm_lib's internal/red_black_tree.h, as the including file's include path named it (see mm/mtl/FixedQueue.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_RED_BLACK_TREE_PATH "../../../mcl/mm_lib/source\\mm_mtl/internal/red_black_tree.h"
#else
#define MM_MTL_RED_BLACK_TREE_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/internal/red_black_tree.h"
#endif

// mm_lib's map.h, as the including file's include path named it
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_MAP_PATH "../../../mcl/mm_lib/source\\mm_mtl/map.h"
#else
#define MM_MTL_MAP_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/map.h"
#endif

namespace mm { namespace mtl {

// a key and its value, as a Map keeps them (1.0.0's RedBlackTreeBase<...>::insert takes one)
template <typename K, typename V>
struct MapPair {
    MapPair() {}
    MapPair(const K& key, const V& value) : first(key), second(value) {}
    K first;
    V second;
};

// mm_lib's red-black tree (its assertions cite mm_mtl/internal/red_black_tree.h and name m_allocator, mem,
// new_node->color and m_size): the nodes come from the tree's allocator, and every tree of one kind shares one
// sentinel node (m_sentinel) as its leaves, its root's parent and its empty root. Traits gives the element and
// its key (Map's MapTraits).
template <typename Traits>
class RedBlackTreeBase {
public:
    typedef typename Traits::key_type key_type;
    typedef typename Traits::value_type value_type;

    enum color_type { red = 0, black = 1 };

    struct node {
        // the sentinel's own: every link to itself, black (the static initializer of m_sentinel)
        node() : left(this), parent(this), right(this), color(black) {}

        node* left;
        node* parent;
        node* right;
        value_type value;
        int color;
    };

    // the empty tree, with no allocator yet
    RedBlackTreeBase() : m_size(0), m_allocator(nullptr) {
        m_sentinel.color = black;
        m_sentinel.left = &m_sentinel;
        m_sentinel.right = &m_sentinel;
        m_sentinel.parent = &m_sentinel;
        m_root = &m_sentinel;
    }
    // the empty tree, its nodes from allocator (fw::SoundVariableTable's constructor)
    explicit RedBlackTreeBase(IAllocator* allocator) : m_size(0), m_allocator(allocator) {
        m_sentinel.color = black;
        m_sentinel.left = &m_sentinel;
        m_sentinel.right = &m_sentinel;
        m_sentinel.parent = &m_sentinel;
        m_root = &m_sentinel;
    }
    ~RedBlackTreeBase() {
        clear();
        m_allocator = nullptr;
    }

    // frees every node
    void clear() {
        if (m_size != 0) {
            free_node(m_root, true);
            m_root = &m_sentinel;
            m_size = 0;
        }
    }
    // a tree changing allocator frees its nodes first
    void setAllocator(IAllocator* allocator) {
        if (m_allocator != allocator) {
            clear();
            m_allocator = allocator;
            init_sentinel();
            m_root = &m_sentinel;
        }
    }

    // the node of key, none without one (each step a `continue`: GfBdatUniqueMotion::getCharaInfo keeps the guard and
    // latch compares apart only with this block order)
    node* find(const key_type& key) const {
        node* n = m_root;
        while (n != &m_sentinel) {
            if (Traits::key(n->value) < key) {
                n = n->right;
                continue;
            }
            if (key < Traits::key(n->value)) {
                n = n->left;
                continue;
            }
            return n;
        }
        return nullptr;
    }

    // the node of value's key: the one there is, else a new one holding value
    node* insert(const value_type& value) {
        node* parent = &m_sentinel;
        node* n = m_root;
        while (n != &m_sentinel) {
            parent = n;
            if (Traits::key(n->value) < Traits::key(value)) {
                n = n->right;
            } else if (Traits::key(value) < Traits::key(n->value)) {
                n = n->left;
            } else {
                return n;
            }
        }
#line 636 MM_MTL_RED_BLACK_TREE_PATH
        MM_ASSERT(m_allocator != 0);
        void* mem = m_allocator->allocate(sizeof(node), 8);
#line 639 MM_MTL_RED_BLACK_TREE_PATH
        MM_ASSERT(mem != 0);
        node* new_node = static_cast<node*>(mem);
        // the element is constructed in place before it is copied in (a FixStr key shows it: the FixStr<32>-keyed
        // instances clear the text and the length first), behind a test of the node as mm_lib's containers test theirs
        if (new_node != nullptr) {
            new (&new_node->value) value_type();
        }
        new_node->color = red;
        new_node->value = value;
        new_node->right = &m_sentinel;
        new_node->left = &m_sentinel;
        new_node->parent = parent;
        if (parent == &m_sentinel) {
            m_root = new_node;
        } else if (Traits::key(value) < Traits::key(parent->value)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        rebalance(new_node);
        ++m_size;
        return new_node;
    }

    void free_node(node* n, bool recursive) {
        if (recursive) {
            if (n->left != &m_sentinel) {
                free_node(n->left, true);
            }
            if (n->right != &m_sentinel) {
                free_node(n->right, true);
            }
        }
        if (n != &m_sentinel) {
#line 661 MM_MTL_RED_BLACK_TREE_PATH
            MM_ASSERT(m_allocator != 0);
            // the node is destroyed only when there is one (the original tests it: framework's ParamManager trees,
            // whose values release a counted reference)
            if (n != nullptr) {
                n->~node();
            }
            m_allocator->deallocate(n);
        }
    }

    void rotate_left(node* x) {
        node* y = x->right;
        x->right = y->left;
        if (x->right != &m_sentinel) {
            x->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == &m_sentinel) {
            m_root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rotate_right(node* x) {
        node* y = x->left;
        x->left = y->right;
        if (x->left != &m_sentinel) {
            x->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == &m_sentinel) {
            m_root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

    void rebalance(node* new_node) {
#line 419 MM_MTL_RED_BLACK_TREE_PATH
        MM_ASSERT(new_node->color == red);
        node* x = new_node;
        while (x->parent->color == red) {
            node* p = x->parent;
            node* g = p->parent;
            if (p == g->left) {
                node* y = g->right;
                if (y->color == red) {
                    p->color = black;
                    y->color = black;
                    g->color = red;
                    x = g;
                } else {
                    if (x == p->right) {
                        x = p;
                        rotate_left(x);
                        p = x->parent;
                        g = p->parent;
                    }
                    p->color = black;
                    g->color = red;
                    rotate_right(g);
                }
            } else {
                node* y = g->left;
                if (y->color == red) {
                    g->color = red;
                    x->parent->color = black;
                    y->color = black;
                    x = g;
                } else {
                    if (x == p->left) {
                        x = p;
                        rotate_right(x);
                        p = x->parent;
                        g = p->parent;
                    }
                    p->color = black;
                    g->color = red;
                    rotate_left(g);
                }
            }
        }
        m_root->color = black;
    }

    // 1.0.0's erase and rebalance_after_erase (GfGameVisible's instances at 0x71002EFD80 and 0x71002EFEC0): CLRS's
    // delete and fixup; erase picks x by address (`*(cond ? &y->right : &y->left)`) and frees y as free_node does
    // z's element taken out: z's node, or its successor's after the successor's element moves into z, unlinked and
    // freed
    void erase(node* z) {
#line 231 MM_MTL_RED_BLACK_TREE_PATH
        MM_ASSERT(m_size > 0);
        node* y;
        if (z->left == &m_sentinel || z->right == &m_sentinel) {
            y = z;
        } else {
            y = z->right;
            while (y->left != &m_sentinel) {
                y = y->left;
            }
        }
        node* x = *(y->left == &m_sentinel ? &y->right : &y->left);
        x->parent = y->parent;
        if (y->parent == &m_sentinel) {
            m_root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        z->value.second = y->value.second;
        z->value.first = y->value.first;
        if (y->color == black) {
            rebalance_after_erase(x);
        }
        free_node(y, false);
        --m_size;
    }
    void rebalance_after_erase(node* x) {
        while (x != m_root && x->color == black) {
            if (x == x->parent->left) {
                node* w = x->parent->right;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == black && w->right->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->right->color == black) {
                        w->left->color = black;
                        w->color = red;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    rotate_left(x->parent);
                    x = m_root;
                }
            } else {
                node* w = x->parent->left;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->left->color == black && w->right->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->left->color == black) {
                        w->right->color = black;
                        w->color = red;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    rotate_right(x->parent);
                    x = m_root;
                }
            }
        }
        x->color = black;
    }

    // the first node in key order, none for an empty tree (GfGameVisible::updateImpl walks its map so)
    node* first() const {
        if (m_size == 0 || m_root == &m_sentinel) {
            return nullptr;
        }
        node* n = m_root;
        while (n->left != &m_sentinel) {
            n = n->left;
        }
        return n;
    }
    // the node after nodePtr in key order, none after the last (red_black_tree.h asserts `nodePtr == m_root` when it
    // climbs past the root; the name is not the original's)
    node* next(node* nodePtr) const {
        node* n = nodePtr->right;
        if (n != &m_sentinel) {
            while (n->left != &m_sentinel) {
                n = n->left;
            }
            return n;
        }
        node* parent = nodePtr->parent;
        if (parent == &m_sentinel) {
#line 363 MM_MTL_RED_BLACK_TREE_PATH
            MM_ASSERT(nodePtr == m_root);
            return nullptr;
        }
        if (parent->left != nodePtr) {
            while (nodePtr == parent->right) {
                nodePtr = parent;
                parent = parent->parent;
                if (parent == &m_sentinel) {
                    return nullptr;
                }
            }
        }
        return parent;
    }

    static void init_sentinel() {
        m_sentinel.color = black;
        m_sentinel.left = m_sentinel.parent = m_sentinel.right = &m_sentinel;
    }

    node* m_root;
    int m_size;
    IAllocator* m_allocator;

    static node m_sentinel;
};

template <typename Traits>
typename RedBlackTreeBase<Traits>::node RedBlackTreeBase<Traits>::m_sentinel;

// mm_lib's map: a red-black tree of MapPairs ordered by their keys
template <typename K, typename V>
class Map {
public:
    template <typename K2, typename V2>
    struct MapTraits {
        typedef K2 key_type;
        typedef MapPair<K2, V2> value_type;
        static const K2& key(const value_type& value) {
            return value.first;
        }
    };
    typedef RedBlackTreeBase<MapTraits<K, V> > tree_type;
    typedef typename tree_type::node node;

    Map() {}
    // an empty map, its nodes from allocator (fw::SoundVariableTable's constructor)
    explicit Map(IAllocator* allocator) : m_tree(allocator) {}

    // a node of the map, none for the end (map.h asserts `m_node != 0` as one is read: GfGameVisible::updateImpl;
    // the names are not the original's)
    class iterator {
    public:
        iterator(node* n) : m_node(n) {}
        MapPair<K, V>* operator->() const {
#line 159 MM_MTL_MAP_PATH
            MM_ASSERT(m_node != 0);
            return &m_node->value;
        }
        node* m_node;
    };
    iterator lookup(const K& key) const {
        return iterator(m_tree.find(key));
    }
    // takes key's element out, if there is one
    void erase(const K& key) {
        if (node* n = m_tree.find(key)) {
            m_tree.erase(n);
        }
    }

    void setAllocator(IAllocator* allocator) {
        m_tree.setAllocator(allocator);
    }
    void clear() {
        m_tree.clear();
    }
    node* find(const K& key) const {
        return m_tree.find(key);
    }
    // value under key, unless key has one already (PadRelay::bindAction inserts an empty handler, then finds it)
    node* insert(const MapPair<K, V>& pair) {
        return m_tree.insert(pair);
    }
    // the value of key, made (V()) when there is none
    V& operator[](const K& key) {
        node* n = m_tree.find(key);
        if (n == nullptr) {
            MapPair<K, V> pair(key, V());
            n = m_tree.insert(pair);
        }
        return n->value.second;
    }

    tree_type m_tree;
};

}}  // namespace mm::mtl

#endif
