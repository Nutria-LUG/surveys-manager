#include <ostream>
#include "survey.hh"

Survey::Survey(unsigned int survey_id,
               const std::string& survey_sensor,
               float survey_value,
               time_t survey_timestamp)
    : id(survey_id),
      sensor(survey_sensor),
      value(survey_value),
      timestamp(survey_timestamp) {}
SurveyError::SurveyError(unsigned int error_id,
                         const std::string& error_value,
                         time_t error_timestamp)
    : id(error_id), value(error_value), timestamp(error_timestamp) { }

std::ostream& operator<<(std::ostream& os, const Survey& survey) {
    os << "{"
       << "\"id\":" << survey.id << ","
       << "\"sensor\":" << survey.sensor << ","
       << "\"value\":" << survey.value << ","
       << "\"timestamp\":" << survey.timestamp << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SurveyError& error) {
    os << "{"
       << "\"id\":" << error.id << ","
       << "\"value\":" << error.value << ","
       << "\"timestamp\":" << error.timestamp << "}";
    return os;
}
