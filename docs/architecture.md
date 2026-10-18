# Architecture

## The executable

Xenoblade Chronicles 2 1.0.0 ships its code as four modules in the ExeFS. This project decompiles `main`, the
game itself; the others are Nintendo's and stay as they are.

| Module | Contents |
|---|---|
| `main` | the game, Monolith Soft's libraries, inlined libc++ templates |
| `sdk` | NintendoSDK 3.5.0: nnSdk, NVN, libz |
| `subsdk0` | NintendoSDK 3.5.0 movie playback |
| `rtld` | the dynamic loader |

`main` (build id `5087af2917d85858a0fd49cb4d6eed67`) loads at `0x7100000000`:

| Section | Range |
|---|---|
| `.text` | `0x0000000`–`0x09BD3D0` |
| `.rodata` | `0x09BE000`–`0x1170033` |
| `.data` | `0x1171000`–`0x11C88E8` |
| `.bss` | `0x11C88E8`–`0x1BDB000` |

It calls the SDK through 792 imports. It exports almost every symbol it defines, so 49,128 of its 49,907
functions and 5,221 data objects (2,845 of them vtables) carry their original mangled names, listed in
[`config/XC2_100/symbols.txt`](../config/XC2_100/symbols.txt). It was built without
RTTI and without exceptions, but with unwind tables for every function.

## Source layout

The game's assertions name their source files, as built on Monolith Soft's machines under
`C:/MonolithSoft/BF2/prog/` (BF2 is the game's internal name). Units keep that layout, relative to `prog/`:

- `application/BF2/`: the game. `gf/` (game framework: objects, menus, fields, data), `ui/`, `framework/`,
  `battle/`, `execute/`, `minigame/`, `plugin/`.
- `libs/`: Monolith Soft's libraries. `monolib_mm` (`ml`), `mcl/mm_lib` (`mm`: math, containers, threads),
  `anmlib` (animation), `eflib` (effects), `wndlib` (wind), `aiLib`, `skdlib`.

The sound driver (`ssd`) cites a separate tree; its unit is `sources/voice_handle_api.cpp`.

## Units

[`config/XC2_100/splits.txt`](../config/XC2_100/splits.txt) assigns every function and the data its code alone uses to one of 532 units. A unit
is named after the source file its code cites. Where no file is cited, the code stays with its neighbour, so a
unit can still hold several original files. The largest, such as
`libs/eflib/source/eflib/effect_update_manager.cpp` (7,306 functions), are certainly several.

Each translation unit with static initializers ends with its initializer function, and the module's `init_array`
lists 195 of them. These mark file boundaries that the splits do not use yet.

## Toolchain

The code was built with clang 3.9.1, the base of NintendoSDK 3.5.0's compiler. Seed functions compiled from
known source identify it:

- libc++'s `__murmur2_or_cityhash<unsigned long, 64>::__hash_len_0_to_16` is byte-identical under 3.9.1. 4.0.1
  differs by one instruction, and 5.0 and 6.0 by most of the function.
- `mm::mtl::ReservedBitflag` methods match in their prologues only with unwind tables on.

The flags are:

    --target=aarch64-none-elf -mcpu=cortex-a57+fp+simd+crypto+crc -fPIC -O3 -fno-exceptions -fno-rtti
    -fasynchronous-unwind-tables -std=gnu++14

`-O2` and `-O3` produced the same code on every seed so far.

`xc2.project.json` pins all of this: the original's SHA-1, the compiler archive and its SHA-256, and the flags.
