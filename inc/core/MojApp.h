/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */


#ifndef MOJAPP_H_
#define MOJAPP_H_

#include "core/MojCoreDefs.h"
#include "core/MojAutoPtr.h"
#include "core/MojMap.h"
#include "core/MojObject.h"
#include "core/MojString.h"
#include "core/MojVector.h"

/**
 * Utility class to handle command line options
 *
 * This class processes various basic program functionality associated with
 * being run from a command line.  Some of the functions it helps cleanly handle
 * include:
 *
 * - General running and interfacing with a terminal.
 * 
 * - Logging.
 *
 * - Displaying help/usage text.
 *
 * - Displaying version information.
 */
class MojApp : private MojNoCopy
{
public:
	/**
	 * Major version of this program.
	 */
	static const MojUInt32 MajorVersion = 1;

	/**
	 * Minor version of this program.
	 */
	static const MojUInt32 MinorVersion = 0;

	/**
	 * Clean up after our app
	 *
	 * Cleans up memory we've allocated, any open files, etc. before an
	 * instance of our class is deleted.
	 */
	virtual ~MojApp();

	/**
	 * Get our app's name
	 *
	 * Gets the name of our app, which is normall determined by the name
	 * of the binary from the command line.
	 *
	 * @return			The name of our app.
	 */
	const MojString& name() const { return m_name; }
	
	/**
	 * Run this command line app and process command line switches
	 *
	 * Handles parsing the command line and dispatching program flow to more
	 * appropriate and easier-to-extend virtual methods which can be
	 * overridden by derivative classes as needed.
	 *
	 * @param	argc		Number of command line arguments we're being passed.
	 * @param	argv		Pointer to array of string pointers for each of the command line arguments being passed.
	 * @return			0 if successful, some other value to indicate an error condition (to be defined by the program being run).
	 */
	virtual int main(int argc, MojChar** argv);

	/**
	 * Loads configuration for this app
	 *
	 * If our app is run with a "-c" option, it means that a chunk of JSON
	 * configuration data is being fed to our app.  This method gives
	 * derived classes a chance to load any applicable data from said
	 * configuration data structure after it's been parsed.
	 *
	 * Derived classes should override this method if they need to load any
	 * configuration information to run.  This method is called just before
	 * {@link open()}.
	 *
	 * The sequence of calling for normal operation is as follows:
	 *
	 * - {@link init()}
	 *
	 * - {@link configure()}
	 *
	 * - {@link open()}
	 *
	 * - {@link run()}
	 *
	 * - {@link close()}
	 *
	 * @param	conf		JSON object of parsed configuration data.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr configure(const MojObject& conf);

	/**
	 * Initialize everything needed to run our app
	 *
	 * Called by {@link main()} just after logging is initialized (so we can
	 * log messages) but before anything else is processed.  Always run,
	 * regardless of which command line switches we're given.
	 *
	 * The sequence of calling for normal operation is as follows:
	 *
	 * - {@link init()}
	 *
	 * - {@link configure()}
	 *
	 * - {@link open()}
	 *
	 * - {@link run()}
	 *
	 * - {@link close()}
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr init();

	/**
	 * Open files and/or connect to things to prepare for normal running
	 *
	 * Called by {@link main()} just after {@link configure()} but before
	 * {@link run()}.  Derived classes should overload this method if they
	 * need to open any files, connect to anything, etc. to prepare for
	 * normal running of the program using {@link run()}.
	 *
	 * The sequence of calling for normal operation is as follows:
	 *
	 * - {@link init()}
	 *
	 * - {@link configure()}
	 *
	 * - {@link open()}
	 *
	 * - {@link run()}
	 *
	 * - {@link close()}
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr open();

	/**
	 * Close any open files and/or connections which were needed for normal running
	 *
	 * Called by {@link main()} to allow derived classes to clean up after
	 * themselves under a normal program run has finished.  Called just
	 * before the end of the program.  Derived classes should overload this
	 * method if they need to close files or connections which were needed
	 * in {@link run()}.
	 *
	 * The sequence of calling for normal operation is as follows:
	 *
	 * - {@link init()}
	 *
	 * - {@link configure()}
	 *
	 * - {@link open()}
	 *
	 * - {@link run()}
	 *
	 * - {@link close()}
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr close();

	/**
	 * Run normally
	 *
	 * Called by {@link main()} when our program has been called with no
	 * additional arguments or arguments which are related to normal running
	 * instead of, for example, displaying help/usage.
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr run();

protected:
	/**
	 * Function to handle a command line option
	 *
	 * @param	name		Name of the option, as given on the command line.
	 * @param	val		Value of the option, as given on the command line.
	 * @return			Error information, in case an error occurs.
	 */
	typedef MojErr (MojApp::*OptionHandler)(const MojString& name, const MojString& val);

	/**
	 * Array of strings
	 */
	typedef MojVector<MojString> StringVec;
	
	/**
	 * Constructor
	 *
	 * The constructor is defined as protected so it has to be called by any
	 * class which derives from this one.  This is where we get information
	 * about the version of this program.
	 *
	 * @param	majorVersion	Major numeric version of our program.
	 * @param	minorVersion	Minor numeric version of our program.
	 * @param	versionString	Optional full text version of our program, which can inclue alpha or beta status.
	 */
	MojApp(MojUInt32 majorVersion = MajorVersion, MojUInt32 minorVersion = MinorVersion, const MojChar* versionString = NULL);

