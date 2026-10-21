#ifndef MM_MTL_HEAPALLOCUTIL_H
#define MM_MTL_HEAPALLOCUTIL_H

namespace mm { namespace mtl {

// mm_lib's port of TLSF 3.0 (two-level segregated fit, Matthew Conte): a control block managing pools of memory.
// The tlsf_ functions are heap_ here; the original's internal helpers are the namespace's functions too.
namespace HeapAllocUtil {

enum {
    SL_INDEX_COUNT_LOG2 = 5,  // log2 of the number of second-level lists per first-level one
};

enum {
    ALIGN_SIZE_LOG2 = 3,  // 64-bit: blocks are 8-aligned
    ALIGN_SIZE = (1 << ALIGN_SIZE_LOG2),
    FL_INDEX_MAX = 32,  // 64-bit: pools up to 4 GiB
    SL_INDEX_COUNT = (1 << SL_INDEX_COUNT_LOG2),
    FL_INDEX_SHIFT = (SL_INDEX_COUNT_LOG2 + ALIGN_SIZE_LOG2),
    FL_INDEX_COUNT = (FL_INDEX_MAX - FL_INDEX_SHIFT + 1),
    SMALL_BLOCK_SIZE = (1 << FL_INDEX_SHIFT),
};

// a block's header: its size carries two flags in its low bits (free, previous free)
struct block_header_t {
    block_header_t* prev_phys_block;  // only valid while the previous block is free
    unsigned long size;
    block_header_t* next_free;  // only valid while this block is free
    block_header_t* prev_free;
};

// the heap: an empty list's sentinel, the bitmaps of non-empty lists and the lists' heads
struct control_t {
    block_header_t block_null;
    unsigned int fl_bitmap;
    unsigned int sl_bitmap[FL_INDEX_COUNT];
    block_header_t* blocks[FL_INDEX_COUNT][SL_INDEX_COUNT];
};

unsigned long block_size(const block_header_t* block);
void block_set_size(block_header_t* block, unsigned long size);
int block_is_last(const block_header_t* block);
int block_is_free(const block_header_t* block);
void block_set_free(block_header_t* block);
void block_set_used(block_header_t* block);
int block_is_prev_free(const block_header_t* block);
void block_set_prev_free(block_header_t* block);
void block_set_prev_used(block_header_t* block);
block_header_t* block_from_ptr(const void* ptr);
void* block_to_ptr(const block_header_t* block);
block_header_t* offset_to_block(const void* ptr, long size);
block_header_t* block_prev(const block_header_t* block);
block_header_t* block_next(const block_header_t* block);
block_header_t* block_link_next(block_header_t* block);
void block_mark_as_free(block_header_t* block);
void block_mark_as_used(block_header_t* block);
unsigned long align_up(unsigned long x, unsigned long align);
unsigned long align_down(unsigned long x, unsigned long align);
void* align_ptr(const void* ptr, unsigned long align);
unsigned long adjust_request_size(unsigned long size, unsigned long align);
void mapping_insert(unsigned long size, int* fli, int* sli);
void mapping_search(unsigned long size, int* fli, int* sli);
block_header_t* search_suitable_block(control_t* control, int* fli, int* sli);
void remove_free_block(control_t* control, block_header_t* block, int fl, int sl);
void insert_free_block(control_t* control, block_header_t* block, int fl, int sl);
void block_remove(control_t* control, block_header_t* block);
void block_insert(control_t* control, block_header_t* block);
int block_can_split(block_header_t* block, unsigned long size);
block_header_t* block_split(block_header_t* block, unsigned long size);
block_header_t* block_absorb(block_header_t* prev, block_header_t* block);
block_header_t* block_merge_prev(control_t* control, block_header_t* block);
block_header_t* block_merge_next(control_t* control, block_header_t* block);
void block_trim_free(control_t* control, block_header_t* block, unsigned long size);
block_header_t* block_trim_free_leading(control_t* control, block_header_t* block, unsigned long size);
block_header_t* block_locate_free(control_t* control, unsigned long size);
void* block_prepare_used(control_t* control, block_header_t* block, unsigned long size);
void control_construct(control_t* control);
unsigned long heap_block_size_min();
unsigned long heap_block_size_max();
unsigned long heap_pool_overhead();

void* heap_create(void* memory);
void heap_destroy(void* heap);
void* heap_add_pool(void* heap, void* memory, unsigned long bytes);
void heap_remove_pool(void* heap, void* pool);
void* heap_malloc(void* heap, unsigned long size);
void* heap_memalign(void* heap, unsigned long alignment, unsigned long size);
void heap_free(void* heap, void* memory);

}  // namespace HeapAllocUtil

}}  // namespace mm::mtl

#endif
