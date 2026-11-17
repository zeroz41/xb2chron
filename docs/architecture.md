# How the project is organised

What you need to know to find your way around the code and the repository. [CONTRIBUTING.md](../CONTRIBUTING.md)
says how to work on a function; this page explains what you are looking at.

## The game's code

The project targets one version of the game, 3.0.1, its final update. Older versions are only a source of names
([Names](#names)).

The game's code is one executable, `main`, from the 3.0.1 update. It holds the whole game, including the code
of every DLC (the DLC packs themselves are data only). The update's other code modules (`sdk`,
`subsdk0`, `rtld`) are Nintendo's SDK and loader, and are not part of this project.

`main` loads at `0x7100000000`. Names, comments and the tools use full addresses, such as `fn_710067A41C` or
`zkit lookup 0x710067A41C`. `symbols.txt` and `splits.txt` give offsets from the start of `main` instead
(`.text:0x0067A41C`).

| Section | Range | Holds |
|---|---|---|
| `.text` | `0x7100000000`–`0x71008B4180` | the code |
| `.rodata` | `0x710097BA60`–`0x71009D93F0` | the game's constants: strings, numbers, tables (the rest of the read-only segment is the linker's) |
| `.data` | `0x7100B3A000`–`0x7100B8FDF0` | initialised variables and virtual tables |
| `.bss` | `0x7100B8FDF0`–`0x71015ED4E0` | zero-initialised variables |

