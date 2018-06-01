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

#include<string>

#ifndef CURL_SERVICE_CONNECTOR_INCLUDE_GUARD_HH
#define CURL_SERVICE_CONNECTOR_INCLUDE_GUARD_HH 1

class CurlServiceConnector {
public:
    CurlServiceConnector(const std::string& address);
    ~CurlServiceConnector();

    long int post_call(const std::string& method,
                       const std::string& params) const;
    long int get_call(const std::string& method,
                      const std::string& json) const;
private:
    CurlServiceConnector();
    CurlServiceConnector(const CurlServiceConnector&);
    CurlServiceConnector(const CurlServiceConnector&&);
    std::string _address;
};
#endif
