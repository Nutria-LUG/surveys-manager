/* openair is an air quality system monitoring.
 * Copyright (C) 2018 Gabriele Labita
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file      curl_service_connector.hh
 * \brief     This file contains the service client used to send
 *            surveys to the server.
 * \copyright GNU Public License.
 * \author    NutriaLUG
 *
 * This file contains the definition of the data strcut and class
 * used to perform get and post calls through libcurl. This connector
 * implementation allow only JSON contents calls.
 */

#include <string>

#ifndef CURL_SERVICE_CONNECTOR_INCLUDE_GUARD_HH
#define CURL_SERVICE_CONNECTOR_INCLUDE_GUARD_HH 1

/*!
 * \brief This structure represent an http response.
 */
struct HttpResponse {
    /*! Typedefinition to represent the returned http code. */
    typedef long int    http_code_t;
    /*! Typedefinition to represent the returned http body. */
    typedef std::string http_body_t;

    /*! Http code of the response. */
    http_code_t http_code;
    /*! Http body of the response. */
    http_body_t http_body;

    /*!
     * \brief Default constructor.
     *
     * Initialize code and body with relatives default values.
     */
    HttpResponse();

    /*!
     * \brief Move constructor.
     *
     * Perform the move of the object passed as parameter for
     * memory optimization purpose.
     */
    HttpResponse(const HttpResponse&& response);

    /*!
     * \brief Default destructor.
     */
    ~HttpResponse();
};

class CurlServiceConnector {
public:
    
    CurlServiceConnector(const std::string& address);
    ~CurlServiceConnector();

    HttpResponse post_call(const std::string& method) const;
    HttpResponse post_call(const std::string& method,
                           const std::string& params) const;

    HttpResponse get_call(const std::string& method) const;
    HttpResponse get_call(const std::string& method,
                      const std::string& json) const;

private:

    std::string _get_url(const std::string& method) const;
    std::string _get_url(const std::string& method,
                         const std::string& params) const;
    
    CurlServiceConnector();
    CurlServiceConnector(const CurlServiceConnector&);
    CurlServiceConnector(const CurlServiceConnector&&);
    std::string _address;
};

#endif
