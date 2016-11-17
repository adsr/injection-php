<?php

$sqli_yes = "select * from x where y='";
$sqli_no = "select 1";
$xss_yes = "<script>";
$xss_no = "foo";

var_dump(injection_is_sqli($sqli_yes));
var_dump(injection_is_sqli($sqli_no));
var_dump(injection_is_xss($xss_yes));
var_dump(injection_is_xss($xss_no));
