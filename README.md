# generate-names

Generates random names. Useful for finding a name for something.


## Building

**generate-names** uses [nob.h](https://github.com/tsoding/nob.h) as build
system. So it only requires a C11 compiler for build project.

    # bootstrap build system
    cc -o nob nob.c

    # run build system
    ./nob

Then copy resultant binary to whatever you want. Generally it becomes
`/usr/local/bin` or `$HOME/.local/bin`.


## Usage

Just run **generate-names**. It will print names to the standard output. For
options see `generate-names -h`.


## Copying

Licensed under the terms of ISC. See file COPYING for details.
