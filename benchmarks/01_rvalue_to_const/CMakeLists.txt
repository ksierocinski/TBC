set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(01_rvalue_to_const_QT_SRC QTReceiver.h QTSender.h)

add_executable(01_rvalue_to_const_QT QT.cpp ${01_rvalue_to_const_QT_SRC})
target_link_libraries(01_rvalue_to_const_QT Qt5::Core)

add_executable(01_rvalue_to_const_TBC TBC.cpp)
target_link_libraries(01_rvalue_to_const_TBC TBC)
