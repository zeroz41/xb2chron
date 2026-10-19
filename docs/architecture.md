# Architecture

## The executable

Xenoblade Chronicles 2 ships its code as four modules in the ExeFS. An update replaces the whole ExeFS, so the
3.0.1 update's modules are complete executables; the base game supplies the data, which the update's RomFS
patches. The DLC packs hold data only, so their code is part of 3.0.1's `main` too. This project decompiles
`main`, the game itself; the others are Nintendo's and stay as they are.

| Module | Contents |
|---|---|
| `main` | the game, Monolith Soft's libraries, inlined libc++ templates |
| `sdk` | NintendoSDK 3.5.0: nnSdk, NVN, libz |
| `subsdk0` | NintendoSDK 3.5.0 movie playback |
| `rtld` | the dynamic loader |

`main` (build id `4f5c96e2d97f45ac288bc67613ebef0a`) loads at `0x7100000000`:

| Section | Range |
|---|---|
| `.text` | `0x0000000`–`0x08B4180` |
| `.rodata` | `0x08B5000`–`0x0B39F23` |
| `.data` | `0x0B3A000`–`0x0B8FDF0` |
| `.bss` | `0x0B8FDF0`–`0x15EE000` |

It calls the SDK through 667 imports and exports only 21 symbols (`nnMain`, the allocator, `operator new` and
`delete`, two `std::vector` instances). Its 35,906 functions come from the unwind table, which clang writes for
every function. It was built without RTTI and without exceptions, so the module names no classes either.

## Names from 1.0.0

1.0.0's `main` exports almost every symbol it defines: 49,128 of its 49,907 functions and 5,221 data objects
(2,845 of them vtables) carry their original mangled names. 3.0.1 is the same code base built with the same
compiler, linked in the same order, but with nothing exported, so the linker also dropped every function nothing
calls. 1.0.0's [symbols](../config/XC2_100/symbols.txt) and [splits](../config/XC2_100/splits.txt) stay in the
repository as the reference build for 3.0.1's names.

zkit's signatures carry the names across. A function's shape is its instructions with every relocated field
cleared, and what each relocation names. A 3.0.1 function takes a 1.0.0 name when the evidence admits only that
one:

- **its shape**, unique among 1.0.0's functions, or confirmed by what it refers to or by its neighbours;
- **a reference**: a matched function's call or address names its target, and a matched constructor's vtable
  names the virtual functions in its slots;
- **its place**: between two named functions, the functions in between are 1.0.0's functions in between, less
  what the linker dropped. Copies of one shape pair in order; code that changed pairs one to one, or with the
  function it shares by far the most callees, data and strings with;
- **a call**: a changed function's one unnamed callee is its 1.0.0 version's one unclaimed callee.

The steps that pair changed code were checked against changed functions named independently (by their callers or
their vtable slots) and kept only where they were never wrong. 28,478 of the 35,906 functions and 3,983 data
objects take 1.0.0's names this way (395 more are import stubs and exports the module names itself);
`build/XC2_301/analysis/analysis.json` lists the evidence for each, and
[`config/XC2_301/symbols.txt`](../config/XC2_301/symbols.txt) holds them. The other 7,033 are code an update added,
or changed past what the evidence settles. To redo the transfer, with 1.0.0's `main` at `orig/XC2_100/main`:

    zkit signatures build xc2_100 --image orig/XC2_100/main --symbols config/XC2_100/symbols.txt \
        --splits config/XC2_100/splits.txt
    zkit analyze --out build/XC2_301/analysis

## Source layout

The game's assertions name their source files, as built on Monolith Soft's machines under
`C:/MonolithSoft/BF2/prog/` (BF2 is the game's internal name). Units keep that layout, relative to `prog/`:

- `application/BF2/`: the game. `gf/` (game framework: objects, menus, fields, data), `ui/`, `framework/`,
  `battle/`, `execute/`, `minigame/`, `plugin/`.
- `libs/`: Monolith Soft's libraries. `monolib_mm` (`ml`), `mcl/mm_lib` (`mm`: math, containers, threads),
  `anmlib` (animation), `eflib` (effects), `wndlib` (wind), `aiLib`, `skdlib`.

The sound driver (`ssd`) cites a separate tree; its unit is `sources/voice_handle_api.cpp`.

## Units

[`config/XC2_301/splits.txt`](../config/XC2_301/splits.txt) assigns every function and the data its code alone
uses to one of 534 units. A unit is named after the source file its code cites, or else the file 1.0.0's splits
put its functions in; a function's own citation wins, and so does a unit's run in the link over a lone function
1.0.0 placed elsewhere. Inline functions and template instances take no unit from 1.0.0: the linker keeps one
copy, from whichever unit it meets first, and that differs between the builds. Where nothing is cited, the code
stays with its neighbour, so a unit can still hold several original files, and 28 files still come out in more
than one piece.

Each translation unit with static initializers ends with its initializer function, and the module's `init_array`
lists 200 of them. These mark file boundaries that the splits do not use yet.

## Toolchain

The code was built with clang 3.9.1, the base of NintendoSDK 3.5.0's compiler. All four modules of 3.0.1 still
carry NintendoSDK 3.5.0's middleware strings, and 28,522 of 3.0.1's functions have the shape of a 1.0.0
function. Seed functions compiled from known source identify the compiler:

- libc++'s `__murmur2_or_cityhash<unsigned long, 64>::__hash_len_0_to_16` is byte-identical under 3.9.1. 4.0.1
  differs by one instruction, and 5.0 and 6.0 by most of the function.
- `mm::mtl::ReservedBitflag` methods match in their prologues only with unwind tables on.

The flags are:

    --target=aarch64-none-elf -mcpu=cortex-a57+fp+simd+crypto+crc -fPIC -O3 -fno-exceptions -fno-rtti
    -fasynchronous-unwind-tables -std=gnu++14

`-O2` and `-O3` produced the same code on every seed so far.

`xc2.project.json` pins all of this: the original's SHA-1, the compiler archive and its SHA-256, and the flags.
