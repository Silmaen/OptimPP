#
# Copyright (C) 2018 by George Cave - gcave@stablecoder.ca
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

find_program(DOXYGEN_PATH doxygen ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
if (DOXYGEN_PATH)
    execute_process(COMMAND ${DOXYGEN_PATH} --version
                    OUTPUT_VARIABLE DOXYGEN_VERSION)
    message(STATUS "doxygen found version: ${DOXYGEN_VERSION}")
else()
    message(ERROR "doxygen executable needed and not found")
endif()

# Builds doxygen documentation with a default 'Doxyfile.in' or with a specified
# one, and can make the results installable (under the `doc` install target)
#
# ~~~
# Optional Arguments:
#
#
# TARGET_NAME <str>
#   The name to give the doc target. (Default: doc-${PROJECT_NAME})
#
# OUTPUT_DIR <str>
#   The directory to place the generated output. (Default: ${CMAKE_CURRENT_BINARY_DIR}/doc)
#
# DOXYFILE_PATH <str>
#   The given doxygen file to use/process. (Defaults to'${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile')
# ~~~
function(build_docs)
    set(SINGLE_VALUE_KEYWORDS TARGET_NAME DOXYFILE_PATH OUTPUT_DIR)
    cmake_parse_arguments(build_docs "${OPTIONS}" "${SINGLE_VALUE_KEYWORDS}" "${MULTI_VALUE_KEYWORDS}" ${ARGN})

    if(NOT build_docs_DOXYFILE_PATH)
        set(DOXYFILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    elseif(EXISTS ${build_docs_DOXYFILE_PATH})
        set(DOXYFILE_PATH ${build_docs_DOXYFILE_PATH})
    else()
        set(DOXYFILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${build_docs_DOXYFILE_PATH})
    endif()

    if(NOT EXISTS ${DOXYFILE_PATH})
        message(SEND_ERROR "Could not find Doxyfile to use for processing documentation at: ${DOXYFILE_PATH}")
        return()
    endif()

    if(build_docs_OUTPUT_DIR)
        set(OUT_DIR ${build_docs_OUTPUT_DIR})
    else()
        set(OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)
    endif()
    file(MAKE_DIRECTORY ${OUT_DIR})
    if(build_docs_TARGET_NAME)
        set(TARGET_NAME ${build_docs_TARGET_NAME})
    else()
        set(TARGET_NAME doc-${PROJECT_NAME})
    endif()

    add_custom_target(
            ${TARGET_NAME}
            COMMAND ${DOXYGEN_PATH} ${DOXYFILE_PATH}
            WORKING_DIRECTORY ${OUT_DIR}
            VERBATIM)
endfunction()