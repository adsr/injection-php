# injection-php

This is a hand-written libinjection wrapper for PHP 7 (and 5). (libinjection
includes a SWIG-generated PHP extension, but SWIG does not currently support PHP
7.) See https://github.com/client9/libinjection for the underlying library.

### Building

    $ # Clone repo and submodule
    $ git clone https://github.com/adsr/injection-php.git
    $ cd injection-php
    $ git submodule update --init --recursive
    $
    $ # Install php-dev
    $ sudo apt-get install php-dev # ...or equivalent for your system
    $
    $ # Build library and extension
    $ make -C libinjection && phpize && ./configure && make
    $
    $ # Run demo
    $ php -dextension=`pwd`/modules/injection.so example.php
