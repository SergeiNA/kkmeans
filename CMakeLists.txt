cmake_minimum_required(VERSION 3.7)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(kkmeans VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(kkmeans VERSION 7.7.7)
endif()


set (EXE_NAME kkmeans)

set (SRC_FILES
                main.cpp
                print.hpp   print.cpp
                utils.hpp   utils.cpp
                )

add_executable(${EXE_NAME} ${SRC_FILES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMP_OPTIONS "-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;\
                    -Wold-style-cast;-Wcast-align;-Wunused;\
                    -Woverloaded-virtual;-Wconversion;\
                    -Wsign-conversion;-Wduplicated-cond")

  if(CMAKE_BUILD_TYPE MATCHES Debug)
      set(CMP_OPTIONS ${CMP_OPTIONS}";-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
      message("debug")
  endif()
else()
  set(CMP_OPTIONS "/W4")
endif()

set_target_properties(${EXE_NAME} ${TEST_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS ${CMP_OPTIONS}
)

target_link_libraries(${EXE_NAME}
        dlib openblas
)

install(TARGETS kkmeans RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikseas@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)




