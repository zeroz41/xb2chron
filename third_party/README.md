# Third-party code

Almost all of the source is written for this project and is under the [MIT License](../LICENSE). The game also
links some open-source libraries. Where the matching source follows one of these libraries, that library's own licence
applies to those files, and its notice is kept here.

| Library | Files | Licence |
| --- | --- | --- |
| [zlib](https://zlib.net/) 1.2.8 (the copy in NintendoSDK's libz) | `include/zlib/`, `src/unit_71008AA7BC.cpp` (inflate.c, inftrees.c), `src/unit_71008ACC24.cpp` (crc32.c, inffast.c), `src/unit_71008AC858.cpp` (zutil.c, adler32.c) | zlib, [LICENSES/zlib.txt](LICENSES/zlib.txt) |
| [libc++](https://libcxx.llvm.org/) 3.9.1 (the copy in NintendoSDK) | the C++ library headers in `include/` that rebuild its containers: `algorithm`, `bitset`, `chrono`, `condition_variable`, `__config`, `functional`, `__functional_base`, `__hash_table`, `memory`, `stdexcept`, `string`, `unordered_map`, `utility`, `vector` | MIT or University of Illinois/NCSA, [LICENSES/libcxx.txt](LICENSES/libcxx.txt) |
| [MT19937](http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/emt.html) (mt19937ar-cok.c, Matsumoto and Nishimura) | `include/mm/mtl/MTRand.h`, `src/libs/monolib_mm/source/MTRand.cpp` | BSD 3-clause, [LICENSES/mt19937.txt](LICENSES/mt19937.txt) |
| [dlmalloc](https://gee.cs.oswego.edu/dl/html/malloc.html) 2.8.6 (Doug Lea) | `src/libs/monolib_mm/source/mtl/mtl_mem_manager.cpp` | public domain ([CC0](https://creativecommons.org/publicdomain/zero/1.0/)), notice kept in the file |

These files are altered versions, not the original software: each is reduced to what the game links and written so
that it compiles to the game's exact code. Report problems with them here, not to the upstream authors.
