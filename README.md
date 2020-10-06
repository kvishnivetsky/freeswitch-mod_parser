# mod_parser - FreeSWITCH module for XML, JSON encoded data parsing and extraction

## Exported API applications

### get_config_value <element1> [element2] ... [elementN]

Get value, specifed by arguments, from FreeSWITCH XML configuration.

### get_xml_value <XML string> <element1> [element2] ... [elementN]

Get value, specified by arguments, from XML string, specified by first argument.

### get_json_value <JSON string> <element1> [element2] ... [elementN]

Get value, specified by arguments, from JSON string, specified by first argument.

## Build as a part of FreeSWITCH tree

+ `git branch devel-mod_parser`
+ `git checkout devel-mod_parser`
+ `git submodule add -- https://github.com/kvishnivetsky/freeswitch-mod_parser.git src/mod/applications/mod_parser`
+ edit your `configure.ac` and add to `AC_CONFIG_FILES` section `src/mod/applications/mod_parser/Makefile`
+ edit your `modules.conf` and add `applications/mod_parser`
+ build FreeSWITCH as usual: `./bootstrap.sh` and so on....

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

## Keywords

+ FreeSWITCH JSON parser
+ FreeSWITCH XML parser
+ FreeSWITCH dialplan JSON
+ FreeSWITCH dialplan XML
