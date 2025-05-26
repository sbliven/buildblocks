# IMOD


## Installation

IMOD is shipped as a self-expanding installation script. Run `./build` to
install.

## Known Issues

The installation includes environment scripts which install into
`$IMOD_DIR/profile.d`. These are sourced in the modulefile. This means that the
module cannot be unloaded cleanly (eg IMOD remains in the PATH after
unloading).

TODO solution: re-write the .sh script that is sourced in the modulefile into the 
modulefile directly. Variables and Path extensions will then automatically be 
"unset" when unloding. 
