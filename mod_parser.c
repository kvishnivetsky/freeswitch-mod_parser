/*.
 * FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Copyright (C) 2005-2014, Anthony Minessale II <anthm@freeswitch.org>
 *
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 *
 * The Initial Developer of the Original Code is
 * Anthony Minessale II <anthm@freeswitch.org>
 * Portions created by the Initial Developer are Copyright (C)
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *.
 * Anthony Minessale II <anthm@freeswitch.org>
 * Neal Horman <neal at wanlink dot com>
 * <Enter your name and e-mail here>
 *
 * mod_parser.c -- XML and JSON parsing applications
 *
 */

#include "mod_parser.h"

/* Prototypes */
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_parser_shutdown);
SWITCH_MODULE_RUNTIME_FUNCTION(mod_parser_runtime);
SWITCH_MODULE_LOAD_FUNCTION(mod_parser_load);

/* SWITCH_MODULE_DEFINITION(name, load, shutdown, runtime).
 * Defines a switch_loadable_module_function_table_t and a static const char[] modname
 */
SWITCH_MODULE_DEFINITION(mod_parser, mod_parser_load, mod_parser_shutdown, NULL);

/*
SWITCH_STANDARD_API(get_json_value_function)
{
	const char * value = NULL;
	int tagc = 0;
	char *mydata = NULL, *tagv[1024] = { 0 } ;
	int i = 0;
	const char *err = NULL;
	switch_xml_t xml_root = NULL, xml = NULL, obj = NULL;

	if (!cmd) {
		err = "Usage: get_json_value <path>";
		goto end;
	}

	mydata = strdup(cmd);
	switch_assert(mydata);
	tagc = switch_separate_string(mydata, ' ', tagv, (sizeof(tagv) / sizeof(tagv[0])));

	if (tagc == 0) {
		err = "Usage: get_json_value <path>";
		goto end;
	}

end:

	free(mydata);
	return SWITCH_STATUS_SUCCESS;
}
*/

SWITCH_STANDARD_API(get_xml_value_function)
{
	const char * value = NULL;
	int tagc = 0;
	char *mydata = NULL, *tagv[1024] = { 0 } ;
	int i = 0;
	const char *err = NULL;
	switch_xml_t xml_root = NULL, xml = NULL, obj = NULL;

	if (!cmd) {
		err = "Usage: get_xml_value <xml> <tag[@param[@value]]> [tag1[@param1[@value1]]] ... <@attribute>";
		goto end;
	}

	mydata = strdup(cmd);
	switch_assert(mydata);
	tagc = switch_separate_string(mydata, ' ', tagv, (sizeof(tagv) / sizeof(tagv[0])));

	if (tagc < 2) {
		err = "Usage: get_xml_value <xml> <tag[@param[@value]]> [tag1[@param1[@value1]]] ... <@attribute>";
		goto end;
	}

	if (!(xml_root = xml = switch_xml_parse_str_dynamic(tagv[0], SWITCH_TRUE))) {
	    err = "Error parsing XML data";
	    goto end;
	}

	for(i=1; i<tagc; i++) {
		value = getXMLNode(tagv[i], xml, &obj);

		if (obj == NULL) {
			obj = xml;
			goto end;
		} else {
			xml = obj;
		}
	}

end:
	if (err) {
		stream->write_function(stream, "-ERR %s\n", err);
	}

	if (obj) {
		//TODO: return real result
		stream->write_function(stream, "%s", value);
	} else {
		err = "Found nothing.";
		stream->write_function(stream, "-ERR %s\n", err);
	}

	switch_xml_free(xml_root);
	free(mydata);
	return SWITCH_STATUS_SUCCESS;
}

SWITCH_STANDARD_API(get_config_value_function)
{
	const char * value = NULL;
	int tagc = 0;
	char *mydata = NULL, *tagv[1024] = { 0 } ;
	int i = 0;
	const char *err = NULL;
	switch_xml_t xml_root = NULL, xml = NULL, obj = NULL;

	if (!cmd) {
		err = "Usage: get_config_value <tag[@param[@value]]> [tag1[@param1[@value1]]] ... <@attribute>";
		goto end;
	}

	mydata = strdup(cmd);
	switch_assert(mydata);
	tagc = switch_separate_string(mydata, ' ', tagv, (sizeof(tagv) / sizeof(tagv[0])));

	if (tagc == 0) {
		err = "Usage: get_config_value <tag[@param[@value]]> [tag1[@param1[@value1]]] ... <@attribute>";
		goto end;
	}

	xml_root = xml = switch_xml_root();
	for(i=0; i<tagc; i++) {
		value = getXMLNode(tagv[i], xml, &obj);

		if (obj == NULL) {
			obj = xml;
			goto end;
		} else {
			xml = obj;
		}
	}

end:
	if (err) {
		stream->write_function(stream, "-ERR %s\n", err);
	}

	if (obj) {
		//TODO: return real result
		stream->write_function(stream, "%s", value);
	} else {
		err = "Found nothing.";
		stream->write_function(stream, "-ERR %s\n", err);
	}

	switch_xml_free(xml_root);
	free(mydata);

	return SWITCH_STATUS_SUCCESS;
}


/* Macro expands to: switch_status_t mod_parser_load(switch_loadable_module_interface_t **module_interface, switch_memory_pool_t *pool) */
SWITCH_MODULE_LOAD_FUNCTION(mod_parser_load)
{
	// TODO: define used interfaces
	switch_api_interface_t *api_interface;

	/* connect my internal structure to the blank pointer passed to me */
	*module_interface = switch_loadable_module_create_module_interface(pool, modname);

	switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "Module mod_parser loading...\n");

//	SWITCH_ADD_API(api_interface, "get_json_value", "Get value from JSON object, encoded to string", get_json_value_function, "<JSON> <path_to_value>");
	SWITCH_ADD_API(api_interface, "get_xml_value", "Get value from XML document, encoded to string", get_xml_value_function, "<XML> <path_to_value>");
	SWITCH_ADD_API(api_interface, "get_config_value", "Get value from XML config", get_config_value_function, "<section> <path_to_value>");

	/* indicate that the module should continue to be loaded */
	return SWITCH_STATUS_SUCCESS;
}

/*
  Called when the system shuts down
  Macro expands to: switch_status_t mod_parser_shutdown()
*/
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_parser_shutdown)
{
	switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "Module mod_parser unloading...\n");
	/* Cleanup dynamically allocated config settings */
	return SWITCH_STATUS_SUCCESS;
}


/*
  If it exists, this is called in it's own thread when the module-load completes
  If it returns anything but SWITCH_STATUS_TERM it will be called again automatically
  Macro expands to: switch_status_t mod_parser_runtime()
SWITCH_MODULE_RUNTIME_FUNCTION(mod_parser_runtime)
{
	while(looping)
	{
	    switch_cond_next();
	}
	return SWITCH_STATUS_TERM;
}
*/

/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4 noet
 */
