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
 * utils.c -- Utils for mod_parser
 *
 */

#include "utils.h"

/*
    Utility functions BEGIN
*/

SWITCH_DECLARE(const char *) getXMLNode(const char *tag, switch_xml_t xml, switch_xml_t *obj_out)
{
	int pc = 0;
	char *mydata = NULL, *pv[1024] = { 0 };

	if (!tag) {
//		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Tag descriptor should not by empty");
		return NULL;
	}

	mydata = strdup(tag);
	switch_assert(mydata);
	pc = switch_separate_string(mydata, '@', pv, (sizeof(pv) / sizeof(pv[0])));

	if (!(pc == 3 || pc == 1 || (pc == 2 && tag[0] == '@'))) {
//		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Tag descriptor [%s] should be described by 1 value or 3 values, separated by @", tag);
		free(mydata);
		return NULL;
	}

	if (pc == 1) {
//		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Searching for tag[%s]", pv[0]);
		if ((*obj_out = switch_xml_child(xml, pv[0])) != NULL) {
//			switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Tag [%s] found", tag);
			free(mydata);
			return NULL;
		}
	}
	if (pc == 2 && tag[0] == '@') {
//		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Searching for attribute[%s]", tag+1);
		return switch_xml_attr(xml, tag+1);
	}
	if (pc == 3) {
//		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Searching for tag[%s] attr[%s] value[%s]", pv[0], pv[1], pv[2]);
		if ((*obj_out = switch_xml_find_child(xml, pv[0], pv[1], pv[2])) != NULL) {
//			switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Tag [%s] found", tag);
			free(mydata);
			return NULL;
		}
	}

	free(mydata);
	return NULL;
}

/*
    Utility functions END
*/
