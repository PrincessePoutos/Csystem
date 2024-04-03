AC_PREREQ(2.60)
AC_INIT([Csystem],
	[1.0],
	[tymothe.billerey@gmail.com],
	[Csystem],
	[https://lse.epita.fr/])

AC_CONFIG_SRCDIR([src/example.c])
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

AM_SILENT_RULES([yes])

PKG_CHECK_MODULES([CRITERION], [criterion], [], [
  AC_MSG_ERROR([unable to find Criterion])
])

AC_SUBST([CRITERION_CFLAGS])
AC_SUBST([CRITERION_LIBS])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])

AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_OUTPUT
AC_MSG_RESULT([
	$PACKAGE $VERSION
	====================

	prefix:		${prefix}
	compiler:	${CC}
	cflags:		${CFLAGS}
	ldflags:	${LDFLAGS}
])
