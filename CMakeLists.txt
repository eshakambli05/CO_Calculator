cmake_minimum_required(VERSION 3.19)
project(COAttainmentSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(COAttainmentSystem
    main.cpp
    MainWindow.cpp
    MainWindow.h
    mainwindow.ui

    DatabaseManager.cpp
    DatabaseManager.h
    Faculty.cpp
    Faculty.h
    Course.cpp
    Course.h
    CourseOutcome.cpp
    CourseOutcome.h
    ProgramOutcome.cpp
    ProgramOutcome.h
    ProgramSpecificOutcome.cpp
    ProgramSpecificOutcome.h
    Exam.cpp
    Exam.h
    Student.cpp
    Student.h
    COCalculator.cpp
    COCalculator.h
    ReportGenerator.cpp
    ReportGenerator.h
)

target_link_libraries(COAttainmentSystem PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::PrintSupport
)
