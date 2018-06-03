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

/*!
 * \brief This class is used to perform http requests through libcurl.
 */
class CurlServiceConnector {
public:
    /*!
     * \brief Constructor with one parameter.
     * \param address - Address of the service to call.
     *
     * Initialize the connector with the address passed as parameter.
     */    
    CurlServiceConnector(const std::string& address);
    /*! Default destructor. */
    ~CurlServiceConnector();

    /*!
     * Perform a POST http call at the method passed as parameter, to
     * the service specified in the constructor.
     * \param method - Method to call.
     * \return The http response structure.
     *
     * This method perform a call to the service specified in the
     * constructor. It throws exception if curl perform function
     * return a value different from CURLE_OK. Exception thrown is
     * a const char* that contains the message.
     */
    HttpResponse post_call(const std::string& method) const;

    /*!
     * Perform a POST http call at the method passed as parameter, to
     * the service specified in the constructor with the parameters
     * passed.
     * \param method - Method to call.
     * \param json   - JSON parameters to pass to the call.
     * \return The http response structure.
     *
     * This method perform a call to the service specified in the
     * constructor. It throws exception if curl perform function
     * return a value different from CURLE_OK. Exception thrown is
     * a const char* that contains the message.
     */
    HttpResponse post_call(const std::string& method,
                           const std::string& json) const;

    /*!
     * Perform a GET http call at the method passed as parameter, to
     * the service specified in the constructor.
     * \param method - Method to call.
     * \return The http response structure.
     *
     * This method perform a call to the service specified in the
     * constructor. It throws exception if curl perform function
     * return a value different from CURLE_OK. Exception thrown is
     * a const char* that contains the message.
     */
    HttpResponse get_call(const std::string& method) const;

    /*!
     * Perform a GET http call at the method passed as parameter, to
     * the service specified in the constructor with the parameters
     * passed.
     * \param method - Method to call.
     * \param params - String that contains GET parameters: in the
     *                 format key1=value1&key2=value2 ...
     * \return The http response structure.
     *
     * This method perform a call to the service specified in the
     * constructor. It throws exception if curl perform function
     * return a value different from CURLE_OK. Exception thrown is
     * a const char* that contains the message.
     */
    HttpResponse get_call(const std::string& method,
                          const std::string& params) const;

private:

    /*!
     * \brief Gets the url from method string.
     * \param method - Method to call through http.
     * \return A string that represent the url to call through curl.
     *
     * Private utility method used to get url from mehtod. It concats
     * service address with method putting the right '/'.
     */
    std::string _get_url(const std::string& method) const;

    /*!
     * \brief Gets the url from method string.
     * \param method - Method to call through http.
     * \param params - GETS parameters to add.
     * \return A string that represent the url to call through curl
     *         with the parameters specified.
     *
     * Private utility method used to get url from mehtod. It concats
     * service address and GET parameters passed, putting the right
     * separator between theme.
     */
    std::string _get_url(const std::string& method,
                         const std::string& params) const;

    /*! Private not implemented */
    CurlServiceConnector();
    /*! Private not implemented */
    CurlServiceConnector(const CurlServiceConnector&);
    /*! Private not implemented */
    CurlServiceConnector(const CurlServiceConnector&&);

    /*! Host address to call. */
    std::string _address;
};

#endif
