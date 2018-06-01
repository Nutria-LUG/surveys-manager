#include <sstream>
#include <curl/curl.h>
#include "curl_service_connector.hh"

namespace __CURL_SERVICE_CONNECTOR_INTERNAL__ {
    struct auto_curl {
#ifndef NDEBUG
        FILE *devnull;
#endif
        
        CURL *ptr;
        auto_curl() :
#ifndef NDEBUG
            devnull(fopen("/dev/null", "w+")),
#endif
            ptr(curl_easy_init()) {
#ifndef NDEBUG
            curl_easy_setopt(ptr, CURLOPT_WRITEDATA, devnull);
#endif
        }
        ~auto_curl() {
            curl_easy_cleanup(ptr);
#ifndef NDEBUG
            fclose(devnull);
#endif
        }
    };
    
    long int perform_call(CURL *curl, const std::string& url) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        long http_code = 0;
        auto res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            throw curl_easy_strerror(res);
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return http_code;
    }
}

CurlServiceConnector::CurlServiceConnector(const std::string& address)
    : _address(address)  { }

CurlServiceConnector::~CurlServiceConnector() { }

long int CurlServiceConnector::get_call(
    const std::string& method, const std::string& params) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;    
    std::string url = _address + "/" + method + "?" + params; 

    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr,  url);
}

long int CurlServiceConnector::post_call(
    const std::string& method, const std::string& json) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;
    std::string url = _address + "/" + method; 
    curl_easy_setopt(curl.ptr, CURLOPT_POST, 1);
    
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers,
                                "Content-Type: application/json");
    curl_easy_setopt(curl.ptr, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl.ptr, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl.ptr, CURLOPT_POSTFIELDSIZE, -1L);
  
    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr, url);
}
