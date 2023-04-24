set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(06_const_to_value_1_to_4_QT_SRC QTReceiver.h QTSender.h)

add_executable(06_const_to_value_1_to_4_QT QT.cpp ${06_const_to_value_1_to_4_QT_SRC})
target_link_libraries(06_const_to_value_1_to_4_QT Qt5::Core)

add_executable(06_const_to_value_1_to_4_TBC TBC.cpp)
target_link_libraries(06_const_to_value_1_to_4_TBC TBC)
