#=============================================================================
#  sftools
#  $Id:$
#
#  Copyright (C) 2002-2007 by Werner Schweer and others
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#=============================================================================

CPUS = 2

release:
	if test ! -d build.release; then mkdir build.release; fi; \
  cd build.release; \
  cmake -DCMAKE_BUILD_TYPE=RELEASE  .. ;\
  $(MAKE) -j ${CPUS}

debug:
	if test ! -d build.debug; then mkdir build.debug; fi; \
  cd build.debug ; \
  cmake -DCMAKE_BUILD_TYPE=DEBUG .. ; \
  $(MAKE) -j ${CPUS}

version:
	@echo ${VERSION}

#
# clean out of source build
#

clean:
	rm -rf build.debug build.release