	/**
	 * Register a command line option handling function
	 *
	 * When the command line is parsed, we go through looking for options
	 * (command line parameters) to process.  When an option is encountered,
	 * it looks through the list of registered option handlers to find one
	 * that matches the given option.  If there is an option handler, it
	 * calls it.
	 *
	 * That's where this method comes in.  Call it to register a new option
	 * with the command line parser.
	 *
	 * @param	handler		Function to call when the specified option is encountered.
	 * @param	opt		String containing the full option name which triggers this function.  Example: "-h"
	 * @param	help		String of information about how to properly use this option which can be displayed to the user on the command line when they specify a "help" option.
	 * @param	argRequired	Whether or not this option requires a value.  If it's a simple switch for presence of an option vs. absence, this would be left at false.
	 * @return			Error information, if applicable.
	 */
	MojErr registerOption(OptionHandler handler, const MojChar* opt, const MojChar* help, bool argRequired = false);

	/**
	 * Outputs a message to the terminal
	 *
	 * Outputs an optionally-formatted message to the terminal.  Basically
	 * a wrapper for printf.
	 *
	 * @param	format		Message, possibly containing printf-style format specifiers.
	 * @param	...		Any variables which could be combined into printf-style format specifiers contained in format.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr displayMessage(const MojChar* format, ...) MOJ_FORMAT_ATTR((printf, 2, 3));

	/**
	 * Displays an error message to the terminal
	 *
	 * If an error message has not already been displayed, this method
	 * outputs a given error message to the user via the terminal's stdout.
	 *
	 * If an error message has already been displayed, this method does not
	 * display the given message.
	 *
	 * Error messages are in the format:
	 *
	 * (Program name): (prefix) -- (errToDisplay)
	 *
	 * @param	prefix		Prefix for the error message (see message format above).
	 * @param	errToDisplay	Error message to display.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr displayErr(const MojChar* prefix, const MojChar* errToDisplay);

	/**
	 * Displays information about a given MojErr
	 *
	 * Displays an error message based on a {@link MojErr} value.
	 * Basically, this method translates the {@link MojErr} into a readable
	 * string and outputs it to the terminal's stdout via
	 * {@link displayErr()}.  Provides a very easy method to tell the user
	 * what went wrong when all we have to go on is a {@link MojErr} which
	 * has been returned to us.
	 *
	 * @param	errToDisplay	MojErr value to translate.
	 * @param	message		Prefix for error message - see format of error messages in {@link displayErr}.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr displayErr(MojErr errToDisplay, const MojChar* message);

	/**
	 * Displays the information from the loggers registered with MojLogEngine
	 *
	 * Goes through each of the loggers registered with {@link MojLogEngine}
	 * and displays their information to the command line.
	 *
	 * @see MojLogEngine
	 *
	 * @return			Error information, if available.
	 */
	virtual MojErr displayLoggers();

	/**
	 * Displays a very basic line explaining how to pass options to our program
	 *
	 * Normal format of the text which is output is as follows:
	 *
	 * usage: (program name) [OPTIONS]
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr displayUsage();

	/**
	 * Displays a list of available command line options
	 *
	 * This method goes through the list of handlers registered using
	 * {link registerOption()} and displays information on how to use them
	 * on the command line
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr displayOptions();
	
	/**
	 * Displays the name of the program, version, and a copyright notice
	 *
	 * @return			Error information, in case an error occurs.
	 */
	virtual MojErr displayVersion();

	/**
	 * Parses the command line
	 *
	 * - Determines the name of the app using the name of the binary.
	 *
	 * - Locates command line switches which can be handled by a handler
	 *   which has been registered using {@link registerOption()} and hands
	 *   them off to said handler function.
	 *
	 * - Hands any unrecognized command line options to {@link handleArgs()}.
	 *
	 * @param	argc		Number of command line arguments.
	 * @param	argv		Pointer to array of strings for each command line argument.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr handleCommandLine(int argc, MojChar** argv);

	/**
	 * Handles any command line arguments for which a handler has not been registered
	 *
	 * The normal method of handling command line switches is for a derived
	 * class to call {@link registerOption()}, but if an option is specified
	 * on the command line and no handler has been registered for it, the
	 * parsed arguments are handed to this method.
	 *
	 * @param	args		Array of arguments which cannot be handled through standard means.
	 * @return			Error information, if applicable.
	 */
	virtual MojErr handleArgs(const StringVec& args);

protected:
	/**
	 * Trace log for debugging
	 */
	static MojLogger s_log;

private:
	enum RunMode {
		ModeDefault,
		ModeHelp,
		ModeLoggers,
		ModeVersion
	};
	struct Option {
		Option(OptionHandler handler, const MojString& help, bool argRequired)
		: m_handler(handler), m_help(help), m_arg(argRequired) {}
		bool operator<(const Option& rhs) const { return m_help < rhs.m_help; }

		OptionHandler m_handler;
		MojString m_help;
		bool m_arg;
	};
	typedef MojMap<MojString, Option, const MojChar*> OptHandlerMap;

	MojErr handleConfig(const MojString& name, const MojString& val);
	MojErr handleHelp(const MojString& name, const MojString& val);
	MojErr handleLoggers(const MojString& name, const MojString& val);
	MojErr handleVersion(const MojString& name, const MojString& val);
	MojErr loadConfig(const MojChar* path);

	MojString m_name;
	OptHandlerMap m_optMap;
	MojObject m_conf;
	RunMode m_runMode;
	bool m_errDisplayed;
	MojUInt32 m_majorVersion;
	MojUInt32 m_minorVersion;
	const MojChar* m_versionString;
};

#endif /* MOJAPP_H_ */
