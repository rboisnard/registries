# Ensures that we do an out of source build

function(check_out_of_source_build)
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" in_source)
  get_filename_component(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PARENTDIR}" in_source_subdir)
  if(in_source OR in_source_subdir)
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build.")
  endif(in_source OR in_source_subdir)
endfunction(check_out_of_source_build)