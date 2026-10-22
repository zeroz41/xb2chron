#ifndef WND_QUERY_H
#define WND_QUERY_H

#include "mm/mtl/RTTI.h"

namespace wnd {
// what BroadPhazeOctree::query answers: it asks the query's type through slot 0 and fills an AreaQuery. The
// classes' tables are not in the update; their m_rtti are wnd_probe.cpp's.
class Query {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0

    static mm::mtl::RTTI m_rtti;
};

class AreaWindQuery : public Query {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0

    static mm::mtl::RTTI m_rtti;
};

class LocalWindQuery : public Query {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0

    static mm::mtl::RTTI m_rtti;
};

class ProbeQuery : public Query {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0

    static mm::mtl::RTTI m_rtti;
};

// BroadPhazeOctree::query gives it the octree's areas
class AreaQuery : public Query {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0

    static mm::mtl::RTTI m_rtti;
};
}  // namespace wnd

#endif
