/*!
 * \brief     This file contains the definition of the components and
 *            operators to fill the configuration data structure.
 * \file      configuration.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include <istream>

#ifndef CONFIGURATION_INCLUDE_GUARD_HH
#define CONFIGURATION_INCLUDE_GUARD_HH 1

/*!
 * This macro contains the name of the openair configuration file.
 */
#define OPEN_AIR_CONFIGURATION_FILE_NAME ".openair.conf"

/*!
 * This macro contains the name of the openair database to use.
 */
#define OPEN_AIR_DATABASE_NAME           ".openair.db"

/*!
 * This macro contains the ENV code used to represent the home folder
 * in the current system (see getenv standard function).
 */
#define OPEN_AIR_HOME_ENV                "HOME"

/*!
 * Gets the configuration file path used by the sensor-logger.
 *\return A string that represent the path to the configuarion file.
 */
std::string get_configuration_file_path();

/*!
 * This macro represent the key value of the data base path in the
 * configuration file.
 */
#define DATABASE_PATH_KEY "data_base_path"

/*!
 * Data struct that contains the configuration informations.
 */
struct ConfigurationData {
    /*! 
     * Sqlite3 data base path that contains the database where perform
     * the log operations.
     */
    std::string database_path;
    
    /*! Default constructor. */
    ConfigurationData();

    /*! Default destructor. */
    ~ConfigurationData();
};

/*!
 * \brief This is the operator>> overloading used to initialize the
 *        configuration.
 *
 * Configuration must be passed in the following format:
 *   key = value
 * Where:
 *  key:   Name of the field to configure
 *  value: Value of that field.
 * Each key value pair will be put in the config object passed as
 * parameter.
 * Characters: '#' and ';' are handled as comments.
 *
 * \param is     - Input stream used to initialize the configuration
 *                 object.
 * \param config - Configuration object to initialize.
 * \return istream object passed as parameter to allow chaining.
 */
std::istream& operator>>(std::istream& is, ConfigurationData& config);

/*!
 * \brief Gets the configuration of the application.
 *
 * This functions builds and retrieve the configuration of the
 * application getting it by file .openair.conf in the home folder.
 * Configuration file is read only first time, then data informations
 * are cached. In this way you can call this getter function each time
 * you need don't caring about performance.
 * \return Const reference to the configuration object.
 */
const ConfigurationData& get_configuration();
#endif
