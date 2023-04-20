set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(03_const_to_value_QT_SRC QTReceiver.h QTSender.h)

add_executable(03_const_to_value_QT QT.cpp ${03_const_to_value_QT_SRC})
target_link_libraries(03_const_to_value_QT Qt5::Core)

add_executable(03_const_to_value_TBC TBC.cpp)
target_link_libraries(03_const_to_value_TBC TBC)
