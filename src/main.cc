#include <iostream>
#include <list>
#include <iterator>
#include "configuration.hh"
#include "surveys_provider.hh"
#include "surveys_service_client.hh"

const unsigned int TOP = 10;

void send_surveys(SqliteSurveysProvider& provider,
                  const SurveysServiceClient& service_client) {
    std::list<Survey> surveys;
    surveys = provider.get_surveys(TOP);
    while(surveys.size() > 0) {
        service_client.send_data(surveys);
        provider.remove_data(surveys);
        surveys = provider.get_surveys(TOP);
    }    
}

void send_errors(SqliteSurveysProvider& provider,
                 const SurveysServiceClient& service_client) {
    std::list<SurveyError> errors;
    errors = provider.get_errors(TOP);
    while(errors.size() > 0) {
        service_client.send_data(errors);
        provider.remove_data(errors);
        errors = provider.get_errors(TOP);
    }
}

int main() {    
    auto configuration = get_configuration();
    SurveysServiceClient service_client;
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
