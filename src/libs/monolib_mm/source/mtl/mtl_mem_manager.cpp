#define MM_LIB_FROM_MONOLIB_MM
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "mtl/MemManagerRegion.h"
#include "ml/CriticalSection.h"
#include "classes/mtl/IMemAllocator.h"
#include "classes/mtl/DlAllocator.h"
#include "classes/mtl/NullAllocator.h"
#include "classes/mtl/MemHandlebaseAllocator.h"
#include "classes/mtl/AssetAllocator.h"
#include "classes/mm/mtl/HeapAllocator.h"
#include <new>
#include <stdlib.h>

// ---- dlmalloc 2.8.6 (Doug Lea, public domain), compiled as C++ inside this file ----
// The original #included "source\mtl/dlmalloc.inl" here (its assert path is in this unit's .rodata). Its
// configuration, read from the code: ONLY_MSPACES, USE_LOCKS 0, no MMAP/MORECORE, FOOTERS 1, granularity
// 64KiB, page 4KiB, the magic from the constant 123456789 instead of time(0). Only the parts the matched functions
// use are written so far; the rest (mspace_malloc, mspace_free, ...) follows stock 2.8.6.
#include <stddef.h>
#include <string.h>

#define FOOTERS 1
#define MALLOC_ALIGNMENT ((size_t)16U)
#define MAX_SIZE_T           (~(size_t)0)
#define DEFAULT_GRANULARITY ((size_t)64U * (size_t)1024U)
#define DEFAULT_TRIM_THRESHOLD ((size_t)2U * (size_t)1024U * (size_t)1024U)
#define DEFAULT_MMAP_THRESHOLD MAX_SIZE_T
#define MAX_RELEASE_CHECK_RATE MAX_SIZE_T
#define malloc_getpagesize ((size_t)4096U)

extern "C" {
typedef void* mspace;
mspace create_mspace_with_base(void* base, size_t capacity, int locked);
size_t mspace_usable_size(const void* mem);
}

#define SIZE_T_SIZE         (sizeof(size_t))
#define SIZE_T_ONE          ((size_t)1)
#define SIZE_T_TWO          ((size_t)2)
#define SIZE_T_FOUR         ((size_t)4)
#define TWO_SIZE_T_SIZES    (SIZE_T_SIZE<<1)
#define CHUNK_ALIGN_MASK    (MALLOC_ALIGNMENT - SIZE_T_ONE)
#define align_offset(A)\
 ((((size_t)(A) & CHUNK_ALIGN_MASK) == 0)? 0 :\
  ((MALLOC_ALIGNMENT - ((size_t)(A) & CHUNK_ALIGN_MASK)) & CHUNK_ALIGN_MASK))

#define USE_NONCONTIGUOUS_BIT (4U)
#define EXTERN_BIT            (8U)
#define USE_LOCK_BIT               (0U)
#define INITIAL_LOCK(l)            (0)
#define ACQUIRE_MALLOC_GLOBAL_LOCK()
#define RELEASE_MALLOC_GLOBAL_LOCK()

struct malloc_chunk {
  size_t               prev_foot;  /* Size of previous chunk (if free).  */
  size_t               head;       /* Size and inuse bits. */
  struct malloc_chunk* fd;         /* double links -- used only if free. */
  struct malloc_chunk* bk;
};

typedef struct malloc_chunk  mchunk;
typedef struct malloc_chunk* mchunkptr;
typedef struct malloc_chunk* sbinptr;  /* The type of bins of chunks */
typedef unsigned int bindex_t;         /* Described below */
typedef unsigned int binmap_t;         /* Described below */
typedef unsigned int flag_t;           /* The type of various bit flag sets */

#define MCHUNK_SIZE         (sizeof(mchunk))
#define CHUNK_OVERHEAD      (TWO_SIZE_T_SIZES)
#define MMAP_CHUNK_OVERHEAD (TWO_SIZE_T_SIZES)
#define MIN_CHUNK_SIZE\
  ((MCHUNK_SIZE + CHUNK_ALIGN_MASK) & ~CHUNK_ALIGN_MASK)
#define chunk2mem(p)        ((void*)((char*)(p)       + TWO_SIZE_T_SIZES))
#define mem2chunk(mem)      ((mchunkptr)((char*)(mem) - TWO_SIZE_T_SIZES))
#define align_as_chunk(A)   (mchunkptr)((A) + align_offset(chunk2mem(A)))
#define pad_request(req) \
   (((req) + CHUNK_OVERHEAD + CHUNK_ALIGN_MASK) & ~CHUNK_ALIGN_MASK)

