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
 * \file      surveys_provider.hh
 * \brief     This file contains definition of the surveys provider.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the surveys provider that use
 * sqlite3 to get data.
 * It is used to retrieve surveys and errors data and remove theme.
 */


#include <sqlite3.h>
#include <string>
#include <list>
#include "survey.hh"

#ifndef SOURVAYS_PROVIDER_INCLUDE_GUARD_HH
#define SOURVAYS_PROVIDER_INCLUDE_GUARD_HH 1

/*!
 * \brief This is a data provider that use sqlite3 as engine.
 *
 * This data provider is used to retrive surveys and errors data
 * structure.
 * It also give the api to remove a list of that structures. This
 * functionality is used to remove theme when send operation success.
 */
class SqliteSurveysProvider {
public:
    /*!
     * \brief Constructor with one parameter.
     *
     * Initialize the provider opening a sqlite3 connection to the
     * database file passed as parameter.
     * \param db_path - File path to a sqlite3 data base.
     */
    explicit SqliteSurveysProvider(const std::string& db_path);

    /*!
     * \brief Virtual destructor.
     *
     * Destroy the provider closing the sqlite3 connection.
     */
    virtual ~SqliteSurveysProvider();

    /*!
     * \brief Gets the surveys.
     *
     * Gets the top surveys specified as parameter. Avoid retrieving
     * of all surveys is used for memory save purpose.
     * \paramm top - Number of surveys to retrieve. They are retrieved
     *               ordered by timestamp.
     * \return The list of top surveys specified as parameter ordered
     *         by timestamp.
     */
    std::list<Survey> get_surveys(unsigned int top) const;

    /*!
     * \brief Gets the errors.
     *
     * Gets the top surveys errors specified as parameter. Avoid
     * retrieving of all data is used for memory save purpose.
     * \paramm top - Number of errors to retrieve. They are retrieved
     *               ordered by timestamp.
     * \return The list of top errors specified as parameter ordered
     *         by timestamp.
     */
    std::list<SurveyError> get_errors(unsigned int top) const;

    /*!
     * \brief Remove data from dta base.
     *
     * Remove the surveys passed as parameter from >the database. 
     * \paramm surveys - List of surveys to remove.
     */
    void remove_data(const std::list<Survey>& surveys);

    /*!
     * \brief Remove data from dta base.
     *
     * Remove the survey's errors  passed as parameter from the
     * database. 
     * \paramm errors - List of errors to remove.
     */
    void remove_data(const std::list<SurveyError>& errors);
private:
    /*! Private not implemented. */
    SqliteSurveysProvider();
    /*! Private not implemented. */
    SqliteSurveysProvider(const SqliteSurveysProvider&);
    /*! Private not implemented. */
    SqliteSurveysProvider(const SqliteSurveysProvider&&);

    /*! Name of the surveys table. */
    const std::string _SURVEYS_TABLE_NAME = "surveys";
    /*! Name of the errors table. */
    const std::string _ERRORS_TABLE_NAME = "errors";
    
    /*! Pointer to the sqlite3 data base connector. */
    sqlite3 *_db;
};
#endif
