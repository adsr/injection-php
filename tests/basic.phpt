--TEST--
basic
--FILE--
<?php
$ss = <<<'EOD'
seems fine
1 = 1 OR 1
foo 'bar' "zap"
foo 'bar'
foo 'bar'
1 = 1 OR 1
1 = '1' OR 1
1 = "1" OR 1
1 /* /* */ */ 2
1 = "1" /* 'blah' */  OR 1
1 = '1' /* "blah" */  OR 1
1# blah blah
foo/* yes this is sqli */
1/* yes this is sqli */
"foo" OR "BAR"
foo" OR "BAR"
"foo" OR "BAR
foo' OR "BAR
foo' OR 'BAR
foo' + 1
'foo' + 1
1" UNION ALL SELECT * FROM FOO
1" INCH
1' INCH
1 /*!anything*/
foo" and 1=1 `
foo" and 1=1 `
1 and @version
1 and @version < 1
1 and "a" < "b"
1 and "a"
1 TOP 'foo'
1 UNION
1 ANALYZE 'foo'
1 /* junk */ UNION
1),(1)) UNION SELECT 1;
foo - (bar) UNION SELECT 1
foo - (1) UNION SELECT 1
1, -sin(1)) UNION SELECT 1
{``.``.id} UNION SELECT table_name from information_schemas LIMIT 1
foo
"foo"
aa<foo>bb
aa<foo>
<foo>bb
<foo>
<foo          >
<foo/>
<foo   />
<foo
<foo
<foo/
<foo   /
<foo  bar>
<foo  bar
<foo  bar
<foo  bar=yes>
<foo  bar=yes  >
<foo  bar=yes
<foo  bar=yes
<foo  bar= 'yes' >
<foo  bar= "yes" >
<foo  bar=>
<foo  bar =  >
<foo  bar = '' >
<foo  bar = 'xxx
<foo  bar = '
<foo  bar = "xxx"
</foo>
</foo  >
<foo bar/>
<?foo
<?foo>
<foo bar="yes"/>
<foo bar="yes">
<1234 foo
<foo /junk>
<foo bar="yes"isdir>
<!DOCTYPE>
<!DOCTYPE "stuff">
<!DOCTYPE "stuff"
<!doctype>
<![CDATA[foobar]]>
<![CDATA[foobar
<![CDATA[foobar
<![CDATA[foobar]]]>
<![CDATA
<![CDATA
<![CDATA foo>
<![CDATAX foo>
<?import foo="bar"/>
<% foo><x foo="%><script>
<!ENTITY foo>
<foo  bar   =   "xxx"
<foo  bar   =   `xxx`
<foo =_=xxx
</ foo="><script>
EOD;

$ss = explode("\n", $ss);

function var_dump_r($x) {
    ob_start();
    var_dump($x);
    return trim(ob_get_clean());
}

foreach ($ss as $s) {
    $is_sqli = injection_is_sqli($s);
    $is_xss = injection_is_xss($s);
    printf(
        "%-16s %-16s %s\n",
        substr(preg_replace('/[^a-z0-9]/i', '_', $s), 0, 16),
        var_dump_r(injection_is_xss($s)),
        var_dump_r(injection_is_sqli($s)),
    );
}
--EXPECT--
seems_fine       bool(false)      bool(false)
1___1_OR_1       bool(false)      string(3) "1&1"
foo__bar___zap_  bool(false)      bool(false)
foo__bar_        bool(false)      bool(false)
foo__bar_        bool(false)      bool(false)
1___1_OR_1       bool(false)      string(3) "1&1"
1____1__OR_1     bool(false)      string(5) "1os&1"
1____1__OR_1     bool(false)      string(5) "1os&1"
1_____________2  bool(false)      string(1) "X"
1____1______blah bool(false)      string(5) "1os&1"
1____1______blah bool(false)      string(5) "1os&1"
1__blah_blah     bool(false)      bool(false)
foo___yes_this_i bool(false)      string(2) "nc"
1___yes_this_is_ bool(false)      string(2) "1c"
_foo__OR__BAR_   bool(false)      bool(false)
foo__OR__BAR_    bool(false)      bool(false)
_foo__OR__BAR    bool(false)      bool(false)
foo__OR__BAR     bool(false)      bool(false)
foo__OR__BAR     bool(false)      string(3) "s&s"
foo____1         bool(false)      bool(false)
_foo____1        bool(false)      bool(false)
1__UNION_ALL_SEL bool(false)      string(5) "sUEok"
1__INCH          bool(false)      bool(false)
1__INCH          bool(false)      bool(false)
1____anything__  bool(false)      string(1) "X"
foo__and_1_1__   bool(false)      string(4) "s&1c"
foo__and_1_1__   bool(false)      string(4) "s&1c"
1_and__version   bool(false)      bool(false)
1_and__version__ bool(false)      string(3) "1&v"
1_and__a_____b_  bool(false)      string(5) "1&sos"
1_and__a_        bool(false)      bool(false)
1_TOP__foo_      bool(false)      bool(false)
1_UNION          bool(false)      bool(false)
1_ANALYZE__foo_  bool(false)      bool(false)
1____junk____UNI bool(false)      string(2) "1U"
1___1___UNION_SE bool(false)      string(5) "1)UE1"
foo____bar__UNIO bool(false)      string(4) "nUE1"
foo____1__UNION_ bool(false)      string(4) "nUE1"
1___sin_1___UNIO bool(false)      string(5) "1,f(1"
_______id__UNION bool(false)      string(1) "X"
foo              bool(false)      bool(false)
_foo_            bool(false)      bool(false)
aa_foo_bb        bool(false)      bool(false)
aa_foo_          bool(false)      bool(false)
_foo_bb          bool(false)      bool(false)
_foo_            bool(false)      bool(false)
_foo___________  bool(false)      bool(false)
_foo__           bool(false)      bool(false)
_foo_____        bool(false)      bool(false)
_foo             bool(false)      bool(false)
_foo             bool(false)      bool(false)
_foo_            bool(false)      bool(false)
_foo____         bool(false)      bool(false)
_foo__bar_       bool(false)      bool(false)
_foo__bar        bool(false)      bool(false)
_foo__bar        bool(false)      bool(false)
_foo__bar_yes_   bool(false)      bool(false)
_foo__bar_yes___ bool(false)      bool(false)
_foo__bar_yes    bool(false)      bool(false)
_foo__bar_yes    bool(false)      bool(false)
_foo__bar___yes_ bool(false)      bool(false)
_foo__bar___yes_ bool(false)      bool(false)
_foo__bar__      bool(false)      bool(false)
_foo__bar_____   bool(false)      bool(false)
_foo__bar_______ bool(false)      bool(false)
_foo__bar____xxx bool(false)      bool(false)
_foo__bar____    bool(false)      bool(false)
_foo__bar____xxx bool(false)      bool(false)
__foo_           bool(false)      bool(false)
__foo___         bool(false)      bool(false)
_foo_bar__       bool(false)      bool(false)
__foo            bool(false)      bool(false)
__foo_           bool(false)      bool(false)
_foo_bar__yes___ bool(false)      bool(false)
_foo_bar__yes__  bool(false)      bool(false)
_1234_foo        bool(false)      bool(false)
_foo__junk_      bool(false)      bool(false)
_foo_bar__yes_is bool(false)      bool(false)
__DOCTYPE_       bool(true)       bool(false)
__DOCTYPE__stuff bool(true)       bool(false)
__DOCTYPE__stuff bool(true)       bool(false)
__doctype_       bool(true)       bool(false)
___CDATA_foobar_ bool(false)      bool(false)
___CDATA_foobar  bool(false)      bool(false)
___CDATA_foobar  bool(false)      bool(false)
___CDATA_foobar_ bool(false)      bool(false)
___CDATA         bool(false)      bool(false)
___CDATA         bool(false)      bool(false)
___CDATA_foo_    bool(false)      bool(false)
___CDATAX_foo_   bool(false)      bool(false)
__import_foo__ba bool(true)       bool(false)
___foo__x_foo___ bool(true)       bool(false)
__ENTITY_foo_    bool(true)       bool(false)
_foo__bar_______ bool(false)      bool(false)
_foo__bar_______ bool(false)      bool(false)
_foo____xxx      bool(false)      bool(false)
___foo____script bool(true)       bool(false)
