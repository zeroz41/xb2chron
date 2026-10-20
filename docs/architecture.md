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
| `.rodata` | `0x097BA60`–`0x09D93F0` (the game's), and `0x08B5000`–`0x097BA60`, `0x09D93F0`–`0x0B39F23` (the linker's) |
| `.data` | `0x0B3A000`–`0x0B8FDF0` |
| `.bss` | `0x0B8FDF0`–`0x15EE000` |

The read-only segment is mostly the linker's: the dynamic relocations, hash tables, symbols and strings before
the game's constants, and the unwind tables (`.eh_frame_hdr`, `.eh_frame`) after them. The symbols list each in a
section of its own, as a section table would, and no unit owns them.

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
  names the virtual functions in its slots. Slots pair with 1.0.0's by the code in them, not by index: the updates
  added and removed virtuals, so `gf::DataObjEnemy`'s table kept its length while its slots moved;
- **its place**: between two named functions, the functions in between are 1.0.0's functions in between, less
  what the linker dropped. Copies of one shape pair in order; code that changed pairs one to one, with the
  function it shares by far the most callees, data and strings with, or, in order, with the function whose code
  it is by far the most like (sixteen instructions or more: a short getter whose field moved reads exactly like
  its neighbour did). Code that differs from a sibling only in immediates pairs in order too, never by its exact
  code: the updates added BDAT columns and struct fields, so 3.0.1's `GfBdatItem::getInfoName` reads exactly like
  1.0.0's `getEventName`;
- **a call**: a changed function's one unnamed callee is its 1.0.0 version's one unclaimed callee.

3.0.1 was built from `D:/`, 1.0.0 from `C:/`, so the source paths that assertions cite compare without their
drive letter. The steps that pair changed code were checked against changed functions named independently (by their callers or
their vtable slots) and kept only where they were never wrong. 29,334 of the 35,906 functions and 4,020 data
objects take 1.0.0's names this way (395 more are import stubs and exports the module names itself), each with
1.0.0's binding: 7,753 are inline functions or template instances (`scope:weak`);
`build/XC2_301/analysis/analysis.json` lists the evidence for each, and
[`config/XC2_301/symbols.txt`](../config/XC2_301/symbols.txt) holds them. The other 6,177 are code an update added,
or changed past what the evidence settles.

Every other address the code forms, loads or stores through, and every address a relocated pointer holds, starts
a data object too, named `lbl_<address>` until evidence names it: 18,194 of them, sized by what they are (a
string to its NUL, a scalar the code only reads at one width to that width, else up to the next object). To redo
the transfer, with 1.0.0's `main` at `orig/XC2_100/main`, build
1.0.0's signatures and analyze 3.0.1 with `config/XC2_301/symbols.txt` moved aside, so the analysis starts from
the module's own tables and inherits no name:

    zkit signatures build xc2_100 --image orig/XC2_100/main --symbols config/XC2_100/symbols.txt \
        --splits config/XC2_100/splits.txt
    zkit analyze --out build/XC2_301/analysis

## Source layout

The game's assertions name their source files, as built on Monolith Soft's machines under
`D:/Monolithsoft/BF2/prog/` for 3.0.1 (`C:/` for 1.0.0; BF2 is the game's internal name). `mm_lib` cites
`C:/MonolithSoft/` in 3.0.1 too: it was linked prebuilt. Units keep that layout, relative to `prog/`:

- `application/BF2/`: the game. `gf/` (game framework: objects, menus, fields, data), `ui/`, `framework/`,
  `battle/`, `execute/`, `minigame/`, `plugin/`.
- `libs/`: Monolith Soft's libraries. `monolib_mm` (`ml`), `mcl/mm_lib` (`mm`: math, containers, threads),
  `anmlib` (animation), `eflib` (effects), `wndlib` (wind), `aiLib`, `skdlib`.

The sound driver (`ssd`) cites a separate tree; its unit is `sources/voice_handle_api.cpp`.

## Units

[`config/XC2_301/splits.txt`](../config/XC2_301/splits.txt) assigns every function, and the data only its code
uses, to one of 637 units: 498 named after a source file (464 after the file their own code cites, 34 after the
file 1.0.0's splits put their functions in), 113 after the class most of their functions belong to, and 26 by
address. A unit named by class or address is code no file string reaches, such as the event system (`event::`,
1,716 functions), monolib's renderer, or files that assert nothing; its name is a placeholder until evidence
names the file. The evidence, strongest first:

- **citations**: a function's own `__FILE__` names its unit, and a change of cited file is a boundary;
- **static initializers**: each unit with static initializers ends with its own initializer (one that tests no
  guard; a guarded one initializes a template's static member and goes with whichever unit came first), so the
  200 entries of `init_array` mark where those units end, and each entry is its unit's data;
- **classes**, in 1.0.0: its symbol table marks inlines and template instances weak, so a class's other
  functions are its own, compiled in one file (every one of the 636 classes with a citing function cites a single
  file); next to that file's citations they are that file's;
- **another build**: 1.0.0's splits, where 3.0.1's code says nothing. Where 3.0.1's code states a boundary between
  the same two files, 1.0.0's boundary there yields to it; where 1.0.0 puts a third file between them, it stands;
- **data**: data only one run of code uses holds the run in one unit, unless what the code states separates it
  (a template's table or an inline's static is shared, kept from whichever unit came first);
- **reach**: a file's evidence reaches through the data its code shares, over the inlines and template
  instances clang emits after the code that first uses them (weak in 1.0.0, and so in 3.0.1 where the name came
  from 1.0.0), and at most 48 functions or 0x8000 bytes past that. A longer run tied to neither neighbouring file
  is neither's, but a unit of its own.

1.0.0's [splits](../config/XC2_100/splits.txt) are this same evidence applied to 1.0.0's `main` (`zkit units
--splits` on a project whose target is 1.0.0), not the original build's: no map of either build exists. Two
checks measure them. Hiding half of each build's citations at random and proposing units again, 96% of 3.0.1's
hidden functions that land in a file-named unit land in the file they cite (85% with the splits before the class,
third-file and reach rules), and those rules moved none into a wrong file. A class's table and static members are
its file's (the table goes with the class's first out-of-line virtual): of the 711 in 3.0.1 whose file 1.0.0's
classes fix, 655 lie in that file's unit and 12 in another (599 and 69 before).

The link order follows the source paths, sorted case-insensitively by their upper-case spelling within the game
(`ik_lookat_solver.cpp` before `ik_look_solver.cpp`); 20 of the 498 file units step back in that order, which marks
units still misnamed or holding several files (and the start of each library). Inline functions and template
instances take no unit from 1.0.0. 12 files still come out in more than one piece.

A unit owns one range per section, in link order like its code: 99.6% of `.bss`, 84% of `.data` and nearly all of
the game's `.rodata` have a unit; the rest is data several units use, which the unit defining it has to claim,
and data no code refers to between two units' ranges.

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