#define PINUSE_BIT          (SIZE_T_ONE)
#define CINUSE_BIT          (SIZE_T_TWO)
#define FLAG4_BIT           (SIZE_T_FOUR)
#define INUSE_BITS          (PINUSE_BIT|CINUSE_BIT)
#define FLAG_BITS           (PINUSE_BIT|CINUSE_BIT|FLAG4_BIT)
#define FENCEPOST_HEAD      (INUSE_BITS|SIZE_T_SIZE)
#define is_inuse(p)         (((p)->head & INUSE_BITS) != PINUSE_BIT)
#define is_mmapped(p)       (((p)->head & INUSE_BITS) == 0)
#define chunksize(p)        ((p)->head & ~(FLAG_BITS))
#define chunk_plus_offset(p, s)  ((mchunkptr)(((char*)(p)) + (s)))
#define next_chunk(p) ((mchunkptr)( ((char*)(p)) + ((p)->head & ~FLAG_BITS)))
#define overhead_for(p)\
 (is_mmapped(p)? MMAP_CHUNK_OVERHEAD : CHUNK_OVERHEAD)

struct malloc_tree_chunk {
  /* The first four fields must be compatible with malloc_chunk */
  size_t                    prev_foot;
  size_t                    head;
  struct malloc_tree_chunk* fd;
  struct malloc_tree_chunk* bk;

  struct malloc_tree_chunk* child[2];
  struct malloc_tree_chunk* parent;
  bindex_t                  index;
};

typedef struct malloc_tree_chunk  tchunk;
typedef struct malloc_tree_chunk* tchunkptr;
typedef struct malloc_tree_chunk* tbinptr; /* The type of bins of trees */

struct malloc_segment {
  char*        base;             /* base address */
  size_t       size;             /* allocated size */
  struct malloc_segment* next;   /* ptr to next segment */
  flag_t       sflags;           /* mmap and extern flag */
};

typedef struct malloc_segment  msegment;
typedef struct malloc_segment* msegmentptr;

#define NSMALLBINS        (32U)
#define NTREEBINS         (32U)

struct malloc_state {
  binmap_t   smallmap;
  binmap_t   treemap;
  size_t     dvsize;
  size_t     topsize;
  char*      least_addr;
  mchunkptr  dv;
  mchunkptr  top;
  size_t     trim_check;
  size_t     release_checks;
  size_t     magic;
  mchunkptr  smallbins[(NSMALLBINS+1)*2];
  tbinptr    treebins[NTREEBINS];
  size_t     footprint;
  size_t     max_footprint;
  size_t     footprint_limit; /* zero means no limit */
  flag_t     mflags;
  msegment   seg;
  void*      extp;      /* Unused but available for extensions */
  size_t     exts;
};

typedef struct malloc_state*    mstate;

struct malloc_params {
  size_t magic;
  size_t page_size;
  size_t granularity;
  size_t mmap_threshold;
  size_t trim_threshold;
  flag_t default_mflags;
};

static struct malloc_params mparams;

/* Ensure mparams initialized */
#define ensure_initialization() (void)(mparams.magic != 0 || init_mparams())

#define is_initialized(M)  ((M)->top != 0)
#define disable_contiguous(M) ((M)->mflags |=  USE_NONCONTIGUOUS_BIT)
#define set_lock(M,L)\
 ((M)->mflags = (L)?\
  ((M)->mflags | USE_LOCK_BIT) :\
  ((M)->mflags & ~USE_LOCK_BIT))
#define segment_holds(S, A)\
  ((char*)(A) >= S->base && (char*)(A) < S->base + S->size)
#define TOP_FOOT_SIZE\
  (align_offset(TWO_SIZE_T_SIZES)+pad_request(sizeof(struct malloc_segment))+MIN_CHUNK_SIZE)
#define check_top_chunk(M,P)
#define smallbin_at(M, i)   ((sbinptr)((char*)&((M)->smallbins[(i)<<1])))
#define ok_magic(M)      ((M)->magic == mparams.magic)

