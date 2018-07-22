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
 * \file      survey.hh
 * \brief     File containing suverys data structure.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the data structure used as
 * models for surveys and errors.
 */

#include <string>
#include <ctime>
#include <ostream>

#ifndef SURVEY_INCLUDE_GUARD_HH
#define SURVEY_INCLUDE_GUARD_HH 1

/*!
 * \brief Data structure representing a survey.
 */
struct Survey {
    /*! Id of the survey in the database. */
    unsigned int id;
    /*! Sensor from which survey to have been taken. */
    std::string  sensor;
    /*! Value of the suvey. */
    float        value;
    /*! Timestamp of the suvey. */
    time_t       timestamp;

    /*!
     * \brief Constructor with four parameters.
     *
     * Initialize the struct with the relative values passed as
     * parameter.
     * \param survey_id        - Id to assignt to the survey.
     * \param survey_sensor    - Sensor to assign to the survey.
     * \param survey_value     - Value of the survey.
     * \param survey_timestamp - Timestamp of the survey.
     */
    Survey(unsigned int survey_id,
           const std::string& survey_sensor,
           float survey_value,
           time_t survey_timestamp);
};

/*!
 * \brief Data structure representing a survey's error.
 */
struct SurveyError {
    /*! Id of the error in the database. */
    unsigned int id;
    /*! String that represent or describe the error. */
    std::string  message;
    /*! Timestamp of the error. */
    time_t       timestamp;

    /*!
     * \brief Constructor with three parameters.
     *
     * Initialize the struct with the relative values passed as
     * parameter.
     * \param error_id        - Id to assign to the errore.
     * \param error_value     - Value to asign to the error.
     * \param error_timestamp - Timestamp to assign to the error.
     */
    SurveyError(unsigned int       error_id,
                const std::string& error_value,
                time_t             error_timestamp);

};

/*!
 * \brief ostream operator overload to print survey as json.
 *
 * This overload is used to print the survey passed as parameter as
 * a JSON string.
 *
 * \param os     - ostream where put the output.
 * \param survey - Survey to serialize.
 * \return A ostream reference used to chain purpose.
 */
std::ostream& operator<<(std::ostream& os, const Survey& survey);

/*!
 * \brief ostream operator overload to print error as json.
 *
 * This overload is used to print the error passed as parameter as
 * a JSON string.
 *
 * \param os           - ostream where put the output.
 * \param survey_error - Survey's error to serialize.
 * \return A ostream reference used to chain purpose.
 */
std::ostream& operator<<(std::ostream& os,
                         const SurveyError& survey_error);
#endif
