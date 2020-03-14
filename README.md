# mod_parser - FreeSWITCH module for XML, JSON encoded data parsing and extraction

## Exported API applications

### get_config_value <element1> [element2] ... [elementN]

Get value, specifed by arguments, from FreeSWITCH XML configuration.

### get_xml_value <XML string> <element1> [element2] ... [elementN]

Get value, specified by arguments, from XML string, specified by first argument.

### get_json_value <JSON string> <element1> [element2] ... [elementN]

Get value, specified by arguments, from JSON string, specified by first argument.

## Build as a part of FreeSWITCH tree

`git submodule add -b devel -- https://github.com/kvishnivetsky/freeswitch-mod_parser src/mod/applications/mod_parser`

Edit `configure.sh` and add `src/mod/applications/mod_parser/Makefile` in `AC_CONFIG_FILES` section.

Edit `modules.conf` and add `applications/mod_parser`.

## Usage examples

CURL response in this examplereturns JSON string:

`
{
  "data":[
    "test2",
    {"test3":"value"}
    ]
}
`

To extract `value` to variable in dialplan use:

`<action application="curl" data="https://api.test.local/get-some-json"/>`

`<action application="set" data="api_result=${get_json_value('${curl_response_data}' data 1 test3)}"/>`
