set(rummikub_SOURCES
  bots.cpp
  game.cpp
  main.cpp
  sequence.cpp
  tile.cpp
  tile_map.cpp
  )

set(rummikub_HEADERS
  game.hpp
  lexical_cast.hpp
  sequence.hpp
  tile.hpp
  tile_map.hpp
  wrapper.hpp
  )

add_executable(rummikub ${rummikub_SOURCES})
target_link_libraries(rummikub allegro allegro_image allegro_primitives allegro_audio allegro_acodec)

add_custom_target(resources ${CMAKE_COMMAND};-E;copy_directory;${CMAKE_SOURCE_DIR}/resources;resources)
add_dependencies(rummikub resources)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES resources)
