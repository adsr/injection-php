/*
  +----------------------------------------------------------------------+
  | injection                                                            |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License"); you  |
  | may not use this file except in compliance with the License. You may |
  | obtain a copy of the License at                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Author: Adam Saponara <as@php.net>                                   |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_injection.h"

#include <libinjection.h>
#include <libinjection_sqli.h>

#if PHP_MAJOR_VERSION >= 7
    #define COMPAT_RETURN_STRINGL(str, len, dup) RETURN_STRINGL(str, len)
    #define COMPAT_STRLEN_DELTA 1
    #define compat_strlen_t size_t
#else
    #define COMPAT_RETURN_STRINGL(str, len, dup) RETURN_STRINGL(str, len, dup)
    #define COMPAT_STRLEN_DELTA 0
    #define compat_strlen_t int
#endif

ZEND_DECLARE_MODULE_GLOBALS(injection)

ZEND_BEGIN_ARG_INFO_EX(arginfo_injection_is_x, 0, 0, 1)
        ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

/* {{{ injection_functions[]
 *
 * Every user visible function must have an entry in injection_functions[].
 */
const zend_function_entry injection_functions[] = {
    PHP_FE(injection_is_sqli,              arginfo_injection_is_x)
    PHP_FE(injection_is_xss,               arginfo_injection_is_x)
#ifdef PHP_FE_END
    PHP_FE_END    /* Must be the last line in injection_functions[] */
#else
    {NULL, NULL, NULL}
#endif
};
/* }}} */

/* {{{ injection_module_entry
 */
zend_module_entry injection_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "injection",
    injection_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(injection),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_INJECTION_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_INJECTION
ZEND_GET_MODULE(injection)
#endif

/* {{{
 * Initialize module globals */
static void _injection_init_globals(zend_injection_globals *g)
{
    memset(g, 0, sizeof(zend_injection_globals));
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(injection)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "injection support", "enabled");
    php_info_print_table_header(2, "extension version", PHP_INJECTION_VERSION);
    php_info_print_table_header(2, "libinjection version", libinjection_version());
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto mixed injection_is_sqli(string sql)
   Return fingerprint if sqli is detected in string. Return FALSE otherwise. */
PHP_FUNCTION(injection_is_sqli)
{
    char *str;
    compat_strlen_t str_len;
    struct libinjection_sqli_state state;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
        return;
    }

    libinjection_sqli_init(&state, str, str_len, FLAG_NONE);
    if (libinjection_is_sqli(&state)) {
        COMPAT_RETURN_STRINGL(state.fingerprint, strlen(state.fingerprint), 1);
    }

    RETURN_FALSE;
}
/* }}} */

/* {{{ proto mixed injection_is_xss(string str)
   Return TRUE xss is detected in string. Return FALSE otherwise. */
PHP_FUNCTION(injection_is_xss)
{
    char *str;
    compat_strlen_t str_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
        return;
    }

    if (libinjection_xss(str, str_len)) {
        RETURN_TRUE;
    }

    RETURN_FALSE;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
