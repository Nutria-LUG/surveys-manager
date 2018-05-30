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
 * \brief     This file contains the service client used to send surveys to the server.
 * \copyright GNU Public License.
 * \author    NutriaLUG
 *
 * This file contains the service client used to send surveys to the
 * server. A service client is an object that perform the data
 * connection with a remote server.
 */

#ifndef SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH
#define SURVEYS_SERVICE_CLIENT_INCLUDE_GUARD_HH 1

#include <list>
#include "survey.hh"
#include "curl_service_connector.hh"


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
     */
    SurveysServiceClient(CurlServiceConnector *service_connector);

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

    const std::string _SEND_DATA_METHOD = "SaveData";
    CurlServiceConnector *_service_connector;
};

#endif
