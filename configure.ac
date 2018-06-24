AC_INIT([surveys-manager], [1.0.0], [author-gabriele])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects])

AC_PROG_CXX

AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([libopenair/configuration.hh])
AC_CHECK_HEADERS([libopenair/curl_service_connector.hh])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
        Makefile
        src/Makefile
])

AC_OUTPUT
