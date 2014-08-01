cmake_minimum_required (VERSION 2.6)


add_Executable (boiler-plate boiler-plate.cpp)

# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS boiler-plate DESTINATION "${PROJECT_EULER_RELEASE_DIRECTORY}/bin")