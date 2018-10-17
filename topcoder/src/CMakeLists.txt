cmake_minimum_required (VERSION 2.6)


add_Executable (boiler-plate boiler-plate.cpp)
add_Executable (tchs-2 tchs-2.cpp)
add_Executable (tchs-5 tchs-5.cpp)
add_Executable (tchs-10 tchs-10.cpp)
add_Executable (tchs-15 tchs-15.cpp)
add_Executable (tchs-25 tchs-25.cpp)

#add_Executable (srm-1 srm-1.cpp)
add_Executable (srm-441 srm-441.cpp)
add_Executable (srm-625-div1 srm-625-div1.cpp)
add_Executable (srm-602 srm-602.cpp)


add_Executable (leetcode-oj leetcode-oj.cpp)


# link the libraries
#target_link_libraries (Tutorial ${EXTRA_LIBS})

# add the install targets
install (TARGETS boiler-plate tchs-2 tchs-5 tchs-10 tchs-15 tchs-25 srm-441 srm-625-div1 srm-602 leetcode-oj DESTINATION "${TOP_CODER_RELEASE_DIRECTORY}/bin")