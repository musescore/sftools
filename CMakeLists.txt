#=============================================================================
#  MuseScore
#  Music Composition & Notation
#  $Id:$
#
#  Copyright (C) 2011 Werner Schweer
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2
#  as published by the Free Software Foundation and appearing in
#  the file LICENSE.GPL
#=============================================================================

project(sfconvert)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(QT_MIN_VERSION    "4.8.0")
set(QT_USE_QTXML         TRUE)

find_package(Qt4 "4.8")

if (NOT QT4_FOUND)
      message(FATAL_ERROR "Fatal error: QT (version >= 4.8.0) required."
         " Cmake tries to detect QT4 by searching for 'qmake' in your PATH."
         "If you have QT4 installed, make sure qmake is found in your PATH. "
         "If you compiled QT4 yourself make sure your new qmake is found"
         " _first_ in your PATH."
         )
else (NOT QT4_FOUND)
      message("Qt lib found at ${QT_LIBRARY_DIR}")
endif (NOT QT4_FOUND)

include(${QT_USE_FILE})

set(CMAKE_CXX_FLAGS   "-g")

add_executable(sfconvert
   sfconvert.cpp sfont.cpp xml.cpp
   )

target_link_libraries(sfconvert
   ${QT_LIBRARIES}
   vorbis
   vorbisenc
   ogg
   sndfile
   )

