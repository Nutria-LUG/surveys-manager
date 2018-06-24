#include <sstream>
#include <libopenair/curl_service_connector.hh>
#include <libopenair/configuration.hh>
#include "surveys_service_client.hh"

SurveysServiceClient::SurveysServiceClient(
    const openair::ConfigurationData *configuration,
    openair::CurlServiceConnector *service_connector)
    : _configuration(configuration),
      _service_connector(service_connector) { }

SurveysServiceClient::~SurveysServiceClient() { }

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

    auto response = _service_connector -> post_call(
        _configuration -> send_data_method,
        ss.str());
    return response.http_code == _SUCCESS_CODE;
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
    auto response = _service_connector -> post_call(
        _configuration -> send_errors_method,
        ss.str());
    return response.http_code == _SUCCESS_CODE;
}
