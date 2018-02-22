set(_components
    Core
    Xml
  )

foreach(_component ${_components})
  find_package(Qt5${_component})
  list(APPEND QT_LIBRARIES ${Qt5${_component}_LIBRARIES})
  list(APPEND QT_INCLUDES ${Qt5${_component}_INCLUDE_DIRS})
endforeach()

include_directories(${QT_INCLUDES})
set(QT_INSTALL_PREFIX ${_qt5Core_install_prefix})

#add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)