static int init_mparams(void) {
  ACQUIRE_MALLOC_GLOBAL_LOCK();
  if (mparams.magic == 0) {
    size_t magic;
    size_t psize;
    size_t gsize;

    psize = malloc_getpagesize;
    gsize = ((DEFAULT_GRANULARITY != 0)? DEFAULT_GRANULARITY : psize);

    /* Sanity-check configuration */
    if ((sizeof(size_t) != sizeof(char*)) ||
        (MAX_SIZE_T < MIN_CHUNK_SIZE)  ||
        (sizeof(int) < 4)  ||
        (MALLOC_ALIGNMENT < (size_t)8U) ||
        ((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT-SIZE_T_ONE)) != 0) ||
        ((MCHUNK_SIZE      & (MCHUNK_SIZE-SIZE_T_ONE))      != 0) ||
        ((gsize            & (gsize-SIZE_T_ONE))            != 0) ||
        ((psize            & (psize-SIZE_T_ONE))            != 0))
      ;
    mparams.granularity = gsize;
    mparams.page_size = psize;
    mparams.mmap_threshold = DEFAULT_MMAP_THRESHOLD;
    mparams.trim_threshold = DEFAULT_TRIM_THRESHOLD;
    mparams.default_mflags = USE_LOCK_BIT|USE_NONCONTIGUOUS_BIT;

    {
      magic = (size_t)(123456789 ^ (size_t)0x55555555U);
      magic |= (size_t)8U;    /* ensure nonzero */
      magic &= ~(size_t)7U;   /* improve chances of fault for bad values */
      /* Until memory modes commonly available, use volatile-write */
      (*(volatile size_t *)(&(mparams.magic))) = magic;
    }
  }

  RELEASE_MALLOC_GLOBAL_LOCK();
  return 1;
}

static void init_top(mstate m, mchunkptr p, size_t psize) {
  /* Ensure alignment */
  size_t offset = align_offset(chunk2mem(p));
  p = (mchunkptr)((char*)p + offset);
  psize -= offset;

  m->top = p;
  m->topsize = psize;
  p->head = psize | PINUSE_BIT;
  /* set size of fake trailing chunk holding overhead space only once */
  chunk_plus_offset(p, psize)->head = TOP_FOOT_SIZE;
  m->trim_check = mparams.trim_threshold; /* reset on each update */
}

/* Initialize bins for a new mstate that is otherwise zeroed out */
static void init_bins(mstate m) {
  /* Establish circular links for smallbins */
  bindex_t i;
  for (i = 0; i < NSMALLBINS; ++i) {
    sbinptr bin = smallbin_at(m,i);
    bin->fd = bin->bk = bin;
  }
}

// what a new mstate's extp points at until mspace_set_stats names it
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009CEBA0); 4 zero bytes, type inferred
static const char s_noStatsName[4] = "";

static mstate init_user_mstate(char* tbase, size_t tsize) {
  size_t msize = pad_request(sizeof(struct malloc_state));
  mchunkptr mn;
  mchunkptr msp = align_as_chunk(tbase);
  mstate m = (mstate)(chunk2mem(msp));
  memset(m, 0, msize);
  (void)INITIAL_LOCK(&m->mutex);
  msp->head = (msize|INUSE_BITS);
  m->seg.base = m->least_addr = tbase;
  m->seg.size = m->footprint = m->max_footprint = tsize;
  m->magic = mparams.magic;
  m->release_checks = MAX_RELEASE_CHECK_RATE;
  m->mflags = mparams.default_mflags;
  m->extp = (void*)s_noStatsName;
  m->exts = 0;
  disable_contiguous(m);
  init_bins(m);
  mn = next_chunk(mem2chunk(m));
  init_top(m, mn, (size_t)((tbase + tsize) - (char*)mn) - TOP_FOOT_SIZE);
  check_top_chunk(m, m->top);
  return m;
}

mspace create_mspace_with_base(void* base, size_t capacity, int locked) {
  mstate m = 0;
  size_t msize;
  ensure_initialization();
  msize = pad_request(sizeof(struct malloc_state));
  if (capacity > msize + TOP_FOOT_SIZE &&
      capacity < (size_t) -(msize + TOP_FOOT_SIZE + mparams.page_size)) {
    m = init_user_mstate((char*)base, capacity);
    m->seg.sflags = EXTERN_BIT;
    set_lock(m, locked);
  }
  return (mspace)m;
}

// 3.0.1's linker dropped it (inlined in DlAllocator::getNewInfo)
size_t mspace_usable_size(const void* mem) {
  if (mem != 0) {
    mchunkptr p = mem2chunk(mem);
    if (is_inuse(p))
      return chunksize(p) - overhead_for(p);
  }
  return 0;
}

// not in stock dlmalloc: names the mspace in extp (1.0.0 symbol _Z16mspace_set_statsPvPKc, C++ linkage; 3.0.1 inlines it)
void mspace_set_stats(mspace msp, const char* name) {
  mstate ms = (mstate)msp;
  if (ms != 0 && ok_magic(ms)) {
    ms->extp = (void*)((name != 0) ? name : "no name");
  }
}

