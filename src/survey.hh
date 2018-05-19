#include <string>
#include <ctime>
#include <ostream>

#ifndef SURVEY_INCLUDE_GUARD_HH
#define SURVEY_INCLUDE_GUARD_HH 1

struct Survey {
    unsigned int id;
    std::string  sensor;
    float        value;
    time_t       timestamp;

    Survey(unsigned int survey_id,
           const std::string& survey_sensor,
           float survey_value,
           time_t survey_timestamp);
};
struct SurveyError {
    unsigned int id;
    std::string  value;
    time_t       timestamp;

    SurveyError(unsigned int error_id,
                const std::string& error_value,
                time_t error_timestamp);

};

std::ostream& operator<<(std::ostream& os, const Survey& survey);
std::ostream& operator<<(std::ostream& os,
                         const SurveyError& survey_error);
#endif
