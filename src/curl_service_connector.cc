#include <sstream>
#include <curl/curl.h>
#include "curl_service_connector.hh"

namespace __CURL_SERVICE_CONNECTOR_INTERNAL__ {
    class auto_curl {
    public:
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
    
    static int writer(
        char *data,
        size_t size,
        size_t nmemb,
        HttpResponse *response) {
        (response -> http_body).append(data, size * nmemb);
        return size * nmemb;  
    }

    HttpResponse perform_call(
        CURL *curl, const std::string& url) {
        HttpResponse response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(response));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);

        auto res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            throw curl_easy_strerror(res);
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,
                          &response.http_code);
        return std::move(response);
    }

    void prepare_post_call(CURL *curl) {
        
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers,
                                    "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    void prepare_post_call(CURL *curl, const std::string& json) {
        prepare_post_call(curl);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
    }
}

HttpResponse::HttpResponse() { }
HttpResponse::HttpResponse(const HttpResponse&& response)
    : http_code(response.http_code),
      http_body(std::move(response.http_body)){ }
HttpResponse::~HttpResponse() { }


CurlServiceConnector::CurlServiceConnector(const std::string& address)
    : _address(address)  { }

CurlServiceConnector::~CurlServiceConnector() { }

HttpResponse CurlServiceConnector::get_call(
    const std::string& method) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;
    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr,
        _get_url(method));
}

HttpResponse CurlServiceConnector::get_call(
    const std::string& method, const std::string& params) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;
    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr,
        _get_url(method, params));
}

HttpResponse CurlServiceConnector::post_call(
    const std::string& method) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;
    __CURL_SERVICE_CONNECTOR_INTERNAL__::prepare_post_call(curl.ptr);
    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr,
        _get_url(method));
}

HttpResponse CurlServiceConnector::post_call(
    const std::string& method, const std::string& json) const {
    __CURL_SERVICE_CONNECTOR_INTERNAL__::auto_curl curl;
    __CURL_SERVICE_CONNECTOR_INTERNAL__::prepare_post_call(curl.ptr,
                                                           json);
    return __CURL_SERVICE_CONNECTOR_INTERNAL__::perform_call(
        curl.ptr,
        _get_url(method));
}

std::string CurlServiceConnector::_get_url(
    const std::string& method) const {
    return _address + "/" + method;
}
std::string CurlServiceConnector::_get_url(
    const std::string& method,
    const std::string& params) const {
    return _address + "/" + method + "?" + params; 
}
