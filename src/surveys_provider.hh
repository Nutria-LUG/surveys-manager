#include <sqlite3.h>
#include <string>
#include <list>
#include "survey.hh"

#ifndef SOURVAYS_PROVIDER_INCLUDE_GUARD_HH
#define SOURVAYS_PROVIDER_INCLUDE_GUARD_HH 1

class SqliteSurveysProvider {
public:
    explicit SqliteSurveysProvider(const std::string& db_path);
    ~SqliteSurveysProvider();

    std::list<Survey> get_surveys(unsigned int top) const;

    std::list<SurveyError> get_errors(unsigned int top) const;

    void remove_data(const std::list<Survey>& surveys);
    void remove_data(const std::list<SurveyError>& errors);
private:
    SqliteSurveysProvider();
    SqliteSurveysProvider(const SqliteSurveysProvider&);
    SqliteSurveysProvider(const SqliteSurveysProvider&&);


    const std::string _SURVEYS_TABLE_NAME = "surveys";
    const std::string _ERRORS_TABLE_NAME = "errors";
    
    /*! Pointer to the sqlite3 data base connector. */
    sqlite3 *_db;
};
#endif
