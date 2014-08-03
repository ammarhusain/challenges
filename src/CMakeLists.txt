cmake_minimum_required (VERSION 2.6)


add_Executable (pe1 pe1.cpp)
add_Executable (pe2 pe2.cpp)
add_Executable (pe3 pe3.cpp)
add_Executable (pe4 pe4.cpp)
add_Executable (pe5 pe5.cpp)
add_Executable (pe6 pe6.cpp)
add_Executable (pe7 pe7.cpp)
add_Executable (pe8 pe8.cpp)
add_Executable (pe9 pe9.cpp)
add_Executable (pe10 pe10.cpp)
add_Executable (pe11 pe11.cpp)
add_Executable (pe12 pe12.cpp)
# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS pe1 pe2 pe3 pe4 pe5 pe6 pe7 pe8 pe9 pe10 pe11 pe12 DESTINATION "${PROJECT_EULER_RELEASE_DIRECTORY}/bin")