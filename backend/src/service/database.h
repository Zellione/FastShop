#pragma once

#include "orm.h"
#include "../logging/log.h"
#include <sqlite3.h>

namespace service
{
class Database
{
public:
    Database(logging::Log* logger);
    Database(const Database &other) = delete;
    ~Database();

    void initializeDatabase() const;

    void addModel(ORM* model);

private:
    int m_maxObjects;
    int m_numOfObjects;
    ORM** m_ormObjects;
    logging::Log* m_logger;
};
} // namespace service
