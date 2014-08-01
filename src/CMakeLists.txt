cmake_minimum_required (VERSION 2.6)


add_Executable (pe1 pe1.cpp)
add_Executable (pe2 pe2.cpp)
# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS pe1 pe2 DESTINATION "${PROJECT_EULER_RELEASE_DIRECTORY}/bin")