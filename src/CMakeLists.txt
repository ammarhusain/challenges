cmake_minimum_required (VERSION 2.6)


add_Executable (boiler-plate boiler-plate.cpp)
add_Executable (tchs-2 tchs-2.cpp)
add_Executable (tchs-5 tchs-5.cpp)
add_Executable (srm663-div2 srm663-div2.cpp)

# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS boiler-plate tchs-2 tchs-5 srm663-div2 DESTINATION "${PROJECT_EULER_RELEASE_DIRECTORY}/bin")