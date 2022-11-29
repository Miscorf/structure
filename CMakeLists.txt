cmake_minimum_required (VERSION 3.23)

project (demo)

# 头文件
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/)
# include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/cyusb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HDF5/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HDF5/include/c)

# 外部库搜索路径
link_directories(${PROJECT_SOURCE_DIR}/HDF5/lib/vc14/x64/release/)
# 枚举源文件
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 输出路径
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
# 链接
set(LINK_LIBS
    hdf5.lib
    ws2_32.lib
)

# 生成dll库
ADD_LIBRARY(include SHARED ${INCLUDES} ${SOURCES})
TARGET_LINK_LIBRARIES(include ${LINK_LIBS})
INSTALL(TARGETS include DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 设置目标属性
SET_TARGET_PROPERTIES(include PROPERTIES LINKER_LANGUAGE CXX
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "uDASAPI"
        PREFIX "")

add_executable(st src/main.cpp ${INCLUDES})
TARGET_LINK_LIBRARIES(st ${LINK_LIBS})
TARGET_LINK_LIBRARIES(st ${CMAKE_CURRENT_SOURCE_DIR}/bin/uDASAPI.dll)
TARGET_LINK_LIBRARIES(st ${CMAKE_CURRENT_SOURCE_DIR}/bin/cyusb.dll)
target_link_libraries(st hdf5.lib)

# add_executable(tst src/test.cpp)
# target_link_libraries(tst hdf5.lib)
# TARGET_LINK_LIBRARIES(tst ${CMAKE_CURRENT_SOURCE_DIR}/bin/uDASAPI.dll)