function(download_external_project project_name)
  include(CMakeParseArguments)

  set(_dep_flags
    NO_UPDATE)
  set(_dep_one_variables
    URL
    TAG
    BACKEND
    THIRD_PARTY_DIR
    PATCH
    )

  set(_dep_multi_variables)

  cmake_parse_arguments(_dep_args
    "${_dep_flags}"
    "${_dep_one_variables}"
    "${_dep_multi_variables}"
    ${ARGN}
    )

  if(NOT _dep_args_URL)
    message(FATAL_ERROR "You have to provide a URL for the project ${project_name}")
  endif()

  if(_dep_args_BACKEND)
    set(_ep_backend ${_dep_args_BACKEND}_REPOSITORY ${_dep_args_URL})
  else()
    set(_ep_backend URL ${_dep_args_URL} DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  endif()

  if(_dep_args_TAG)
    set(_ep_tag "${_dep_args_BACKEND}_TAG ${_dep_args_TAG}")
  endif()


  if (NOT _dep_args_THIRD_PARTY_DIR)
    set(_dep_args_THIRD_PARTY_DIR deps)
  endif()

  if (_dep_args_PATCH)
    find_program(PATCH_EXECUTABLE patch REQUIRED)
    set(_patch_cmd PATCH_COMMAND ${PATCH_EXECUTABLE} -p1 < "${PROJECT_SOURCE_DIR}/${_dep_args_THIRD_PARTY_DIR}/${_dep_args_PATCH}")
  endif()

  set(_src_dir ${PROJECT_SOURCE_DIR}/${_dep_args_THIRD_PARTY_DIR}/${project_name})
  if(EXISTS ${_src_dir}/.DOWNLOAD_SUCCESS AND _dep_args_NO_UPDATE)
    return()
  endif()

  set(_working_dir ${PROJECT_BINARY_DIR}/${_dep_args_THIRD_PARTY_DIR}/${project_name}-download)
  set(_cmake_lists ${_working_dir}/CMakeLists.txt)
  file(WRITE  ${_cmake_lists} "cmake_minimum_required(VERSION 3.1)\n")
  file(APPEND ${_cmake_lists} "project(${project_name}-download NONE)\n")
  file(APPEND ${_cmake_lists} "include(ExternalProject)\n")
  file(APPEND ${_cmake_lists} "ExternalProject_Add(${project_name}\n")
  file(APPEND ${_cmake_lists} "    SOURCE_DIR ${_src_dir}\n")
  file(APPEND ${_cmake_lists} "    BINARY_DIR ${_working_dir}\n")
  file(APPEND ${_cmake_lists} "    ${_ep_backend}\n")
  file(APPEND ${_cmake_lists} "    ${_ep_tag}\n")
  file(APPEND ${_cmake_lists} "    CONFIGURE_COMMAND \"\"\n")
  file(APPEND ${_cmake_lists} "    BUILD_COMMAND     \"\"\n")
  file(APPEND ${_cmake_lists} "    INSTALL_COMMAND   \"\"\n")
  file(APPEND ${_cmake_lists} "    TEST_COMMAND      \"\"\n")
  file(APPEND ${_cmake_lists} "    ${_patch_cmd}\n")
  file(APPEND ${_cmake_lists} "LOG_BUILD 1)")

  message(STATUS "Downloading ${project_name} ${_dep_args_GIT_TAG}")
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE _result
    WORKING_DIRECTORY ${_working_dir}
    OUTPUT_FILE ${_working_dir}/download-out.log
    ERROR_FILE ${_working_dir}/download-error.log)

  if(_result)
    message(FATAL_ERROR "Something went wrong (${_result}) during the download"
      " process of ${project_name} check the file"
      " ${_working_dir}/download-error.log for more details:")
    file(STRINGS "${_working_dir}/download-error.log" ERROR_MSG)
    message("${ERROR_MSG}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE _result
    WORKING_DIRECTORY ${_working_dir}
    OUTPUT_FILE ${_working_dir}/build-out.log
    ERROR_FILE ${_working_dir}/build-error.log)

  if(_result)
    message(FATAL_ERROR "Something went wrong (${_result}) during the download"
      " process of ${project_name} check the file"
      " ${_working_dir}/build-error.log for more details")
  endif()

  file(WRITE ${_src_dir}/.DOWNLOAD_SUCCESS "")
endfunction()

# ------------------------------------------------------------------------------
function(mark_as_advanced_prefix prefix)
  get_property(_list DIRECTORY PROPERTY VARIABLES)
  foreach(_var ${_list})
    if("${_var}" MATCHES "^${prefix}")
      mark_as_advanced(${_var})
    endif()
  endforeach()
endfunction()

# ------------------------------------------------------------------------------
function(add_external_package package)
  include(CMakeParseArguments)


  set(_aep_flags
    IGNORE_SYSTEM
    )
  set(_aep_one_variables
    VERSION
    THIRD_PARTY_DIR
    )
  set(_aep_multi_variables)

  cmake_parse_arguments(_aep_args
    "${_aep_flags}"
    "${_aep_one_variables}"
    "${_aep_multi_variables}"
    ${ARGN}
    )

  if(_aep_args_VERSION)
    set(_${package}_version ${_aep_args_VERSION})
  endif()

  if (NOT _aep_args_THIRD_PARTY_DIR)
    set(_aep_args_THIRD_PARTY_DIR deps)
  endif()


  set(_cmake_includes ${PROJECT_SOURCE_DIR}/${_aep_args_THIRD_PARTY_DIR})
  set(_${package}_external_dir ${PROJECT_BINARY_DIR}/${_aep_args_THIRD_PARTY_DIR})


  if(NOT EXISTS ${_cmake_includes}/${package}.cmake)
    set(_required REQUIRED)
  endif()

  if(NOT _aep_args_IGNORE_SYSTEM)
    find_package(${package} ${_${package}_version} ${_required} ${_aep_UNPARSED_ARGUMENTS} QUIET)
    if(${package}_FOUND AND NOT ${package}_FOUND_EXTERNAL)
      string(TOUPPER ${package} u_package)
      mark_as_advanced_prefix(${package})
      mark_as_advanced_prefix(${u_package})
      return()
    endif()
  endif()

  if(EXISTS ${_cmake_includes}/${package}.cmake)
    include(${_cmake_includes}/${package}.cmake)
  endif()
  string(TOUPPER ${package} u_package)
  mark_as_advanced_prefix(${package})
  mark_as_advanced_prefix(${u_package})
endfunction()

function(quote_arguments var)
  set(_quoted "")
  foreach(_arg ${ARGN})
    if(_quoted)
      set(_quoted "${_quoted}, \"${_arg}\"")
    else()
      set(_quoted "\"${_arg}\"")
    endif()
  endforeach()

  if(${var})
    set(${var} "${${var}}, ${_quoted}" PARENT_SCOPE)
  else()
    set(${var} "${_quoted}" PARENT_SCOPE)
  endif()
endfunction()
