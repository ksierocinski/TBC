set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(07_rvalue_to_value_1_to_4_QT_SRC QTReceiver.h QTSender.h)

add_executable(07_rvalue_to_value_1_to_4_QT QT.cpp ${07_rvalue_to_value_1_to_4_QT_SRC})
target_link_libraries(07_rvalue_to_value_1_to_4_QT Qt5::Core)

add_executable(07_rvalue_to_value_1_to_4_TBC TBC.cpp)
target_link_libraries(07_rvalue_to_value_1_to_4_TBC TBC)
