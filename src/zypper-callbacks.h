/*-----------------------------------------------------------*- c++ -*-\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#ifndef ZYPPER_CALLBACKS_H
#define ZYPPER_CALLBACKS_H

#include <iostream>
#include <string>

#include "zypp/Resolvable.h"
#include "zypp/base/Exception.h"

#include "zypper.h"

/*
enum Error {
    NO_ERROR,
    NOT_FOUND,
    IO,
    INVALID,
};
*/
void display_done ( const std::string &id, std::ostream & out, const std::string& s);
// newline if normal progress is on single line
void display_done ( const std::string &id, std::ostream & out);

//! \todo this must be rewritten as the error enums are different for some zypp callbacks
template<typename Error>
std::string zcb_error2str (Error error, const std::string & reason)
{
  std::string errstr;
  if (error != 0 /*NO_ERROR*/)
  {
    static const char * error_s[] = {
      // TranslatorExplanation These are reasons for various failures.
      "", _("Not found"), _("I/O error"), _("Invalid object")
    };

    // error type:
    if (error < 3)
      errstr += error_s[error];
    else
      errstr += _("Error");
    // description
    if (!reason.empty())
      errstr += ": " + reason;
  }
  
  return errstr;
}

/**
 * Abort, Retry, Ignore stdin prompt.
 * \param default_action Answer to be returned in non-interactive mode. If none
 *    is specified, 0 (ABORT) is returned. In interactive mode, this parameter
 *    is ignored.
 */
int read_action_ari (PromptId pid, int default_action = -1);

/**
 * Prompt for y/n answer (localized) from stdin.
 *
 * \param question Question to be printed on prompt.
 * \param default_answer Value to be returned in non-interactive mode or on
 *      input failure.
 */
bool read_bool_answer(PromptId pid, const std::string & question, bool default_answer);

/**
 * Returns string representation of a resolvable.
 */
std::string to_string (zypp::Resolvable::constPtr resolvable);

/**
 * Prints exception message. If there is exception history available for the
 * exception, this method prints the root cause or the whole history (if
 * verbosity level is >2). Otherwise it just prist the e.asUserString() of the
 * exception passed.
 */
void report_zypp_exception(const zypp::Exception & e);

/**
 * Prints the problem description caused by an exception, its cause and,
 * optionaly, a hint for the user.
 * 
 * \param e Exception which caused the problem.
 * \param Problem description for the user.
 * \param Hint for the user how to cope with the problem.
 */
void report_problem(const zypp::Exception & e,
                    const std::string & problem_desc,
                    const std::string & hint = "");

/**
 * 
 */
void report_too_many_arguments(const std::string & specific_help);

#endif