It was built without RTTI and without C++ exceptions, and it exports almost no symbols. So 3.0.1 alone names
nothing: the names come from older versions of the game (see [Names](#names)).

## The repository

| Path | What it is | Edit it? |
|---|---|---|
| `src/` | the decompiled source: one file per original source file ([unit](#units)), at its original path | yes |
| `include/` | headers: the game's own (by folder, like `src/`), the SDK's C library (`string.h`, `math.h`, ...) and the game's version of libc++ (`vector`, `string`, ...) | yes |
| `include/classes/` | one header per class with a virtual table, generated from the tables ([Classes](#classes)) | yes, by hand |
| `config/XC2_301/symbols.txt` | every function and data object in `main`: name, address, size | to name things |
| `config/XC2_301/splits.txt` | which unit owns each address range | to fix a unit |
| `config/XC2_100/` | the same for version 1.0.0, where most names come from: its [symbols](../config/XC2_100/symbols.txt) and [splits](../config/XC2_100/splits.txt). A reference only; 1.0.0 is not built | no |
| `xc2.project.json` | the build's settings: the original's SHA-1, the compiler and its flags, the progress categories | rarely |
| `build.py` | the build | rarely |
| `third_party/` | notices of the open-source code the game links (zlib, libc++, ...) | when adding such code |
| `rom/`, `orig/`, `build/` | your game files, the executable the build takes out of them, and the build's output | never committed |

After a build, `build/XC2_301/report.json` is objdiff's report (what matches), `build/progress/` the progress
pages, and `build/XC2_301/link/main.nso` the rebuilt executable.

## Units

A unit is one original source file: one `.cpp` in `src/`, compiled to one object, owning a range of code and data
in `main`. The game's assertions print their source file's path, as it was on the developers' machines:
`D:/Monolithsoft/BF2/prog/application/BF2/gf/gf_menu_hud.cpp` is unit `src/application/BF2/gf/gf_menu_hud.cpp`.

- `src/application/BF2/`: the game. `gf/` (the game framework: objects, menus, fields, data), `ui/`,
  `framework/`, `battle/`, `execute/`, `minigame/`, `plugin/`.
- `src/libs/`: Monolith Soft's libraries: `monolib_mm` (namespace `ml`), `mcl/mm_lib` (`mm`: maths, containers,
  threads), `anmlib` (animation), `eflib` (effects), `wndlib` (wind), `aiLib`, `skdlib`.
- Top-level folders and files of `src/` (`ui/`, `ml/`, `grlib/`, `File.cpp`, ...): code whose file the game never
  names, placed by its namespace and its position in the executable.
- `unit_<address>.cpp`: a unit whose original file name is unknown. A class-named file (such as
  `AddBlendTree.cpp`) is the same: named after its main class until evidence names the file.

A unit **links** when every function and data object in it matches: the build then takes that part of the game
from the compiled source instead of from the original, and the result must still be identical. `zkit unit
--blocked` lists units that match but don't link yet, and why.

**If a unit boundary looks wrong**, these are the kinds of evidence that place a function, strongest first:
the file its own assertions name (`__FILE__`); being an inline or template copy emitted right after the first code
in that unit that uses it; a static initializer, which always ends its unit; the class it belongs to (a class's
non-inline functions are compiled in one file); 1.0.0's units; and data that only one run of code uses. A change
to `splits.txt` should say which of these it rests on.

## Names

3.0.1's `main` names almost nothing, but older versions of the game do. They are used only for that; the project
does not build or match them:

- **1.0.0** exports nearly every symbol: 49,128 of its 49,907 functions and 5,221 data objects, with their
  original mangled names. 3.0.1 is the same code base, so most of its functions are 1.0.0 functions, recognised by
  their code, what they refer to and their place between already-named functions.
- **2.0.0** survives as an IDA Pro export with original names too. It names code the updates added after 1.0.0
  and corrects some of 1.0.0's.

A name is only carried over when the evidence allows exactly one. Everything else keeps a placeholder until
evidence replaces it:

| Placeholder | Means |
|---|---|
| `fn_<address>` | a function with no proven name (code an update added or changed) |
| `lbl_<address>` | a data object with no proven name |
| `TUnk_<offset>` | a class whose name is unknown, named after its virtual table's offset in `main` |
| `vf<slot>` | a virtual function whose name is unknown |
| `pad_<offset>` | class fields nothing has explained yet |

Never guess a name. CONTRIBUTING.md's [Names](../CONTRIBUTING.md#names) section says what counts as evidence.

## Classes

The game has no RTTI, but its virtual tables say a lot: a table names nearly every slot (from 1.0.0), and its
layout shows the class's bases. `include/classes/` has a header for each of the 2,069 classes with a table, plus
30 class templates. Each declares its bases and its virtual functions in slot order, and nearly all compile to
exactly the original table.

The headers are a starting point. They don't know fields, return types (they say `void` until code proves one)
or bases no table shows. Add those by hand as functions need them, named on evidence. A header that can't
reproduce its table yet says why at its top.

## Compiler and flags

The game was built with clang 3.9.1, the compiler of NintendoSDK 3.5.0, with:

    --target=aarch64-none-elf -mcpu=cortex-a57+fp+simd+crypto+crc -fPIC -O3 -fno-exceptions -fno-rtti
    -fno-strict-aliasing -fno-slp-vectorize -mno-implicit-float -ffunction-sections -fdata-sections
    -fasynchronous-unwind-tables -std=gnu++14 -nostdlibinc -g

`xc2.project.json` holds them, and the build uses them for every file. What they mean for the code you write:

- **`-g` changes the code.** In clang 3.9.1, debug information affects optimisation: every named local adds a
  debug value that the optimiser works around. When a near miss differs only in the order of floating-point
  operations or in which registers it uses, try adding or removing a local variable.
- **`__FILE__` is already right.** Each unit compiles under its original path
  (`D:/Monolithsoft/BF2/prog/<path>`), so assertion strings match by themselves. **`__LINE__` is not:** put
  `#line <n>` before a statement whose line number the original prints.
- **No host headers** (`-nostdlibinc`). The C library is the SDK's, declared in `include/`; add a declaration
  there when code needs one.
- **One section per function** (`-ffunction-sections`). The linker dropped functions nothing called, so 3.0.1
  lacks some functions that 1.0.0 has. A call to a function in the same file is an ordinary relocated call.
- **No strict aliasing, no SLP vectorizer.** Both show in constructors and destructors: stores are kept and not
  merged into vector stores.

The game's compiler differs from stock clang 3.9.1 in one rule: it keeps the `atexit` registration of a static
object whose destructor only calls empty functions, where stock 3.9.1 drops it. The build restores that rule for
the three units that need it, with a small clang plugin on Linux and macOS, and on Windows (where clang can't
load plugins) with a patched copy of `clang++.exe`. You don't need to do anything about it.

## Data

Data is matched like code: each unit defines its own tables, strings and variables, in source, at the addresses
`splits.txt` gives it.

The linker kept one copy of each string literal and each 4- and 8-byte constant for the whole executable, so a
literal belongs to the first unit that uses it. Each unit's other read-only data (tables) follows in link order.
An inline function's static or a template's table is in every unit that uses it, and the linker kept the first
copy.

Never copy data the code does not use: no textures, models, sounds, text or other assets.

## Redoing the name transfer

Maintainers only. With 1.0.0's `main` at `orig/XC2_100/main`, build 1.0.0's signatures, then analyze 3.0.1 with
`config/XC2_301/symbols.txt` moved aside, so the analysis starts from nothing:

    zkit signatures build xc2_100 --image orig/XC2_100/main --symbols config/XC2_100/symbols.txt \
        --splits config/XC2_100/splits.txt
    zkit analyze --out build/XC2_301/analysis

`build/XC2_301/analysis/analysis.json` then lists the evidence for every name. 2.0.0's IDA export is not in the
repository and is read through its own signatures (`xc2_200`); with both donors' signatures in the cache,
`zkit analyze` uses both.
