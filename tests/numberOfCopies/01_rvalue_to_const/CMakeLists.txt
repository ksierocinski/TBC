set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

qt5_wrap_cpp(01_rvalue_to_const_QT_SRC QTReceiver.h QTSender.h)

add_executable(01_rvalue_to_const_QT_copies QT.cpp ${01_rvalue_to_const_QT_SRC})
target_link_libraries(01_rvalue_to_const_QT_copies Qt5::Core)

add_executable(01_rvalue_to_const_TBC_copies TBC.cpp)
target_link_libraries(01_rvalue_to_const_TBC_copies TBC)
