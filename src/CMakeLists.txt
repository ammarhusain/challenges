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
add_Executable (pe13 pe13.cpp)
add_Executable (pe14 pe14.cpp)
add_Executable (pe15 pe15.cpp)
add_Executable (pe16 pe16.cpp)

add_Executable (pe18 pe18.cpp)

add_Executable (pe20 pe20.cpp)

add_Executable (pe22 pe22.cpp)


add_Executable (pe25 pe25.cpp)


add_Executable (pe28 pe28.cpp)

add_Executable (pe30 pe30.cpp)
add_Executable (pe31 pe31.cpp)


add_Executable (pe34 pe34.cpp)


add_Executable (matterport_1 matterport_1.cpp)
add_Executable (matterport_2 matterport_2.cpp)
add_Executable (matterport_3 matterport_3.cpp)


# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS pe1 pe2 pe3 pe4 pe5 pe6 pe7 pe8 pe9 pe10 pe11 pe12 pe13 pe14 pe15 pe16 pe18 pe20 pe22 pe25 pe28 pe30 pe31 pe34 matterport_1 matterport_2 matterport_3 DESTINATION "${PROJECT_EULER_RELEASE_DIRECTORY}/bin")