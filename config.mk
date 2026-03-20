# dwm version
VERSION = 6.8

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
# start : renzo to take into account modern library locations
# primary paths (actual current system paths)
X11INC = /usr/include/X11
X11LIB = /usr/lib

# fallback paths (old or alternate)
X11INC_FALLBACK = /usr/X11R6/include
X11LIB_FALLBACK = /usr/X11R6/lib
# end : renzo to take into account modern library locations

# FreeBSD (uncomment)
#X11INC = /usr/local/include
#X11LIB = /usr/local/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
# FreeBSD (uncomment)
#FREETYPEINC = /usr/local/include/freetype2
# OpenBSD (uncomment)
#FREETYPEINC = ${X11INC}/freetype2
# OpenBSD - Uncomment this for the swallow patch / SWALLOW_PATCH
#KVMLIB = -lkvm

# Uncomment this for the alpha patch and the winicon patch (BAR_ALPHA_PATCH, BAR_WINICON_PATCH)
XRENDER = -lXrender #renzo uncommented

# Uncomment this for the mdpcontrol patch / MDPCONTROL_PATCH
#MPDCLIENT = -lmpdclient

# Uncomment for the pango patch / BAR_PANGO_PATCH
PANGOINC = `pkg-config --cflags xft pango pangoxft`
PANGOLIB = `pkg-config --libs xft pango pangoxft`

# Uncomment for the ipc patch / IPC_PATCH
#YAJLLIBS = -lyajl
#YAJLINC = -I/usr/include/yajl

# Uncomment this for the rounded corners patch / ROUNDED_CORNERS_PATCH
#XEXTLIB = -lXext

# Uncomment this for the swallow patch / SWALLOW_PATCH
#XCBLIBS = -lX11-xcb -lxcb -lxcb-res

# This is needed for the winicon and tagpreview patches / BAR_WINICON_PATCH / BAR_TAGPREVIEW_PATCH
IMLIB2LIBS = -lImlib2 #renzo uncommented, was commented

# Uncomment for the banish patch / BANISH_PATCH (for mouse related features)
#XILIB = `pkg-config --libs xi xfixes`

# Uncomment for the bidi patch
#BDINC = `pkg-config --cflags fribidi`
#BDLIBS = `pkg-config --libs fribidi`

# start: renzo: to account for modern library locations, also included -I. to help clangd or intellisense detection
# includes and libs

INCS = -I. -Ipatch -I${X11INC} -I${X11INC_FALLBACK} -I${FREETYPEINC} ${YAJLINC} ${PANGOINC} ${BDINC}
LIBS = -L${X11LIB} -L${X11LIB_FALLBACK} -lX11 ${XINERAMALIBS} ${FREETYPELIBS}  ${XRENDER} ${MPDCLIENT} ${XEXTLIB} ${XCBLIBS} ${KVMLIB} ${PANGOLIB} ${YAJLLIBS} ${IMLIB2LIBS} $(BDLIBS) $(XILIB)
# end: renzo: to account for modern library locations

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC = cc
