#ifndef ZLIB_ZLIB_H
#define ZLIB_ZLIB_H

// zlib (NintendoSDK's libz 3.5.0, zlib 1.2.x), as far as the module links it: C functions (their names are C names).
// The types and names are zlib's own.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef void* voidpf;
typedef unsigned z_crc_t;  // zconf.h: Z_U4 (a 4-byte unsigned) on this target
typedef long z_off_t;
typedef long z_off64_t;

#define ZLIB_VERSION "1.2.8.f-NINTENDO-SDK-v1"
#define MAX_WBITS 15 /* 32K LZ77 window */

typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef* next_in;  /* next input byte */
    uInt avail_in;   /* number of bytes available at next_in */
    uLong total_in;  /* total number of input bytes read so far */

    Bytef* next_out; /* next output byte should be put there */
    uInt avail_out;  /* remaining free space at next_out */
    uLong total_out; /* total number of bytes output so far */

    char* msg;                    /* last error message, NULL if no error */
    struct internal_state* state; /* not visible by applications */

    alloc_func zalloc; /* used to allocate the internal state */
    free_func zfree;   /* used to free the internal state */
    voidpf opaque;     /* private data object passed to zalloc and zfree */

    int data_type;  /* best guess about the data type: binary or text */
    uLong adler;    /* adler32 value of the uncompressed data */
    uLong reserved; /* reserved for future use */
} z_stream;

typedef z_stream* z_streamp;

typedef struct gz_header_s {
    int text;       /* true if compressed data believed to be text */
    uLong time;     /* modification time */
    int xflags;     /* extra flags (not used when writing a gzip file) */
    int os;         /* operating system */
    Bytef* extra;   /* pointer to extra field or Z_NULL if none */
    uInt extra_len; /* extra field length (valid if extra != Z_NULL) */
    uInt extra_max; /* space at extra (only when reading header) */
    Bytef* name;    /* pointer to zero-terminated file name or Z_NULL */
    uInt name_max;  /* space at name (only when reading header) */
    Bytef* comment; /* pointer to zero-terminated comment or Z_NULL */
    uInt comm_max;  /* space at comment (only when reading header) */
    int hcrc;       /* true if there was or will be a header crc */
    int done;       /* true when done reading gzip header */
} gz_header;

typedef gz_header* gz_headerp;

#define Z_NO_FLUSH 0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH 2
#define Z_FULL_FLUSH 3
#define Z_FINISH 4
#define Z_BLOCK 5
#define Z_TREES 6

#define Z_OK 0
#define Z_STREAM_END 1
#define Z_NEED_DICT 2
#define Z_ERRNO (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR (-3)
#define Z_MEM_ERROR (-4)
#define Z_BUF_ERROR (-5)
#define Z_VERSION_ERROR (-6)

#define Z_DEFLATED 8

#define Z_NULL 0

int inflateInit_(z_streamp strm, const char* version, int stream_size);
int inflateInit2_(z_streamp strm, int windowBits, const char* version, int stream_size);
#define inflateInit(strm) inflateInit_((strm), ZLIB_VERSION, (int)sizeof(z_stream))
#define inflateInit2(strm, windowBits) inflateInit2_((strm), (windowBits), ZLIB_VERSION, (int)sizeof(z_stream))
int inflate(z_streamp strm, int flush);
int inflateEnd(z_streamp strm);
int inflateSetDictionary(z_streamp strm, const Bytef* dictionary, uInt dictLength);
int inflateGetDictionary(z_streamp strm, Bytef* dictionary, uInt* dictLength);
int inflateSync(z_streamp strm);
int inflateCopy(z_streamp dest, z_streamp source);
int inflateReset(z_streamp strm);
int inflateReset2(z_streamp strm, int windowBits);
int inflatePrime(z_streamp strm, int bits, int value);
long inflateMark(z_streamp strm);
int inflateGetHeader(z_streamp strm, gz_headerp head);
int inflateResetKeep(z_streamp strm);
int inflateSyncPoint(z_streamp strm);
int inflateUndermine(z_streamp strm, int subvert);

uLong crc32(uLong crc, const Bytef* buf, uInt len);
uLong crc32_combine(uLong crc1, uLong crc2, z_off_t len2);
uLong crc32_combine64(uLong crc1, uLong crc2, z_off64_t len2);
const z_crc_t* get_crc_table(void);

uLong adler32(uLong adler, const Bytef* buf, uInt len);

// zutil.c's default allocator (zlib's internal functions)
voidpf zcalloc(voidpf opaque, unsigned items, unsigned size);
void zcfree(voidpf opaque, voidpf ptr);

// NintendoSDK's middleware marker: refers to the library's version string so the linker keeps it
void Libz_SigloMiddlewareInfo(void);

#ifdef __cplusplus
}
#endif

#endif
