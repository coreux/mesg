## Copyright 2012 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

AC_INIT([mesg],[master])

AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE

AC_CONFIG_HEADER([config.h])

AC_PROG_CC

UX_BUILD_DOCS
UX_ENABLE_NLS

if test x"$build_nls" = x"yes" ; then
   NLS_SUBDIRS="C en_GB"
fi
AC_SUBST([NLS_SUBDIRS])

AC_CHECK_HEADERS([unistd.h sys/types.h sys/stat.h errno.h])

AC_CONFIG_FILES([Makefile
C/Makefile
en_GB/Makefile
])

AC_OUTPUT
