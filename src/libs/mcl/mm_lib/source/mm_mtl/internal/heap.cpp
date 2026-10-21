#include "mm/mtl/HeapAllocUtil.h"
#include <stddef.h>
#include "mm/MMStdBase.h"

namespace mm { namespace mtl { namespace HeapAllocUtil {

// the bit scans, in portable C
inline int heap_fls_generic(unsigned int word) {
    int bit = 32;

    if (!word) bit -= 1;
    if (!(word & 0xffff0000)) { word <<= 16; bit -= 16; }
    if (!(word & 0xff000000)) { word <<= 8; bit -= 8; }
    if (!(word & 0xf0000000)) { word <<= 4; bit -= 4; }
    if (!(word & 0xc0000000)) { word <<= 2; bit -= 2; }
    if (!(word & 0x80000000)) { word <<= 1; bit -= 1; }

    return bit;
}

inline int heap_ffs(unsigned int word) {
    return heap_fls_generic(word & (~word + 1)) - 1;
}

inline int heap_fls(unsigned int word) {
    return heap_fls_generic(word) - 1;
}

inline int heap_fls_sizet(size_t size) {
    int high = (int)(size >> 32);
    int bits = 0;
    if (high) {
        bits = 32 + heap_fls(high);
    } else {
        bits = heap_fls((int)size & 0xffffffff);
    }
    return bits;
}

static const size_t block_header_free_bit = 1 << 0;
static const size_t block_header_prev_free_bit = 1 << 1;
static const size_t block_header_overhead = sizeof(size_t);
static const size_t block_start_offset = offsetof(block_header_t, size) + sizeof(size_t);
static const size_t block_size_min = sizeof(block_header_t) - sizeof(block_header_t*);
static const size_t block_size_max = static_cast<size_t>(1) << FL_INDEX_MAX;

size_t block_size(const block_header_t* block) {
    return block->size & ~(block_header_free_bit | block_header_prev_free_bit);
}

void block_set_size(block_header_t* block, size_t size) {
    const size_t oldsize = block->size;
    block->size = size | (oldsize & (block_header_free_bit | block_header_prev_free_bit));
}

int block_is_last(const block_header_t* block) {
    return block_size(block) == 0;
}

int block_is_free(const block_header_t* block) {
    return static_cast<int>(block->size & block_header_free_bit);
}

void block_set_free(block_header_t* block) {
    block->size |= block_header_free_bit;
}

void block_set_used(block_header_t* block) {
    block->size &= ~block_header_free_bit;
}

int block_is_prev_free(const block_header_t* block) {
    return static_cast<int>(block->size & block_header_prev_free_bit);
}

void block_set_prev_free(block_header_t* block) {
    block->size |= block_header_prev_free_bit;
}

void block_set_prev_used(block_header_t* block) {
    block->size &= ~block_header_prev_free_bit;
}

block_header_t* block_from_ptr(const void* ptr) {
    return (block_header_t*)((unsigned char*)ptr - block_start_offset);
}

void* block_to_ptr(const block_header_t* block) {
    return (void*)((unsigned char*)block + block_start_offset);
}

block_header_t* offset_to_block(const void* ptr, long size) {
    return (block_header_t*)((long)ptr + size);
}

block_header_t* block_prev(const block_header_t* block) {
    return block->prev_phys_block;
}

block_header_t* block_next(const block_header_t* block) {
    block_header_t* next = offset_to_block(block_to_ptr(block), block_size(block) - block_header_overhead);
#line 161
    MM_ASSERT(!block_is_last(block));
    return next;
}

block_header_t* block_link_next(block_header_t* block) {
    block_header_t* next = block_next(block);
    next->prev_phys_block = block;
    return next;
}

void block_mark_as_free(block_header_t* block) {
    block_header_t* next = block_link_next(block);
    block_set_prev_free(next);
    block_set_free(block);
}

void block_mark_as_used(block_header_t* block) {
    block_header_t* next = block_next(block);
    block_set_prev_used(next);
    block_set_used(block);
}

size_t align_up(size_t x, size_t align) {
#line 188
    MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
    return (x + (align - 1)) & ~(align - 1);
}

size_t align_down(size_t x, size_t align) {
#line 194
    MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
    return x - (x & (align - 1));
}

void* align_ptr(const void* ptr, size_t align) {
    const long aligned = ((long)ptr + (align - 1)) & ~(align - 1);
#line 202
    MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
    return (void*)aligned;
}

size_t adjust_request_size(size_t size, size_t align) {
    size_t adjust = 0;
    if (size && size < block_size_max) {
        const size_t aligned = align_up(size, align);
        adjust = aligned > block_size_min ? aligned : block_size_min;
    }
    return adjust;
}

void mapping_insert(size_t size, int* fli, int* sli) {
    int fl, sl;
    if (size < SMALL_BLOCK_SIZE) {
        fl = 0;
        sl = (int)size / (SMALL_BLOCK_SIZE / SL_INDEX_COUNT);
    } else {
        fl = heap_fls_sizet(size);
        sl = (int)(size >> (fl - SL_INDEX_COUNT_LOG2)) ^ (1 << SL_INDEX_COUNT_LOG2);
        fl -= (FL_INDEX_SHIFT - 1);
    }
    *fli = fl;
    *sli = sl;
}

void mapping_search(size_t size, int* fli, int* sli) {
    if (size >= (1 << SL_INDEX_COUNT_LOG2)) {
        const size_t round = (1 << (heap_fls_sizet(size) - SL_INDEX_COUNT_LOG2)) - 1;
        size += round;
    }
    mapping_insert(size, fli, sli);
}

block_header_t* search_suitable_block(control_t* control, int* fli, int* sli) {
    int fl = *fli;
    int sl = *sli;

    unsigned int sl_map = control->sl_bitmap[fl] & (~0 << sl);
    if (!sl_map) {
        const unsigned int fl_map = control->fl_bitmap & (~0 << (fl + 1));
        if (!fl_map) {
            return 0;
        }
        fl = heap_ffs(fl_map);
        *fli = fl;
        sl_map = control->sl_bitmap[fl];
    }
#line 263
    MM_ASSERT(sl_map && "internal error - second level bitmap is null");
    sl = heap_ffs(sl_map);
    *sli = sl;

    return control->blocks[fl][sl];
}

void remove_free_block(control_t* control, block_header_t* block, int fl, int sl) {
    block_header_t* prev = block->prev_free;
    block_header_t* next = block->next_free;
#line 274
    MM_ASSERT(prev && "prev_free field can not be null");
    MM_ASSERT(next && "next_free field can not be null");
    next->prev_free = prev;
    prev->next_free = next;

    if (control->blocks[fl][sl] == block) {
        control->blocks[fl][sl] = next;

        if (next == &control->block_null) {
            control->sl_bitmap[fl] &= ~(1 << sl);

            if (!control->sl_bitmap[fl]) {
                control->fl_bitmap &= ~(1 << fl);
            }
        }
    }
}

void insert_free_block(control_t* control, block_header_t* block, int fl, int sl) {
    block_header_t* current = control->blocks[fl][sl];
#line 298
    MM_ASSERT(current && "free list cannot have a null entry");
    MM_ASSERT(block && "cannot insert a null entry into the free list");
    block->next_free = current;
    block->prev_free = &control->block_null;
    current->prev_free = block;

#line 305
    MM_ASSERT(block_to_ptr(block) == align_ptr(block_to_ptr(block), HeapAllocUtil::ALIGN_SIZE) && "block not aligned properly");
    control->blocks[fl][sl] = block;
    control->fl_bitmap |= (1 << fl);
    control->sl_bitmap[fl] |= (1 << sl);
}

void block_remove(control_t* control, block_header_t* block) {
    int fl, sl;
    mapping_insert(block_size(block), &fl, &sl);
    remove_free_block(control, block, fl, sl);
}

void block_insert(control_t* control, block_header_t* block) {
    int fl, sl;
    mapping_insert(block_size(block), &fl, &sl);
    insert_free_block(control, block, fl, sl);
}

int block_can_split(block_header_t* block, size_t size) {
    return block_size(block) >= sizeof(block_header_t) + size;
}

block_header_t* block_split(block_header_t* block, size_t size) {
    block_header_t* remaining = offset_to_block(block_to_ptr(block), size - block_header_overhead);

    const size_t remain_size = block_size(block) - (size + block_header_overhead);

#line 339
    MM_ASSERT(block_to_ptr(remaining) == align_ptr(block_to_ptr(remaining), HeapAllocUtil::ALIGN_SIZE) && "remaining block not aligned properly");

#line 341
    MM_ASSERT(block_size(block) == remain_size + size + block_header_overhead);
    block_set_size(remaining, remain_size);
#line 343
    MM_ASSERT(block_size(remaining) >= heap_block_size_min() && "block split with invalid size");

    block_set_size(block, size);
    block_mark_as_free(remaining);

    return remaining;
}

block_header_t* block_absorb(block_header_t* prev, block_header_t* block) {
#line 353
    MM_ASSERT(!block_is_last(prev) && "previous block can't be last!");
    prev->size += block_size(block) + block_header_overhead;
    block_link_next(prev);
    return prev;
}

block_header_t* block_merge_prev(control_t* control, block_header_t* block) {
    if (block_is_prev_free(block)) {
        block_header_t* prev = block_prev(block);
#line 365
        MM_ASSERT(prev && "prev physical block can't be null");
        MM_ASSERT(block_is_free(prev) && "prev block is not free though marked as such");
        block_remove(control, prev);
        block = block_absorb(prev, block);
    }

    return block;
}

block_header_t* block_merge_next(control_t* control, block_header_t* block) {
    block_header_t* next = block_next(block);
#line 377
    MM_ASSERT(next && "next physical block can't be null");

    if (block_is_free(next)) {
#line 381
        MM_ASSERT(!block_is_last(block) && "previous block can't be last!");
        block_remove(control, next);
        block = block_absorb(block, next);
    }

    return block;
}

void block_trim_free(control_t* control, block_header_t* block, size_t size) {
#line 391
    MM_ASSERT(block_is_free(block) && "block must be free");
    if (block_can_split(block, size)) {
        block_header_t* remaining_block = block_split(block, size);
        block_link_next(block);
        block_set_prev_free(remaining_block);
        block_insert(control, remaining_block);
    }
}

block_header_t* block_trim_free_leading(control_t* control, block_header_t* block, size_t size) {
    block_header_t* remaining_block = block;
    if (block_can_split(block, size)) {
        remaining_block = block_split(block, size - block_header_overhead);
        block_set_prev_free(remaining_block);

        block_link_next(block);
        block_insert(control, block);
    }

    return remaining_block;
}

block_header_t* block_locate_free(control_t* control, size_t size) {
    int fl = 0, sl = 0;
    block_header_t* block = 0;

    if (size) {
        mapping_search(size, &fl, &sl);
        block = search_suitable_block(control, &fl, &sl);
    }

    if (block) {
#line 442
        MM_ASSERT(block_size(block) >= size);
        remove_free_block(control, block, fl, sl);
    }

    return block;
}

void* block_prepare_used(control_t* control, block_header_t* block, size_t size) {
    void* p = 0;
    if (block) {
        block_trim_free(control, block, size);
        block_mark_as_used(block);
        p = block_to_ptr(block);
    }
    return p;
}

void control_construct(control_t* control) {
    int i, j;

    control->block_null.next_free = &control->block_null;
    control->block_null.prev_free = &control->block_null;

    control->fl_bitmap = 0;
    for (i = 0; i < FL_INDEX_COUNT; ++i) {
        control->sl_bitmap[i] = 0;
        for (j = 0; j < SL_INDEX_COUNT; ++j) {
            control->blocks[i][j] = &control->block_null;
        }
    }
}

size_t heap_block_size_min() {
    return block_size_min;
}

size_t heap_block_size_max() {
    return block_size_max;
}

size_t heap_pool_overhead() {
    return 2 * block_header_overhead;
}

void* heap_add_pool(void* heap, void* mem, size_t bytes) {
    block_header_t* block;
    block_header_t* next;

    const size_t pool_overhead = heap_pool_overhead();
    const size_t pool_bytes = align_down(bytes - pool_overhead, ALIGN_SIZE);

    if (((long)mem % ALIGN_SIZE) != 0) {
        MMStdBase::mmPrint("heap_add_pool: Memory must be aligned by %u bytes.\n", (unsigned int)ALIGN_SIZE);
        return 0;
    }

    if (pool_bytes < block_size_min || pool_bytes > block_size_max) {
        MMStdBase::mmPrint("heap_add_pool: Memory size must be between 0x%x and 0x%x00 bytes.\n",
                           (unsigned int)(pool_overhead + block_size_min),
                           (unsigned int)((pool_overhead + block_size_max) / 256));
        return 0;
    }

    block = offset_to_block(mem, -(long)block_header_overhead);
    block_set_size(block, pool_bytes);
    block_set_free(block);
    block_set_prev_used(block);
    block_insert((control_t*)heap, block);

    next = block_link_next(block);
    block_set_size(next, 0);
    block_set_used(next);
    block_set_prev_free(next);

    return mem;
}

void heap_remove_pool(void* heap, void* pool) {
    control_t* control = (control_t*)heap;
    block_header_t* block = offset_to_block(pool, -(int)block_header_overhead);

    int fl = 0, sl = 0;

#line 692
    MM_ASSERT(block_is_free(block) && "block should be free");
    MM_ASSERT(!block_is_free(block_next(block)) && "next block should not be free");
    MM_ASSERT(block_size(block_next(block)) == 0 && "next block size should be zero");

    mapping_insert(block_size(block), &fl, &sl);
    remove_free_block(control, block, fl, sl);
}

void* heap_create(void* mem) {
    if (((long)mem % ALIGN_SIZE) != 0) {
        MMStdBase::mmPrint("heap_create: Memory must be aligned to %u bytes.\n", (unsigned int)ALIGN_SIZE);
        return 0;
    }

    control_construct((control_t*)mem);

    return mem;
}

void heap_destroy(void* heap) {
    (void)heap;
}

void* heap_malloc(void* heap, size_t size) {
    control_t* control = (control_t*)heap;
    const size_t adjust = adjust_request_size(size, ALIGN_SIZE);
    block_header_t* block = block_locate_free(control, adjust);
    return block_prepare_used(control, block, adjust);
}

void* heap_memalign(void* heap, size_t align, size_t size) {
    control_t* control = (control_t*)heap;
    const size_t adjust = adjust_request_size(size, ALIGN_SIZE);

    const size_t gap_minimum = sizeof(block_header_t);
    const size_t size_with_gap = adjust_request_size(adjust + align + gap_minimum, align);

    const size_t aligned_size = (align <= ALIGN_SIZE) ? adjust : size_with_gap;

    block_header_t* block = block_locate_free(control, aligned_size);

    if (block) {
        void* ptr = block_to_ptr(block);
        void* aligned = align_ptr(ptr, align);
        size_t gap = (size_t)((long)aligned - (long)ptr);

        if (gap && gap < gap_minimum) {
            const size_t gap_remain = gap_minimum - gap;
            const size_t offset = gap_remain > align ? gap_remain : align;
            const void* next_aligned = (void*)((long)aligned + offset);

            aligned = align_ptr(next_aligned, align);
            gap = (size_t)((long)aligned - (long)ptr);
        }

        if (gap) {
#line 802
            MM_ASSERT(gap >= gap_minimum && "gap size too small");
            block = block_trim_free_leading(control, block, gap);
        }
    }

    return block_prepare_used(control, block, adjust);
}

void heap_free(void* heap, void* ptr) {
    if (ptr) {
        control_t* control = (control_t*)heap;
        block_header_t* block = block_from_ptr(ptr);
#line 817
        MM_ASSERT(!block_is_free(block) && "block already marked as free");
        block_mark_as_free(block);
        block = block_merge_prev(control, block);
        block = block_merge_next(control, block);
        block_insert(control, block);
    }
}

}}}  // namespace mm::mtl::HeapAllocUtil
