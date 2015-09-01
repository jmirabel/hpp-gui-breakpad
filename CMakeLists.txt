#
# Copyright (c) 2015 CNRS
# Authors: Joseph Mirabel
#
#
# This file is part of hpp-gui
# hpp-gui is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp-gui is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp-gui  If not, see
# <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CXX_DISABLE_WERROR TRUE)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(ExternalProject)

SET(PROJECT_NAME "hpp-gui-breakpad")
SET(PROJECT_URL "https://github.com/jmirabel/hpp-gui-breakpad")
SET(PROJECT_DESCRIPTION "Crash reporter plugin for HPP")
SET(PROJECT_VERSION "0")

SETUP_PROJECT()

FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui)
ADD_REQUIRED_DEPENDENCY("hpp-gui")

ExternalProject_Add (google-breakpad
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/google-breakpad
  SVN_REPOSITORY http://google-breakpad.googlecode.com/svn/trunk/
  SOURCE_DIR ${CMAKE_BINARY_DIR}/google-breakpad
  CONFIGURE_COMMAND ./configure --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  )

INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/google-breakpad/src)

SET(PLUGIN_NAME breakpadplugin)

SET(${PLUGIN_NAME}_HEADERS
  include/hpp/gui/plugin/breakpad-plugin.hh
  )

SET(${PLUGIN_NAME}_FORMS
  )

SET(${PLUGIN_NAME}_RESOURCES
  )

QT4_WRAP_CPP(${PLUGIN_NAME}_HEADERS_MOC ${${PLUGIN_NAME}_HEADERS} OPTIONS -I${HPP_GUI_INCLUDEDIR})
QT4_WRAP_UI(${PLUGIN_NAME}_FORMS_HEADERS ${${PLUGIN_NAME}_FORMS})
QT4_ADD_RESOURCES(${PLUGIN_NAME}_RESOURCES_RCC ${${PLUGIN_NAME}_RESOURCES})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

SET (${PLUGIN_NAME}_SOURCES
  src/breakpad-plugin.cc
  )

ADD_LIBRARY(${PLUGIN_NAME} SHARED ${${PLUGIN_NAME}_SOURCES}
  ${${PLUGIN_NAME}_HEADERS_NO_MOC}
  ${${PLUGIN_NAME}_HEADERS_MOC}
  ${${PLUGIN_NAME}_FORMS_HEADERS}
  ${${PLUGIN_NAME}_RESOURCES_RCC}
  )
ADD_DEPENDENCIES (${PLUGIN_NAME} google-breakpad)

TARGET_LINK_LIBRARIES(${PLUGIN_NAME}
  ${QT_LIBRARIES}
  ${CMAKE_BINARY_DIR}/google-breakpad/src/client/linux/libbreakpad_client.a
  pthread)
PKG_CONFIG_USE_DEPENDENCY(${PLUGIN_NAME} "hpp-gui")

INSTALL(TARGETS ${PLUGIN_NAME} DESTINATION lib/hpp-gui-plugins)

SETUP_PROJECT_FINALIZE()
