/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Edin Kadribasic <edink@emini.dk>
  | Modified: Bearlord <565364226@qq.com>
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
    #include "php.h"
    #include "php_ini.h"
    #include "ext/standard/info.h"
    #include "ext/standard/php_string.h"
    #include "main/php_network.h"
    #include "pdo/php_pdo.h"
    #include "pdo/php_pdo_driver.h"
    #include "pdo/php_pdo_error.h"
    #include "ext/standard/file.h"
    #include "php_pdo_pgsqlsw.h"
    #include "php_pdo_pgsqlsw_int.h"
    #include "zend_exceptions.h"
}
#include "swoole_coroutine.h"

#if PHP_VERSION_ID >= 80100
#include "80100/pgsqlsw_driver.cc"
#elif PHP_VERSION_ID >= 80000
#include "80000/pgsqlsw_driver.cc"
#elif PHP_VERSION_ID >= 70300
#include "70300/pgsqlsw_driver.cc"
#elif PHP_VERSION_ID >= 70000
#include "70000/pgsqlsw_driver.cc"
#endif
