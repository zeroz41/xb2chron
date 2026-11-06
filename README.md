# Xenoblade Chronicles 2

A work-in-progress matching decompilation of Xenoblade Chronicles 2 for Nintendo Switch, version 3.0.1: the
final update, whose executable holds the code of the whole game and every DLC.

The goal is C++ source that compiles to the same code as the game's executable, function for function. This
repository contains no game code or assets; you need your own copy of the game.

## Progress

<!-- progress -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 52.07% | 14.68% |
| Data | 24.79% | 13.36% |
| Functions | 30,605 of 35,531 | |
| Units | | 467 of 868 |
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

The first build fetches the compiler and tools into `build/`. Every build then rebuilds `main` from the compiled
units and the original (`build/XC2_301/link/main.nso`), places each matched unit where the original holds it,
checks the result against the segment hashes in the original's header and marks the units it proves as linked.
Code that is not decompiled yet still comes from your copy of the game, so a passing build does not mean the
decompilation is complete.

## Objdiff and the progress page

`zkit build` also writes `objdiff.json` in the repository folder, the match report `build/XC2_301/report.json`,
and a page that browses it, `build/progress/index.html`.

- **objdiff.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open the repository folder
  in it. It reads `objdiff.json`, rebuilds a unit when you save its source and shows each function next to the
  original.
- **Progress page.** Open `build/progress/index.html` in a browser. It shows code and data matched and linked for
  the whole executable, each source folder and each unit, down to every function and data section, with search
  and filters, and works offline. `zkit report` rewrites it from the last report; `zkit report --readme` also
  refreshes the table above.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Source files go under `src/`, at the path of the original file they
recover; [docs/architecture.md](docs/architecture.md) describes how the executable is laid out.

## License

The source in this repository is released under the [MIT License](LICENSE). It covers this project's own work
only: Xenoblade Chronicles 2 and its code and data belong to their owners and are not part of it.
