//Khartikova
//khawm is Khana Window Manager
//Thanks a lot to tinywm and aewm++ developers for fairly simple code
//examples!
//
//
//
//TODO:
//
//1. MoveFocusTo
//2. Focused
//
//

#include <iostream>

#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmd.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RIGHT 1
#define LEFT 2
#define clockwise 2
#define counterclockwise 1

//#define TABBED 5
#define FLOAT 6

#define FOCUS -1

