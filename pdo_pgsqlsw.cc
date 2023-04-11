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
# include "config.h"
#endif

#include <thread>
#include <signal.h>

extern "C" {
    #include "php.h"
    #include "php_ini.h"
    #include "ext/standard/info.h"
    #include "pdo/php_pdo.h"
    #include "pdo/php_pdo_driver.h"
    #include "php_pdo_pgsqlsw.h"
    #include "php_pdo_pgsqlsw_int.h"
}

#ifdef HAVE_PG_CONFIG_H
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include <pg_config.h>
#endif

#include "swoole_coroutine.h"


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pdo_pgsqlsw)
{
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_ATTR_DISABLE_PREPARES", PDO_PGSQLSW_ATTR_DISABLE_PREPARES);
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_TRANSACTION_IDLE", (zend_long)PGSQLSW_TRANSACTION_IDLE);
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_TRANSACTION_ACTIVE", (zend_long)PGSQLSW_TRANSACTION_ACTIVE);
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_TRANSACTION_INTRANS", (zend_long)PGSQLSW_TRANSACTION_INTRANS);
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_TRANSACTION_INERROR", (zend_long)PGSQLSW_TRANSACTION_INERROR);
    REGISTER_PDO_CLASS_CONST_LONG("PGSQLSW_TRANSACTION_UNKNOWN", (zend_long)PGSQLSW_TRANSACTION_UNKNOWN);

    php_pdo_register_driver(&pdo_pgsqlsw_driver);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pdo_pgsqlsw)
{
    php_pdo_unregister_driver(&pdo_pgsqlsw_driver);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdo_pgsqlsw)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "PDO Driver for PostgreSQL and Swoole", "enabled");
#ifdef HAVE_PG_CONFIG_H
    php_info_print_table_row(2, "PostgreSQL(libpq) Version", PG_VERSION);
#endif
    php_info_print_table_end();
}
/* }}} */

/* {{{ pdo_pgsqlsw_functions[]
 */
static const zend_function_entry pdo_pgsqlsw_functions[] = {
	PHP_FE_END
};
/* }}} */

/* {{{ pdo_pgsqlsw_deps
 */
static zend_module_dep pdo_pgsqlsw_deps[] = {
    ZEND_MOD_REQUIRED("pdo")
        ZEND_MOD_END
};
/* }}} */


/* {{{ pdo_pgsqlsw_module_entry */
zend_module_entry pdo_pgsqlsw_module_entry = {
    STANDARD_MODULE_HEADER_EX,
    NULL,
    pdo_pgsqlsw_deps,
    "pdo_pgsqlsw",
    pdo_pgsqlsw_functions,
    PHP_MINIT(pdo_pgsqlsw),
    PHP_MSHUTDOWN(pdo_pgsqlsw),
    NULL,
    NULL,
    PHP_MINFO(pdo_pgsqlsw),
    PHP_PDO_TAOSW_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */


#ifdef COMPILE_DL_PDO_TAOSW
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(pdo_pgsqlsw)
#endif
