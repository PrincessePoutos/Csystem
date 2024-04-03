# use the TAP log driver
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
            $(top_srcdir)/build-aux/tap-driver.sh

# Setup Criterion TAP output using ENV
# AM_TESTS_ENVIRONMENT = \
#   CRITERION_OUTPUTS='tap:-'; \
#   export CRITERION_OUTPUTS;

check_PROGRAMS = criterion_tests_client criterion_tests_server

criterion_tests_client_SOURCES = tests/client.c $(CnetworkingClient_SOURCES)
criterion_tests_client_CFLAGS =  $(CRITERION_CFLAGS)
criterion_tests_client_LDFLAGS =  $(CRITERION_LIBS)

criterion_tests_server_SOURCES = tests/server.c $(CnetworkingServer_SOURCES)
criterion_tests_server_CFLAGS =  $(CRITERION_CFLAGS)
criterion_tests_server_LDFLAGS =  $(CRITERION_LIBS)


criterion_tests_args = '--tap:-'

TESTS = criterion_tests_client criterion_tests_server

EXTRA_DIST = autogen.sh 
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	      -include $(top_builddir)/config.h \
	      -I${top_srcdir}/src

AM_CFLAGS = $(WARN_CFLAGS)
AM_LDFLAGS = $(WARN_LDFLAGS)

bin_PROGRAMS = CnetworkingClient CnetworkingServer

CnetworkingClient_SOURCES = ./src/protopeach.c \
									./src/protopeach.h \
									./src/client/client.c

CnetworkingServer_SOURCES = ./src/protopeach.c \
									./src/protopeach.h \
									./src/server/server.c

# Cnetworking_LDADD = ''
