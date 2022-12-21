#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [0.00], [])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([No rhash lib!])])

# Checks for header files.
AC_CHECK_HEADERS([rhash.h])
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable input with readline functionality]),
    AC_DEFINE(CHANGE_INPUT,[],[Enable readline])
)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
