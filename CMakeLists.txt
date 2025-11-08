cmake_minimum_required(VERSION 3.16)
project(COAttainmentSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)  # For PDF export

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(COAttainmentSystem
    main.cpp
    faculty.cpp
    student.cpp
    course.cpp
    courseoutcome.cpp
    programoutcome.cpp
    programspecificoutcome.cpp
    exam.cpp
    cocalculator.cpp
    reportgenerator.cpp
    mainwindow.cpp
)

target_link_libraries(COAttainmentSystem Qt5::Widgets Qt5::Sql Qt5::PrintSupport)
