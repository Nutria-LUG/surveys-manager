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
 * \file      main.cc
 * \brief     This is the main file of surveys manager.
 * \copyright GNU Public License.
 * \author    NutriaLUG
 *
 * SurveysManager is a program used to send the surveys saved in the
 * sqlite3 data base to the server. It sends logged surveys and errors.
 * Surveys and errors are sent as block to save memory.
 * If send success, the relative data will be removed from the
 * database.
 */

#include <iostream>
#include <list>
#include <iterator>
#include "configuration.hh"
#include "surveys_provider.hh"
#include "curl_service_connector.hh"
#include "surveys_service_client.hh"

const unsigned int TOP = 10;

void send_surveys(SqliteSurveysProvider& provider,
                  const SurveysServiceClient& service_client) {
    std::list<Survey> surveys;
    surveys = provider.get_surveys(TOP);
    while(surveys.size() > 0) {
        if(!service_client.send_data(surveys)) {
            throw "Cannot send data to server";
        }
        provider.remove_data(surveys);
        surveys = provider.get_surveys(TOP);
    }    
}

void send_errors(SqliteSurveysProvider& provider,
                 const SurveysServiceClient& service_client) {
    std::list<SurveyError> errors;
    errors = provider.get_errors(TOP);
    while(errors.size() > 0) {
        if(!service_client.send_data(errors)) {
            throw "Cannot send data to server";
        };
        provider.remove_data(errors);
        errors = provider.get_errors(TOP);
    }
}

int main() {    
    auto configuration = get_configuration();
    CurlServiceConnector connector(configuration.service_address);
    SurveysServiceClient service_client(&connector);
    SqliteSurveysProvider provider(configuration.database_path);
    try {
        send_surveys(provider, service_client);
    } catch(const char* ex){
        std::cout << ex << std::endl;
        return 1;
    }    
    try {
        send_errors(provider, service_client);
    } catch(const char* ex){
        std::cout << ex << std::endl;
        return 1;
    }    
    
    return 0;
}
