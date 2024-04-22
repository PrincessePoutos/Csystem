AC_PREREQ(2.60)
AC_INIT([Cnetworking],
	[1.0],
	[tymothe.billerey@oteria.fr],
	[Cnetworking],
	[https://github.com/Neptunium931/Csystem])

AC_CONFIG_SRCDIR([src/protopeach.c])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([
		  foreign
		  -Wall
		  silent-rules
		  subdir-objects
      -Werror
])

AC_PROG_CC
AC_PROG_AWK
AC_USE_SYSTEM_EXTENSIONS

AX_COMPILER_FLAGS
AX_CHECK_COMPILE_FLAG([-fsanitize=address], [ASAN_FLAG="-fsanitize=address"])
CFLAGS="$CFLAGS -std=c99 ${ASAN_FLAG}"

AM_SILENT_RULES([yes])

PKG_CHECK_MODULES([CRITERION], [criterion], [], [
  AC_MSG_ERROR([unable to find Criterion])
])

AC_SUBST([CRITERION_CFLAGS])
AC_SUBST([CRITERION_LIBS])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])

AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_ARG_WITH([enable-erase],
    AS_HELP_STRING([--with-enable-erase],
                   [Enable erase sendFruit]),
    [enable-erase=yes],
    [enable_erase=no])

# Set custom define based on the option
if test "x$enable_erase" = "xyes"; then
    AC_DEFINE([ENABLE_ERASE], [1], [Enable erase sendFruit])
fi

AC_OUTPUT
AC_MSG_RESULT([
	$PACKAGE $VERSION
	====================

	prefix:		${prefix}
	compiler:	${CC}
	cflags:		${CFLAGS}
	ldflags:	${LDFLAGS}
])
