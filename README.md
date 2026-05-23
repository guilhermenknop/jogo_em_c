# jogo_em_c

Simple terminal game made in C using ncurses.

# Controls

```text
    ↑
← ↓ →
```

* use the arrow keys to move
* press `h` to open the help menu
* press `q` to close text windows

# Objectives

* collect coins (`$`)
* avoid bombs (`*`)
* find keys (`+`)
* use keys to open doors (`:`)

# Requirements

* gcc
* ncurses

Ubuntu/Debian:

```bash
sudo apt install gcc libncurses-dev
```

# Build

```bash
gcc src/*.c -Iinclude -o bin/jogo_em_c -lncurses
```

# Run

```bash
./bin/jogo_em_c
```

