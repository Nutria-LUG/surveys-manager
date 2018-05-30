#include <sstream>
#include "surveys_service_client.hh"

SurveysServiceClient::SurveysServiceClient(
    CurlServiceConnector *service_connector)
    : _service_connector(service_connector) { }

SurveysServiceClient::~SurveysServiceClient() { }

bool SurveysServiceClient::send_data(
    const std::list<Survey>& surveys) const {
    std::stringstream ss;
    ss  << "[";
    for(auto itr = surveys.begin();
        itr != surveys.end();
        ++itr) {
        if(itr != surveys.begin()) {
            ss << ",\n";
        }
        ss << *itr;
    }
    ss << "]";

    bool ret = true;
    try {
        _service_connector -> post_call(_SEND_DATA_METHOD, ss.str());
    } catch(...) {
        ret = false;
    }
    
    return ret;
}

bool SurveysServiceClient::send_data(
    const std::list<SurveyError>& survey_errors) const {
    std::stringstream ss;

    ss << "[";
    for(auto itr = survey_errors.begin();
        itr != survey_errors.end();
        ++itr) {
        if(itr != survey_errors.begin()) {
            ss << ",\n";
        }
        ss << *itr;
    }
    ss << "]";
    
    bool ret = true;
    try {
        _service_connector -> post_call(_SEND_DATA_METHOD, ss.str());
    } catch(...) {
        ret = false;
    }
    
    return ret;;
}

