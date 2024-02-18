#include "database.h"
#include "orm.h"
#include <string>

namespace service
{
Database::Database(logging::Log* logger)
    : m_maxObjects(10),
      m_numOfObjects(0),
      m_ormObjects(new ORM*[m_maxObjects]),
      m_logger(logger)
{
}

Database::~Database()
{
    for (int i = 0; i < m_numOfObjects; i++)
    {
        delete m_ormObjects[i];
        m_ormObjects[i] = nullptr;
    }

    delete[] m_ormObjects;
    m_ormObjects = nullptr;
}

void Database::addModel(ORM* model)
{
    if ((m_numOfObjects + 1) > m_maxObjects)
    {
        m_logger->error("Cannot add model, limit would be exceeded");
        return;
    }

    m_ormObjects[m_numOfObjects] = model;
    m_numOfObjects++;
}

void Database::initializeDatabase() const
{
    sqlite3* db;
    /* std::string sql = "CREATE TABLE PERSON (" */
    /*                   "ID INT PRIMARY KEY   NOT NULL, " */
    /*                   "NAME           TEXT  NOT NULL, " */
    /*                   "SURNAME        TEXT  NOT NULL, " */
    /*                   "AGE            INT   NOT NULL, " */
    /*                   "ADDRESS        CHAR(50), " */
    /*                   "SALARY         REAL );"; */
    int exit = 0;
    exit     = sqlite3_open("example.db", &db);
    char* errorMessage;

    for (int i = 0; i < m_numOfObjects; i++)
    {
        service::ORM* orm = m_ormObjects[i];
        std::string sql   = orm->createTable();
        std::string name  = orm->tableName();
        char buffer[100];

        exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &errorMessage);

        if (exit != SQLITE_OK)
        {
            std::sprintf(buffer, "Error creating table for %s", name.c_str());
            m_logger->error(buffer);
            sqlite3_free(errorMessage);

            return;
        }

        std::sprintf(buffer, "Succesfully created table for %s", name.c_str());
        m_logger->debug(buffer);
    }
}
} // namespace service
