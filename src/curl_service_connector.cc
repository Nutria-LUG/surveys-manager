
#include <curl/curl.h>
#include <sstream>
#include "curl_service_connector.hh"

namespace __CURL_SERVICE_CONNECTOR_INTERNAL__ {
    void perform_call(CURL *curl, const std::string& url) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        auto res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            throw curl_easy_strerror(res);
        }    
    }
}

CurlServiceConnector::CurlServiceConnector(const std::string& address)
    : _address(address),
      _curl(curl_easy_init()) { }

CurlServiceConnector::~CurlServiceConnector() {
    curl_easy_cleanup(_curl);    
}



void CurlServiceConnector::post_call(
    const std::string& method, const std::string& params) const {
    std::string url = _address + "/" + method + "?" + params; 

    curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "GET");
    __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(_curl, url);
}

void CurlServiceConnector::get_call(
    const std::string& method, const std::string& params) const {
    std::string url = _address + "/" + method; 
    
    curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, params);

    __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(_curl, url);
}
