
#ifndef SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH
#define SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH 1

#include <list>
#include "survey.hh"

class SurveysServiceClient {
public:
    SurveysServiceClient();
    ~SurveysServiceClient();
    
    void send_data(const std::list<Survey>& surveys) const;
    void send_data(const std::list<SurveyError>& survey_errors) const;
};

#endif
