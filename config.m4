PHP_ARG_WITH([pdo-pgsqlsw],
  [for PostgreSQL support for PDO and Swoole],
  [AS_HELP_STRING([[--with-pdo-pgsqlsw[=DIR]]],
    [PDO: PostgreSQL support. DIR is the PostgreSQL base install directory or
    the path to pg_config])])

if test "$PHP_PDO_PGSQLSW" != "no"; then

  if test "$PHP_PDO" = "no" && test "$ext_shared" = "no"; then
    AC_MSG_ERROR([PDO is not enabled! Add --enable-pdo to your configure line.])
  fi

  PHP_EXPAND_PATH($PGSQL_INCLUDE, PGSQL_INCLUDE)

  AC_MSG_CHECKING(for pg_config)
  for i in $PHP_PDO_PGSQLSW $PHP_PDO_PGSQLSW/bin /usr/local/pgsql/bin /usr/local/bin /usr/bin ""; do
    if test -x $i/pg_config; then
      PG_CONFIG="$i/pg_config"
      break;
    fi
  done

  if test -n "$PG_CONFIG"; then
    AC_MSG_RESULT([$PG_CONFIG])
    PGSQL_INCLUDE=`$PG_CONFIG --includedir`
    PGSQL_LIBDIR=`$PG_CONFIG --libdir`
  else
    AC_MSG_RESULT(not found)
    if test "$PHP_PDO_PGSQLSW" = "yes"; then
      PGSQL_SEARCH_PATHS="/usr /usr/local /usr/local/pgsql"
    else
      PGSQL_SEARCH_PATHS=$PHP_PDO_PGSQLSW
    fi

    for i in $PGSQL_SEARCH_PATHS; do
      for j in include include/pgsql include/postgres include/postgresql ""; do
        if test -r "$i/$j/libpq-fe.h"; then
          PGSQL_INC_BASE=$i
          PGSQL_INCLUDE=$i/$j
        fi
      done

      for j in $PHP_LIBDIR $PHP_LIBDIR/pgsql $PHP_LIBDIR/postgres $PHP_LIBDIR/postgresql ""; do
        if test -f "$i/$j/libpq.so" || test -f "$i/$j/libpq.a"; then
          PGSQL_LIBDIR=$i/$j
        fi
      done
    done
  fi

  if test -z "$PGSQL_INCLUDE"; then
    AC_MSG_ERROR(Cannot find libpq-fe.h. Please specify correct PostgreSQL installation path)
  fi

  if test -z "$PGSQL_LIBDIR"; then
    AC_MSG_ERROR(Cannot find libpq.so. Please specify correct PostgreSQL installation path)
  fi

  if test -z "$PGSQL_INCLUDE" -a -z "$PGSQL_LIBDIR" ; then
    AC_MSG_ERROR([Unable to find libpq anywhere under $PGSQL_SEARCH_PATHS])
  fi

  AC_DEFINE(HAVE_PDO_PGSQLSW,1,[Whether to build PostgreSQL for PDO support or not])

  old_LIBS=$LIBS
  old_LDFLAGS=$LDFLAGS
  LDFLAGS="-L$PGSQL_LIBDIR $LDFLAGS"

  AC_CHECK_LIB(pq, PQlibVersion,, AC_MSG_ERROR([Unable to build the PDO PostgreSQL driver: at least libpq 9.1 is required]))

  LIBS=$old_LIBS
  LDFLAGS=$old_LDFLAGS

  PHP_ADD_LIBRARY_WITH_PATH(pq, $PGSQL_LIBDIR, PDO_PGSQLSW_SHARED_LIBADD)
  PHP_SUBST(PDO_PGSQLSW_SHARED_LIBADD)

  PHP_ADD_INCLUDE($PGSQL_INCLUDE)

  PHP_ADD_LIBRARY(stdc++, 1, PDO_PGSQLSW_SHARED_LIBADD)
  CFLAGS="-Wall -pthread $CFLAGS"
  LDFLAGS="$LDFLAGS -lpthread"
  PHP_ADD_LIBRARY(pthread, 1, PDO_PGSQLSW_SHARED_LIBADD)

  PHP_CHECK_PDO_INCLUDES

  PHP_ADD_INCLUDE([$phpincludedir/ext/swoole])
  PHP_ADD_INCLUDE([$phpincludedir/ext/swoole/include])
  PHP_ADD_EXTENSION_DEP(pdo_pgsqlsw, swoole)

  PHP_NEW_EXTENSION(pdo_pgsqlsw, pdo_pgsqlsw.cc pgsqlsw_driver.cc pgsqlsw_statement.cc, $ext_shared,, -I$pdo_cv_inc_path, cxx)
  PHP_ADD_EXTENSION_DEP(pdo_pgsqlsw, pdo)

  PHP_REQUIRE_CXX()
  CXXFLAGS="$CXXFLAGS -Wall -Wno-unused-function -Wno-deprecated -Wno-deprecated-declarations -std=c++11"
fi
