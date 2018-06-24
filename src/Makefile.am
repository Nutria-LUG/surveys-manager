bin_PROGRAMS = surveys-manager
surveys_manager_SOURCES = \
	main.cc \
	survey.cc \
	survey.hh \
	surveys_provider.cc\
	surveys_provider.hh\
	surveys_service_client.cc \
	surveys_service_client.hh

surveys_manager_LDADD = -lsqlite3 -lopenair
surveys_manager_CXXFLAGS = -std=c++14

# Some usefull notes are reported below.
# 01. To add an existing library use -l options
#      sourvays-manager_LDADD =  -lib
#
# 02. To add some custom flag to the project use _CXXFLAGS
#      sourvays-manager_CXXFLAGS = -std=c++17
#
# 03. To compile an inner static library use noinst_, this avoid the
#     installation (static library must be linked directly to the the
#     compiled file).
#      noinst_LIBRARIES = libstaticlibname.a
#      libstaticlibname_a_SOURCES = ... list of sources ...
#
#      bin_PROGRAM = sourvays-manager
#      sourvays-manager_SOURCES = ....
#      sourvays-manager_LDADD = libstaticlibname.a
#
#     Remember to add AC_PROG_RANLIB macro in configure.ac
#     AC_PROG_RANLIB: This is required if any libraries are built in
#                     the package. See Particular Program Checks in
#                     The Autoconf Manual. 

