# use the TAP log driver
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
            $(top_srcdir)/build-aux/tap-driver.sh

  # Setup Criterion TAP output using ENV
# AM_TESTS_ENVIRONMENT = \
#   CRITERION_OUTPUTS='tap:-'; \
#   export CRITERION_OUTPUTS;

check_PROGRAMS = criterion_tests

criterion_tests_SOURCES = tests/simple.c
criterion_tests_CFLAGS =  $(CRITERION_CFLAGS)
criterion_tests_LDFLAGS =  $(CRITERION_LIBS)

TESTS = criterion_tests

EXTRA_DIST = autogen.sh
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	      -include $(top_builddir)/config.h \
	      -I${top_srcdir}/src

AM_CFLAGS = $(WARN_CFLAGS)
AM_LDFLAGS = $(WARN_LDFLAGS)

bin_PROGRAMS = Csystem

Csystem_SOURCES = src/example.c

Csystem_LDADD = $(PTHREAD_LIBS) $(OPENSSL_LDFLAGS) $(OPENSSL_LIBS) $(CURL_LIBS)
