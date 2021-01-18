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

/* backward compat macros */

#if !defined(uint32)
typedef unsigned int uint32;
#endif

#if !defined(uint64)
typedef unsigned long long uint64;
#endif

#ifndef TSRMLS_CC
#define TSRMLS_FETCH()
#define TSRMLS_CC
#define TSRMLS_DC
#define TSRMLS_D
#define TSRMLS_C
#endif

#ifndef ZVAL_EMPTY_ARRAY
#define ZVAL_EMPTY_ARRAY(value)         array_init(value)
#endif

#ifndef RETVAL_EMPTY_ARRAY
#define RETVAL_EMPTY_ARRAY()            ZVAL_EMPTY_ARRAY(return_value)
#endif

#ifndef RETURN_EMPTY_ARRAY
#define RETURN_EMPTY_ARRAY()            do { RETVAL_EMPTY_ARRAY(); return; } while (0)
#endif

#ifndef IS_MIXED
# define IS_MIXED 0
#endif

#ifndef ZEND_ARG_INFO_WITH_DEFAULT_VALUE
#define ZEND_ARG_INFO_WITH_DEFAULT_VALUE(pass_by_ref, name, default_value) \
    ZEND_ARG_INFO(pass_by_ref, name)
#endif

#if PHP_VERSION_ID < 70200
#undef ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
    static const zend_internal_arg_info name[] = { \
        { (const char*)(zend_uintptr_t)(required_num_args), ( #class_name ), 0, return_reference, allow_null, 0 },
#endif

#ifndef ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX
# define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
    ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, class_name, allow_null)
#endif

#ifndef ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX
# define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(name, return_reference, num_args, type) \
    ZEND_BEGIN_ARG_INFO_EX(name, 0, return_reference, num_args)
#endif

#ifndef ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX
# define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) \
    ZEND_BEGIN_ARG_INFO_EX(name, 0, return_reference, required_num_args)
#endif

#ifndef ZEND_ARG_TYPE_MASK
# define ZEND_ARG_TYPE_MASK(pass_by_ref, name, type_mask, default_value) \
    ZEND_ARG_TYPE_INFO(pass_by_ref, name, 0, 0)
#endif

#ifndef ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE
# define ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(pass_by_ref, name, type_hint, allow_null, default_value) \
    ZEND_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null)
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
