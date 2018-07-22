#include <string>
#include <sqlite3.h>
#include <sstream>

#include "surveys_provider.hh"

namespace __SQLITE__INTERNAL__ {  
    sqlite3* create(const std::string& db_file) {
        sqlite3 *db;
        sqlite3_open(db_file.c_str(), &db);
        return db;
    }

    static int get_surveys_callback(void *list,
                                    int argc,
                                    char **argv,
                                    char **azColName) {
        auto res = (std::list<Survey>*)list;
        unsigned int id = std::stoi(argv[0]);
        float value = std::stof(argv[2]);
        time_t timestamp = std::stoi(argv[3]);
        res -> push_back(Survey(id, argv[1], value, timestamp));
        return 0;
    };

    static int get_surveys_error_callback(
        void *list,
        int argc,
        char **argv,
        char **azColName) {

        auto res = (std::list<SurveyError>*)list;
        unsigned int id = std::stoi(argv[0]);
        time_t timestamp = std::stoi(argv[2]);
        res -> push_back(SurveyError(id, argv[1], timestamp));
        return 0;
    };
    
    template<class ForwardIterator>
    void remove_data(ForwardIterator begin,
                     ForwardIterator end,
                     sqlite3 *db,
                     const std::string& table) {
    
        std::ostringstream cmd;
        bool has_data = false;
        char *zErrMsg = 0;
    
        cmd << "DELETE FROM "
            << table
            << " WHERE ";
        for(auto itr = begin; itr != end; ++itr) {
            if(has_data) {
                cmd << " OR ";
            }
            cmd << "id = " << itr -> id;
            has_data = true;
        }
        cmd << ";";
        
        if(has_data) {
            auto result = sqlite3_exec(
                db,
                cmd.str().c_str(),
                NULL,
                NULL,
                &zErrMsg);
            if(result != SQLITE_OK) {
                throw sqlite3_errmsg(db);
            }
        }
    }
}

SqliteSurveysProvider::SqliteSurveysProvider(
    const std::string& db_path)
    : _db(__SQLITE__INTERNAL__::create(db_path)) { }

SqliteSurveysProvider::~SqliteSurveysProvider() {
    sqlite3_close(_db);
}

std::list<Survey> SqliteSurveysProvider::get_surveys(
    unsigned int top) const {
    std::list<Survey> surveys;
    std::ostringstream query;
    query << "SELECT id, sensor, value, timestamp "
          << "FROM " << _SURVEYS_TABLE_NAME << " "
          << "ORDER BY timestamp "
          << "LIMIT " << top << ";";
    char *zErrMsg = 0;
    auto result = sqlite3_exec(
        _db,
        query.str().c_str(),
        __SQLITE__INTERNAL__::get_surveys_callback,
        &surveys,
        &zErrMsg);
    if(result != SQLITE_OK) {
        throw sqlite3_errmsg(_db);
    }
    return std::move(surveys);
}

std::list<SurveyError> SqliteSurveysProvider::get_errors(
    unsigned int top) const {
    std::list<SurveyError> errors;
    std::ostringstream query;
    query << "SELECT id, value, timestamp "
          << "FROM " << _ERRORS_TABLE_NAME << " "
          << "ORDER BY timestamp "
          << "LIMIT " << top << ";";
    char *zErrMsg = 0;
    auto result = sqlite3_exec(
        _db,
        query.str().c_str(),
        __SQLITE__INTERNAL__::get_surveys_error_callback,
        &errors,
        &zErrMsg);
    if(result != SQLITE_OK) {
        throw sqlite3_errmsg(_db);
    }
    return std::move(errors);
}

void SqliteSurveysProvider::remove_data(
    const std::list<Survey>& survays) {
    __SQLITE__INTERNAL__::remove_data(
        survays.begin(),
        survays.end(),
        _db,
        _SURVEYS_TABLE_NAME);
}

void SqliteSurveysProvider::remove_data(
    const std::list<SurveyError>& errors) {
    __SQLITE__INTERNAL__::remove_data(
        errors.begin(),
        errors.end(),
        _db,
        _ERRORS_TABLE_NAME);
}
