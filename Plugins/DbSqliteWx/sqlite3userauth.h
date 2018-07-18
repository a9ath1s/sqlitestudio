/*
** 2014-09-08
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file contains the application interface definitions for the
** user-authentication extension feature.
**
** To compile with the user-authentication feature, append this file to
** end of an SQLite amalgamation header file ("wxsqlite3.h"), then add
** the SQLITE_USER_AUTHENTICATION compile-time option.  See the
** user-auth.txt file in the same source directory as this file for
** additional information.
*/
#ifdef SQLITE_USER_AUTHENTICATION

#ifdef __cplusplus
extern "C" {
#endif

/*
** If a database contains the SQLITE_USER table, then the
** wx_sqlite3_user_authenticate() interface must be invoked with an
** appropriate username and password prior to enable read and write
** access to the database.
**
** Return SQLITE_OK on success or SQLITE_ERROR if the username/password
** combination is incorrect or unknown.
**
** If the SQLITE_USER table is not present in the database file, then
** this interface is a harmless no-op returnning SQLITE_OK.
*/
int wx_sqlite3_user_authenticate(
  wx_sqlite3 *db,           /* The database connection */
  const char *zUsername, /* Username */
  const char *aPW,       /* Password or credentials */
  int nPW                /* Number of bytes in aPW[] */
);

/*
** The wx_sqlite3_user_add() interface can be used (by an admin user only)
** to create a new user.  When called on a no-authentication-required
** database, this routine converts the database into an authentication-
** required database, automatically makes the added user an
** administrator, and logs in the current connection as that user.
** The wx_sqlite3_user_add() interface only works for the "main" database, not
** for any ATTACH-ed databases.  Any call to wx_sqlite3_user_add() by a
** non-admin user results in an error.
*/
int wx_sqlite3_user_add(
  wx_sqlite3 *db,           /* Database connection */
  const char *zUsername, /* Username to be added */
  const char *aPW,       /* Password or credentials */
  int nPW,               /* Number of bytes in aPW[] */
  int isAdmin            /* True to give new user admin privilege */
);

/*
** The wx_sqlite3_user_change() interface can be used to change a users
** login credentials or admin privilege.  Any user can change their own
** login credentials.  Only an admin user can change another users login
** credentials or admin privilege setting.  No user may change their own 
** admin privilege setting.
*/
int wx_sqlite3_user_change(
  wx_sqlite3 *db,           /* Database connection */
  const char *zUsername, /* Username to change */
  const char *aPW,       /* New password or credentials */
  int nPW,               /* Number of bytes in aPW[] */
  int isAdmin            /* Modified admin privilege for the user */
);

/*
** The wx_sqlite3_user_delete() interface can be used (by an admin user only)
** to delete a user.  The currently logged-in user cannot be deleted,
** which guarantees that there is always an admin user and hence that
** the database cannot be converted into a no-authentication-required
** database.
*/
int wx_sqlite3_user_delete(
  wx_sqlite3 *db,           /* Database connection */
  const char *zUsername  /* Username to remove */
);

#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

#endif /* SQLITE_USER_AUTHENTICATION */

