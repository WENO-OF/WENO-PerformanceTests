# ===========================================================================
#       ██╗    ██╗███████╗███╗   ██╗ ██████╗     ███████╗██╗  ██╗████████╗
#       ██║    ██║██╔════╝████╗  ██║██╔═══██╗    ██╔════╝╚██╗██╔╝╚══██╔══╝
#       ██║ █╗ ██║█████╗  ██╔██╗ ██║██║   ██║    █████╗   ╚███╔╝    ██║   
#       ██║███╗██║██╔══╝  ██║╚██╗██║██║   ██║    ██╔══╝   ██╔██╗    ██║   
#       ╚███╔███╔╝███████╗██║ ╚████║╚██████╔╝    ███████╗██╔╝ ██╗   ██║   
#        ╚══╝╚══╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   
# ===========================================================================                                                                                                                                                        
# License
#    This file is part of WENO Ext.
#
#    WENO Ext is free software: you can redistribute it and/or modify it
#    under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    WENO Ext is distributed in the hope that it will be useful, but WITHOUT
#    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#    for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with  WENO Ext.  If not, see <http://www.gnu.org/licenses/>.
#
#
# Author
#   Jan Wilhelm Gärtner <jan.gaertner@outlook.de> Copyright (C) 2020
#
# ===========================================================================
# CMake File for WENOEXT Project
# CMake is used instead of OpenFOAM standard wmake as it allows 
# for some more flexibility between the different OpenFOAM distributions
# without writing extensive bash scripts to do this 
# Further, it integrates directly with Catch2 and the Blaze library if
# needed
# ===========================================================================

cmake_minimum_required (VERSION 3.10)

# Project name 
project (WENOEXT-PerformanceTest)

# Enforce C++ 14 standard
# C++ 14 is required for blaze
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set minimum gnu compiler version
set(GNU_MIN_VERSION 7.5.0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (NOT CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL ${GNU_MIN_VERSION})
        message(WARNING "GNU compiler version ${CMAKE_CXX_COMPILER_VERSION} is below ${GNU_MIN_VERSION}")
    endif()
endif()



# Check that OpenFoam environment variables are available
if (NOT DEFINED ENV{FOAM_USER_LIBBIN} OR NOT DEFINED ENV{FOAM_SRC})
    message(FATAL_ERROR "OpenFOAM environemt variables not available")
endif()


#===============================================================================
#   Create Version File
#===============================================================================

# Get current git commit
#execute_process(
    #COMMAND  git rev-parse --abbrev-ref HEAD
    #WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    #OUTPUT_VARIABLE GIT_BRANCH
    #OUTPUT_STRIP_TRAILING_WHITESPACE
#)

#execute_process(
    #COMMAND git log -1 --format=%h
    #WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    #OUTPUT_VARIABLE GIT_COMMIT_HASH
    #OUTPUT_STRIP_TRAILING_WHITESPACE
#)

#configure_file(
    #${CMAKE_SOURCE_DIR}/versionRules/version.h.in
    #${CMAKE_BINARY_DIR}/generated/version.h
#)

#include_directories(${CMAKE_BINARY_DIR}/generated)


# Set c++ flags
add_compile_options(
    -m64 
    -mavx2
    -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-deprecated
    -ftemplate-depth-100
    -O3
    )

set(CMAKE_SHARED_LINKER_FLAGS "-fPIC -Xlinker --add-needed -Xlinker --no-as-needed")


add_definitions(-Dlinux64 -DWM_ARCH_OPTION=$ENV{WM_ARCH_OPTION} -DWM_DP -DWM_LABEL_SIZE=$ENV{WM_LABEL_SIZE} -DNoRepository)


#===============================================================================
#                           Add subdirectories
#===============================================================================

add_subdirectory(blaze-3.8)

# Directory to build the library
add_subdirectory(geometryWENO/src)





