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

#ifndef PHP_PDO_TAOSW_H
# define PHP_PDO_TAOSW_H

extern zend_module_entry pdo_taosw_module_entry;
# define phpext_pdo_pgsqlsw_ptr &pdo_pgsqlsw_module_entry

# define PHP_PDO_TAOSW_VERSION "0.0.1"

# if defined(ZTS) && defined(COMPILE_DL_PDO_TAOSW)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

PHP_MINIT_FUNCTION(pdo_pgsqlsw);
PHP_MSHUTDOWN_FUNCTION(pdo_pgsqlsw);
PHP_RINIT_FUNCTION(pdo_pgsqlsw);
PHP_RSHUTDOWN_FUNCTION(pdo_pgsqlsw);
PHP_MINFO_FUNCTION(pdo_pgsqlsw);

#endif	/* PHP_PDO_PGSQLSW_H */
