#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([strip_podcast], [1.0], [blair@the-blair.com])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/strip_podcast.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CPP
AC_CHECK_PROG([GENGETOPT], [gengetopt], [gengetopt])

if test "x${GENGETOPT}" = x; then
    AC_MSG_ERROR([
  -----------------------------------------------
  The gengetopt program is required to build 
  strip_podcast.  Stopping...
  Check 'config.log' for more information.
  -----------------------------------------------])
fi

# Checks for libraries.
AX_LIB_TAGLIB([1.6],,AC_MSG_ERROR([taglib 1.6 or greater is required]))

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
