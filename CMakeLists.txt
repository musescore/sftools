#=============================================================================
#  MuseScore
#  Music Composition & Notation
#  $Id:$
#
#  Copyright (C) 2011-2014 Werner Schweer
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2
#  as published by the Free Software Foundation and appearing in
#  the file LICENSE.GPL
#=============================================================================

project(sfconvert)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
include (${PROJECT_SOURCE_DIR}/build/ECMQt4To5Porting.cmake)
include (${PROJECT_SOURCE_DIR}/build/FindQt5Transitional.cmake)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(QT_MIN_VERSION    "5.1.0")
set(QT_USE_QTXML         TRUE)

# find_package(Qt4 "4.8")

# if (NOT QT4_FOUND)
      # message(FATAL_ERROR "Fatal error: QT (version >= 4.8.0) required."
         # " Cmake tries to detect QT4 by searching for 'qmake' in your PATH."
         # "If you have QT4 installed, make sure qmake is found in your PATH. "
         # "If you compiled QT4 yourself make sure your new qmake is found"
         # " _first_ in your PATH."
         # )
# else (NOT QT4_FOUND)
      # message("Qt lib found at ${QT_LIBRARY_DIR}")
# endif (NOT QT4_FOUND)

# include(${QT_USE_FILE})

if (MINGW)
      set(CMAKE_CXX_FLAGS   "-g -std=c++0x")
else (MINGW)
      set(CMAKE_CXX_FLAGS   "-g -std=c++0x -fPIC -fPIE")
endif (MINGW)

add_executable(sfconvert
   sfconvert.cpp sfont.cpp xml.cpp
   )

if (MINGW)
   target_link_libraries(sfconvert
      ${QT_LIBRARIES}
      vorbis
      ##vorbisfile
      ogg
      sndfile-1
   )

   install( TARGETS sfconvert RUNTIME DESTINATION . )

   install_files ( . .dll
      ${CROSS}/bin/libgcc_s_dw2-1.dll
      ${CROSS}/bin/libstdc++-6.dll
      ${CROSS}/bin/libwinpthread-1.dll
      ${CROSS}/lib/libsndfile-1.dll
      ${CROSS}/lib/libogg.dll
      ${CROSS}/lib/libvorbis.dll
      #${CROSS}/lib/libvorbisfile.dll
      ${CROSSQT}/bin/Qt5Core.dll
      ${CROSSQT}/bin/Qt5Xml.dll
      ${CROSSQT}/bin/icuin51.dll
      ${CROSSQT}/bin/icuuc51.dll
      ${CROSSQT}/bin/icudt51.dll
      )
else (MINGW)
   target_link_libraries(sfconvert
      ${QT_LIBRARIES}
      vorbis
      vorbisenc
      ogg
      sndfile
   )
endif (MINGW)
