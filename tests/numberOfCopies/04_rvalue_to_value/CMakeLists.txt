set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(04_rvalue_to_value_QT_SRC QTReceiver.h QTSender.h)

add_executable(04_rvalue_to_value_QT_copies QT.cpp ${04_rvalue_to_value_QT_SRC})
target_link_libraries(04_rvalue_to_value_QT_copies Qt5::Core)

add_executable(04_rvalue_to_value_TBC_copies TBC.cpp)
target_link_libraries(04_rvalue_to_value_TBC_copies TBC)
