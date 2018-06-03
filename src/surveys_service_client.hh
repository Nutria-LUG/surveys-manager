/* Survey Manager is used to send surveys to a web server.
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
 * \file      surveys_service_client.hh
 * \brief     This file contains the service client used to send
 *            surveys to the server.
 * \copyright GNU Public License.
 * \author    NutriaLUG
 *
 * This file contains the service client used to send surveys to the
 * server. A service client is an object that perform the data
 * connection with a remote server.
 */

#include <list>
#include "survey.hh"
#include "configuration.hh"
#include "curl_service_connector.hh"


#ifndef SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH
#define SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH 1

/*!
 * \brief This is the service celient used to send errors and surveys
 *        to the server.
 *
 * This is temporaly implemented printing in standard output the json
 * to sent to the server.
 */
class SurveysServiceClient {
public:
    /*!
     * \brief Default constructor.
     *
     * \param configuration     - Configuration structure that
     *                            contains the method's names to call.
     * \param service_connector - Connector used to perform get and/or
     *                            post calls.
     */
    SurveysServiceClient(const ConfigurationData *configuration,
                         CurlServiceConnector *service_connector);
    
    /*!
     * \brief Virtual detructor.
     */
    virtual ~SurveysServiceClient();

    /*!
     * \brief Send data to the server.
     *
     * Send the list of surveys passed as parameter to the server. If
     * operation success it returns true, otherwise returns false.
     * \param surveys - Surveys to send to the server.
     * \return True if operation success, false otherwise.
     */
    bool send_data(const std::list<Survey>& surveys) const;

    /*!
     * \brief Send data to the server.
     *
     * Send the list of errors passed as parameter to the server. If
     * operation success it returns true, otherwise returns false.
     * \param survey_errors - Errors to send to the server.
     * \return True if operation success, false otherwise.
     */
    bool send_data(const std::list<SurveyError>& survey_errors) const;

private:
    SurveysServiceClient();
    /*! Private not implemented. */
    SurveysServiceClient(const SurveysServiceClient&);
    /*! Private not implemented. */
    SurveysServiceClient(const SurveysServiceClient&&);

    /*!
     * This is the http code use for succesfull calls. If a call does
     * not fail on server side, this code to have been returned.
     */
    const HttpResponse::http_code_t _SUCCESS_CODE = 201;
    
    /*!
     * This is the configuration object. It is needed because contains
     * the mehtod's names.
     */
    const ConfigurationData *_configuration;

    /*!
     * This is the service connector used to perform post and get
     * calls.
     */
    CurlServiceConnector *_service_connector;
};

#endif
