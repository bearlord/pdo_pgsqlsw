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
    #include "pdo/php_pdo.h"
    #include "pdo/php_pdo_driver.h"
    #include "php_pdo_pgsqlsw.h"
    #include "php_pdo_pgsqlsw_int.h"
}
#include "swoole_coroutine.h"

#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if PHP_VERSION_ID >= 80100
#include "80100/pgsqlsw_statement.cc"
#elif PHP_VERSION_ID >= 80000
#include "80000/pgsqlsw_statement.cc"
#elif PHP_VERSION_ID >= 70400
#include "70400/pgsqlsw_statement.cc"
#elif PHP_VERSION_ID >= 70300
#include "70300/pgsqlsw_statement.cc"
#elif PHP_VERSION_ID >= 70000
#include "70000/pgsqlsw_statement.cc"
#endif