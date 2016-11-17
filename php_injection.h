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

#ifndef PHP_INJECTION_H
#define PHP_INJECTION_H

extern zend_module_entry injection_module_entry;
#define phpext_injection_ptr &injection_module_entry

#ifdef PHP_WIN32
#    define PHP_INJECTION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_INJECTION_API __attribute__ ((visibility("default")))
#else
#    define PHP_INJECTION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_INJECTION_VERSION "0.1.0"

ZEND_BEGIN_MODULE_GLOBALS(injection)
ZEND_END_MODULE_GLOBALS(injection)

PHP_MINFO_FUNCTION(injection);

PHP_FUNCTION(injection_is_sqli);
PHP_FUNCTION(injection_is_xss);

#ifdef ZTS
#define INJECTION_G(v) TSRMG(injection_globals_id, zend_injection_globals *, v)
#else
#define INJECTION_G(v) (injection_globals.v)
#endif

#endif    /* PHP_INJECTION_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
