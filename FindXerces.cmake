############################################################################
# FindXerces.cmake
# Copyright (C) 2017  Belledonne Communications, Grenoble France
#
############################################################################
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
############################################################################
#
# - Find the xerces include file and library
#
#  XERCES_FOUND - system has xerces
#  XERCES_INCLUDE_DIRS - the xerces include directory
#  XERCES_LIBRARIES - The libraries needed to use xerces

if(APPLE AND NOT IOS)
	set(XERCES_HINTS "/usr")
endif()
if(XERCES_HINTS)
	set(XERCES_LIBRARIES_HINTS "${XERCES_HINTS}/lib")
endif()

find_path(XERCES_INCLUDE_DIRS
	NAMES xercesc/util/XercesDefs.hpp
	HINTS "${XERCES_HINTS}"
	PATH_SUFFIXES include
)

find_library(XERCES_LIBRARIES
	NAMES xerces-c
	HINTS "${XERCES_LIBRARIES_HINTS}"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Xerces
	DEFAULT_MSG
	XERCES_INCLUDE_DIRS XERCES_LIBRARIES
)

mark_as_advanced(XERCES_INCLUDE_DIRS XERCES_LIBRARIES)

