#include "configuration.hh"
#include <fstream>
#include <sstream>
#include <istream>

namespace __CONFIGURATION__INTERNAL__NS__ {
    std::string trim(std::string const& source,
                     char const* delims = " \t\r\n") {
        std::string result(source);
        std::string::size_type index = result.find_last_not_of(delims);
        if(index != std::string::npos) {
            result.erase(++index);
        }
        index = result.find_first_not_of(delims);
        if(index != std::string::npos) {
            result.erase(0, index);
        } else {
            result.erase();
        }
        return result;
    }

    std::string get_default_database_path() { 
        std::string path(getenv(OPEN_AIR_HOME_ENV));
        path = path + "/";
        path = path + OPEN_AIR_DATABASE_NAME;
        return path;
    }
}

std::string get_configuration_file_path() {
    std::string path(getenv(OPEN_AIR_HOME_ENV));
    path = path + "/";
    path = path + OPEN_AIR_CONFIGURATION_FILE_NAME;
    return path;
}

ConfigurationData::ConfigurationData()
    : database_path(
        __CONFIGURATION__INTERNAL__NS__::get_default_database_path()) {
}

ConfigurationData::~ConfigurationData() { }

std::istream& operator>>(std::istream& is,
                         ConfigurationData& config) {
    std::string line;
    int posEqual;
    while (std::getline(is, line)) {
        if (!line.length() ||
            line[0] == '#' ||
            line[0] == ';') {
            continue;
        }
        posEqual = line.find('=');
        std::string key = __CONFIGURATION__INTERNAL__NS__::trim(
            line.substr(0, posEqual));
        if (key == DATABASE_PATH_KEY) {
            std::string value = line.substr(posEqual + 1);
            config.database_path =
                __CONFIGURATION__INTERNAL__NS__::trim(value);
        }
    }    
    return is;
}


namespace __CONFIGURATION__INTERNAL__NS__ {
    bool initialized = false;
}

const ConfigurationData& get_configuration() {
    static ConfigurationData data;
    if(!__CONFIGURATION__INTERNAL__NS__::initialized) {
        __CONFIGURATION__INTERNAL__NS__::initialized = true;
        std::string path(getenv(OPEN_AIR_HOME_ENV));
        path = path + "/";
        path = path + OPEN_AIR_CONFIGURATION_FILE_NAME;
        std::fstream config_file(path);
        config_file >> data;
    }
    return data;
}
