# Xenoblade Chronicles 2

A work-in-progress matching decompilation of Xenoblade Chronicles 2 for Nintendo Switch, version 3.0.1: the
final update, whose executable holds the code of the whole game and every DLC.

The goal is C++ source that compiles to the same code as the game's executable, function for function. This
repository contains no game code or assets; you need your own copy of the game.

## Progress

<!-- progress -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 0.00% | 0.00% |
| Data | 0.00% | 0.00% |
| Functions | 0 of 35,906 | |
| Units | | 0 of 537 |
<!-- /progress -->

## Target

| | |
|---|---|
| Game | Xenoblade Chronicles 2, title `0100E95004038000`, with update `0100E95004038800` version 3.0.1 |
| Executable | `main` of the 3.0.1 update, SHA-1 `55a82580cd6826cfb9ffbbb2da5fe9a4c5a4b4c8` |
| Compiler | clang 3.9.1 (NintendoSDK 3.5.0) |

## Building

You need your own dump of the game with the 3.0.1 update, and Ninja.

1. Extract `main` from the 3.0.1 update's ExeFS and place it at `orig/XC2_301/main`. An update replaces the
   whole ExeFS, so this one file is the executable; running the game still needs the base game as well, whose
   data the update patches.
2. Install the build tooling, [zkit](https://github.com/zeroz41/zkit-gcnx), then run:

       zkit use xc2.project.json
       zkit build --download
       zkit build

The first build fetches the compiler and tools into `build/`. Each build writes the match report to
`build/XC2_301/report.json`; open the folder in [objdiff](https://github.com/encounter/objdiff) to compare
functions.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Source files go under `src/`, at the path of the original file they
recover; [docs/architecture.md](docs/architecture.md) describes how the executable is laid out.
