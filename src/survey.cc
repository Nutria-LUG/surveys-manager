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
                         const std::string& error_message,
                         time_t error_timestamp)
    : id(error_id),
      message(error_message),
      timestamp(error_timestamp) { }

std::ostream& operator<<(std::ostream& os, const Survey& survey) {
    os << "{"
       << "\"sensor\":" << survey.sensor << ","
       << "\"value\":" << survey.value << ","
       << "\"timestamp\":" << survey.timestamp << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SurveyError& error) {
    os << "{"
       << "\"message\":" << error.message << ","
       << "\"timestamp\":" << error.timestamp << "}";
    return os;
}