// ---- end of dlmalloc ----

namespace mtl {

// the heap createAllocator makes the allocators in
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100ED26D0)
static mm::mtl::HeapAllocator s_allocatorHeap;

mm::mtl::FixedVector<MemManager::HandleRegion, 512> MemManager::_existHandle;

DlAllocator::~DlAllocator() {}

}  // namespace mtl

void operator delete(void* p) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

namespace mtl {

void DlAllocator::create(void* p, unsigned long size, const char* pszName) {
    m_name = pszName;
    m_mspace = nullptr;
    m_base = p;
    m_size = size;
    if (p != nullptr) {
        m_mspace = create_mspace_with_base(p, size, 0);
        mspace_set_stats(m_mspace, pszName);
    }
}

void DlAllocator::destroy() {
    m_mspace = nullptr;
    m_base = nullptr;
    m_size = 0;
}

void* DlAllocator::allocate(unsigned long size, unsigned long alignment) {
    return allocate(size, 16, "no name", 0);
}

const char* DlAllocator::getName() const {
    return m_name.m_str;
}

bool DlAllocator::hasMemory(const void* p) const {
    bool result = false;
    if (m_mspace != nullptr && p != nullptr) {
        mstate ms = static_cast<mstate>(m_mspace);
        if (!ok_magic(ms)) {
            return false;
        }
        ensure_initialization();
        if (!is_initialized(ms)) {
            return false;
        }
        for (msegmentptr s = &ms->seg; s != 0; s = s->next) {
            mchunkptr q = align_as_chunk(s->base);
            while ((char*)q >= s->base && q != ms->top && (char*)q < s->base + s->size &&
                   q->head != FENCEPOST_HEAD) {
                void* mem = chunk2mem(q);
                q = next_chunk(q);
                if (mem == p) {
                    return true;
                }
            }
        }
    }
    return result;
}

ALLOC_HANDLE MemManager::create(void* p, unsigned long size, const char* name, bool flag) {
    return create(p, size, name, flag, static_cast<AllocatorType>(1));
}

ALLOC_HANDLE MemManager::create(ALLOC_HANDLE parent, unsigned long size, const char* name, bool flag, const char* file,
                                int line) {
    return create(parent, size, name, flag, static_cast<AllocatorType>(1), 16, file, line);
}

void MemManager::deallocate(void* p, unsigned long size, bool flag) {
    if (s_bInitialize) {
        deallocate_section(p, size, flag);
    }
}

IMemAllocator* MemManager::createAllocator(AllocatorType type) {
    IMemAllocator* allocator = nullptr;
    switch (type) {
    case 1:
        allocator = new (s_allocatorHeap.allocate(sizeof(DlAllocator), 8)) DlAllocator();
        break;
    case 2:
        allocator = new (s_allocatorHeap.allocate(sizeof(AssetAllocator<1024>), 8)) AssetAllocator<1024>();
        break;
    case 0:
        allocator = new (s_allocatorHeap.allocate(sizeof(NullAllocator), 8)) NullAllocator();
        break;
    }
    return allocator;
}

void* MemHandlebaseAllocator::allocate(unsigned long size, unsigned long alignment) {
#line 1906
    return MemManager::allocate(m_handle, size, alignment, false, __FILE__, __LINE__);
}

void MemHandlebaseAllocator::deallocate(void* memory) {
    MemManager::deallocate(memory, 0, false);
}

}  // namespace mtl

void* operator new(unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                   bool flag) {
    return mtl::MemManager::allocate(handle, static_cast<int>(size), alignment, flag, file, line);
}

void* operator new[](unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                     bool flag) {
    return mtl::MemManager::allocate(handle, static_cast<int>(size), alignment, flag, file, line);
}

void* operator new(unsigned long size) {
    return malloc(size);
}

void* operator new[](unsigned long size) {
    return malloc(size);
}

void operator delete[](void* p) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

void operator delete(void* p, const std::nothrow_t&) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

void operator delete[](void* p, const std::nothrow_t&) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

namespace mtl {

IMemAllocator::~IMemAllocator() {}

}  // namespace mtl

namespace mtl {

void MemManager::setHaltAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_HALT_ALLOC : region->m_flags | Region::FLAG_HALT_ALLOC;
    }
}

void MemManager::setWarnAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_WARN_ALLOC : region->m_flags | Region::FLAG_WARN_ALLOC;
    }
}

void MemManager::setLogAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_LOG_ALLOC : region->m_flags | Region::FLAG_LOG_ALLOC;
    }
}

}  // namespace mtl
