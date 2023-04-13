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

#ifndef PHP_PDO_PGSQLSW_INT_H
#define PHP_PDO_PGSQLSW_INT_H

#include <libpq-fe.h>
#include <libpq/libpq-fs.h>
#include <php.h>

#define PHP_PDO_PGSQLSW_CONNECTION_FAILURE_SQLSTATE "08006"

typedef struct {
    const char *file;
    int line;
    unsigned int errcode;
    char *errmsg;
} pdo_pgsqlsw_error_info;

/* stuff we use in a pgsql database handle */
typedef struct {
    PGconn		*server;
    unsigned 	attached:1;
    unsigned 	_reserved:31;
    pdo_pgsqlsw_error_info	einfo;
    Oid 		pgoid;
    unsigned int	stmt_counter;
    /* The following two variables have the same purpose. Unfortunately we need
       to keep track of two different attributes having the same effect. */
    zend_bool		emulate_prepares;
    zend_bool		disable_native_prepares; /* deprecated since 5.6 */
    zend_bool		disable_prepares;
} pdo_pgsqlsw_db_handle;

typedef struct {
    char         *def;
    zend_long    intval;
    Oid          pgsql_type;
    zend_bool    boolval;
} pdo_pgsqlsw_column;

typedef struct {
    pdo_pgsqlsw_db_handle     *H;
    PGresult                *result;
    pdo_pgsqlsw_column        *cols;
    char *cursor_name;
    char *stmt_name;
    char *query;
    char **param_values;
    int *param_lengths;
    int *param_formats;
    Oid *param_types;
    int                     current_row;
    zend_bool is_prepared;
} pdo_pgsqlsw_stmt;

typedef struct {
    Oid     oid;
} pdo_pgsqlsw_bound_param;


#if PHP_VERSION_ID < 70300
extern pdo_driver_t pdo_pgsqlsw_driver;
extern struct pdo_stmt_methods pgsqlsw_stmt_methods;
extern php_stream_ops pdo_pgsqlsw_lob_stream_ops;
#else
extern const pdo_driver_t pdo_pgsqlsw_driver;
extern const struct pdo_stmt_methods pgsqlsw_stmt_methods;
extern const php_stream_ops pdo_pgsqlsw_lob_stream_ops;
#endif


extern int _pdo_pgsqlsw_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, int errcode, const char *sqlstate, const char *msg, const char *file, int line);
#define pdo_pgsqlsw_error(d,e,z)	_pdo_pgsqlsw_error(d, NULL, e, z, NULL, __FILE__, __LINE__)
#define pdo_pgsqlsw_error_msg(d,e,m)	_pdo_pgsqlsw_error(d, NULL, e, NULL, m, __FILE__, __LINE__)
#define pdo_pgsqlsw_error_stmt(s,e,z)	_pdo_pgsqlsw_error(s->dbh, s, e, z, NULL, __FILE__, __LINE__)
#define pdo_pgsqlsw_error_stmt_msg(s,e,m)	_pdo_pgsqlsw_error(s->dbh, s, e, NULL, m, __FILE__, __LINE__)

#define pdo_pgsqlsw_sqlstate(r) PQresultErrorField(r, PG_DIAG_SQLSTATE)

enum {
    PDO_PGSQLSW_ATTR_DISABLE_PREPARES = PDO_ATTR_DRIVER_SPECIFIC,
};

struct pdo_pgsqlsw_lob_self {
    zval dbh;
    PGconn *conn;
    int lfd;
    Oid oid;
};

enum pdo_pgsqlsw_specific_constants {
    PGSQLSW_TRANSACTION_IDLE = PQTRANS_IDLE,
    PGSQLSW_TRANSACTION_ACTIVE = PQTRANS_ACTIVE,
    PGSQLSW_TRANSACTION_INTRANS = PQTRANS_INTRANS,
    PGSQLSW_TRANSACTION_INERROR = PQTRANS_INERROR,
    PGSQLSW_TRANSACTION_UNKNOWN = PQTRANS_UNKNOWN
};

php_stream *pdo_pgsqlsw_create_lob_stream(zval *pdh, int lfd, Oid oid);
extern const php_stream_ops pdo_pgsqlsw_lob_stream_ops;

#endif /* PHP_PDO_PGSQLSW_INT_H */