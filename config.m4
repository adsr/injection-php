PHP_ARG_WITH(injection, for libinjection support,
[  --with-injection             Include libinjection support])

if test "$PHP_INJECTION" != "no"; then
  INJECTION_DIR="./libinjection/src"
  PHP_ADD_INCLUDE($INJECTION_DIR)
  LIBNAME=injection
  LIBSYMBOL=libinjection_is_sqli
  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    LDFLAGS="$LDFLAGS $INJECTION_DIR/libinjection.a"
    AC_DEFINE(HAVE_INJECTIONLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong libinjection version or lib not found])
  ],[
    -L$INJECTION_DIR
  ])

  PHP_NEW_EXTENSION(injection, injection.c, $ext_shared)
fi
