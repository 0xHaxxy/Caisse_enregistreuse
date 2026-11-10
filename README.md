# Cash Register

A small cash register program written in C. It computes the change to give back and breaks it down into bills and coins (in rupees, Rs).

All amounts are handled in cents (integers) to avoid floating-point rounding errors. The smallest coin is 5 cents.

## Project structure

```
Caisse_enregistreuse
    |
    |____headers        
    |        |___header.h
    |
    |____script
    |        |__caisse.c
    |      
    |____.gitignore
    |
    |____ README.md
```

## Requirements

A C compiler (gcc, clang or MSVC). No other dependencies.

| System | Compiler installation |
|---|---|
| Debian, Ubuntu, Lubuntu | `sudo apt install build-essential` |
| Fedora | `sudo dnf install gcc` |
| Arch | `sudo pacman -S gcc` |
| macOS | `xcode-select --install` |
| Windows | MSYS2