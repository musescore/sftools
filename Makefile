#=============================================================================
#  MuseScore sftools
#
#  Copyright (C) 2002-2007 by Werner Schweer and others
#
#  This work is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Library General Public
#  License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
#
#  In addition, as a special exception, licensor gives permission to
#  link the code of this work with the OpenSSL Library (or with modified
#  versions of OpenSSL that use the same license as OpenSSL), and
#  distribute linked combinations including the two. You must obey the
#  GNU General Public License in all respects for all of the code used
#  other than OpenSSL. If you modify this file, you may extend this
#  exception to your version of the file, but you are not obligated to
#  do so. If you do not wish to do so, delete this exception statement
#  from your version. (This exception is necessary should this work be
#  included in a GPL-licenced work.)
#
#  See COPYING.LIB for the licence text and disclaimer of warranty.
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
