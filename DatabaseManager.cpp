#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    m_db.close();
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initialize() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("co_attainment.db");
    if (!m_db.open()) {
        qDebug() << "Database error:" << m_db.lastError().text();
        return false;
    }

    // Create tables if not exist
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Faculty (id INTEGER PRIMARY KEY, name TEXT, email TEXT, department TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS Course (id INTEGER PRIMARY KEY, code TEXT, title TEXT, faculty_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS CourseOutcome (id INTEGER PRIMARY KEY, code TEXT, description TEXT, course_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS ProgramOutcome (id INTEGER PRIMARY KEY, code TEXT, description TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS ProgramSpecificOutcome (id INTEGER PRIMARY KEY, code TEXT, description TEXT, course_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS Exam (id INTEGER PRIMARY KEY, type TEXT, course_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS Student (id INTEGER PRIMARY KEY, name TEXT, roll_no TEXT, course_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS Marks (id INTEGER PRIMARY KEY, student_id INTEGER, exam_id INTEGER, co_id INTEGER, marks REAL)");
    query.exec("CREATE TABLE IF NOT EXISTS COPOMapping (co_id INTEGER, po_id INTEGER, level INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS COPSOMapping (co_id INTEGER, pso_id INTEGER, level INTEGER)");

    // Preload sample data
    query.exec("INSERT OR IGNORE INTO Faculty VALUES (1, 'Dr. John Doe', 'john@univ.edu', 'CSE')");
    query.exec("INSERT OR IGNORE INTO Course VALUES (1, 'CS101', 'Data Structures', 1)");
    query.exec("INSERT OR IGNORE INTO CourseOutcome VALUES (1, 'CO1', 'Understand basics', 1), (2, 'CO2', 'Apply algorithms', 1), (3, 'CO3', 'Analyze complexity', 1)");
    query.exec("INSERT OR IGNORE INTO ProgramOutcome VALUES (1, 'PO1', 'Engineering knowledge'), (2, 'PO2', 'Problem analysis'), (3, 'PO3', 'Design solutions'), (4, 'PO4', 'Conduct investigations'), (5, 'PO5', 'Modern tool usage'), (6, 'PO6', 'Engineer and society'), (7, 'PO7', 'Environment and sustainability'), (8, 'PO8', 'Ethics'), (9, 'PO9', 'Individual and team work'), (10, 'PO10', 'Communication'), (11, 'PO11', 'Project management'), (12, 'PO12', 'Life-long learning')");
    query.exec("INSERT OR IGNORE INTO Exam VALUES (1, 'ISA1', 1), (2, 'ISA2', 1), (3, 'SEA', 1)");
    query.exec("INSERT OR IGNORE INTO Student VALUES (1, 'Alice', '101', 1), (2, 'Bob', '102', 1), (3, 'Charlie', '103', 1), (4, 'David', '104', 1), (5, 'Eve', '105', 1)");
    // Sample marks (e.g., for CO1, ISA1: Alice 80, etc.)
    query.exec("INSERT OR IGNORE INTO Marks VALUES (1, 1, 1, 1, 80), (2, 2, 1, 1, 70), (3, 3, 1, 1, 90), (4, 4, 1, 1, 60), (5, 5, 1, 1, 50)");
    // Add more sample marks similarly...

    return true;
}

QSqlDatabase DatabaseManager::database() const {
    return m_db;
}
