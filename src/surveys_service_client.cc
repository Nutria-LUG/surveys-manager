#include <iostream>
#include "surveys_service_client.hh"

SurveysServiceClient::SurveysServiceClient() { }
SurveysServiceClient::~SurveysServiceClient() { }

void SurveysServiceClient::send_data(
    const std::list<Survey>& surveys) const {
    std::cout << "[";
    for(auto itr = surveys.begin();
        itr != surveys.end();
        ++itr) {
        if(itr != surveys.begin()) {
            std::cout << ",\n";
        }
        std::cout << *itr;
    }
    std::cout << "]" << std::endl;
}

void SurveysServiceClient::send_data(
    const std::list<SurveyError>& survey_errors) const {
    std::cout << "[";
    for(auto itr = survey_errors.begin();
        itr != survey_errors.end();
        ++itr) {
        if(itr != survey_errors.begin()) {
            std::cout << ",\n";
        }
        std::cout << *itr;
    }
    std::cout << "]" << std::endl;

}

