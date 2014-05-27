On windows you must have the PDcurses library properly installed to compile this, you can
compile on command line by typing this with gcc, although I am not sure about visual c++:

gcc	-o	strawbs	main.c	-lpdcurses


A linux port should be as easy as changing the #include <curses.h> to ncurses.h and changing
from -lpdcurses to -lncurses provided you have ncurses-dev installed