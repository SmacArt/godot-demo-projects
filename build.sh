#!/bin/sh
scons -j(nproc) use_llvm=yes use_lld=yes
sudo cp bin/godot.linuxbsd.tools.64.llvm /usr/bin/godot
