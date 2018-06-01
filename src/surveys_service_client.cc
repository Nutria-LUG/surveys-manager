#include <sstream>
#include "surveys_service_client.hh"

SurveysServiceClient::SurveysServiceClient(
    CurlServiceConnector *service_connector)
    : _service_connector(service_connector) { }

SurveysServiceClient::~SurveysServiceClient() { }
#include<iostream>

bool SurveysServiceClient::send_data(
    const std::list<Survey>& surveys) const {
    std::stringstream ss;
    ss  << "[";
    for(auto itr = surveys.begin();
        itr != surveys.end();
        ++itr) {
        if(itr != surveys.begin()) {
            ss << ",";
        }
        ss << *itr;
    }
    ss << "]";

    return _service_connector ->
        post_call(_SEND_DATA_METHOD, ss.str()) == SAVED_DATA_CODE;
}

bool SurveysServiceClient::send_data(
    const std::list<SurveyError>& survey_errors) const {
    std::stringstream ss;

    ss << "[";
    for(auto itr = survey_errors.begin();
        itr != survey_errors.end();
        ++itr) {
        if(itr != survey_errors.begin()) {
            ss << ",";
        }
        ss << *itr;
    }
    ss << "]";
    return _service_connector ->
        post_call(_SEND_ERROR_METHOD, ss.str()) == SAVED_DATA_CODE;
}

