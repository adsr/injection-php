# injection-php

This is a hand-written libinjection wrapper for PHP 7+ (and 5). libinjection
includes a SWIG-generated PHP extension. This one is simpler. It wraps two
simple functions in the API, `libinjection_is_sqli` and `libinjection_xss`.

See https://github.com/libinjection/libinjection for the underlying library.

### Building

    $ # Clone repo and submodule
    $ git clone --recursive https://github.com/adsr/injection-php.git
    $ cd injection-php
    $
    $ # Install php-dev
    $ sudo apt-get install php-dev # ...or equivalent for your system
    $
    $ # Build library
    $ pushd libinjection
    $ ./autogen.sh && ./configure && make
    $ popd
    $
    $ # Build PHP extension
    $ phpize && ./configure && make
    $
    $ # Run tests
    $ NO_INTERACTION=1 make test
