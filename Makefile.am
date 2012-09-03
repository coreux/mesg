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

DIST_SUBDIRS = C en_GB

SUBDIRS = . $(NLS_SUBDIRS)

bin_PROGRAMS = mesg

doc_DATA = README LICENSE-2.0 mesg.1.html

mesg_SOURCES = mesg.c

dist_man1_MANS = mesg.1

mesg.1: mesg.1.xml
	$(XML2MAN) $<

mesg.1.html: mesg.1.xml
	$(XML2HTML) $< > $@

