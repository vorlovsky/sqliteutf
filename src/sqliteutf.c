#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "utfconv.c"

#if !defined(SQLITE_ASCII) && !defined(SQLITE_EBCDIC)
#define SQLITE_ASCII 1
#endif

static void sqlite3LowerUtfFunc(
    sqlite3_context *context,
    int argc,
    sqlite3_value **argv)
{
  char *z1;
  const char *z2;
  int i, n;
  (void)argc;
  z2 = (char *)sqlite3_value_text(argv[0]);
  if (*z2 == 0)
  {
    sqlite3_result_text(context, z2, -1, NULL);
    return;
  }
  z1 = Utf8StrMakeLwrUtf8Str(z2);
  n = StrLenUtf8(z1);
  // n = sqlite3_value_bytes(z1);
  sqlite3_result_text(context, z1, n, free);
}

static void sqlite3UpperUtfFunc(
    sqlite3_context *context,
    int argc,
    sqlite3_value **argv)
{
  char *z1;
  const char *z2;
  int i, n;
  (void)argc;
  z2 = (char *)sqlite3_value_text(argv[0]);
  if (*z2 == 0)
  {
    sqlite3_result_text(context, z2, -1, NULL);
    return;
  }
  z1 = Utf8StrMakeUprUtf8Str(z2);
  n = StrLenUtf8(z1);
  sqlite3_result_text(context, z1, n, free);
}

#ifdef _WIN32
__declspec(dllexport)
#endif
int
sqlite3_sqliteutf_init(
    sqlite3 *db,
    char **pzErrMsg,
    const sqlite3_api_routines *pApi)
{
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg; /* Unused parameter */
  rc = sqlite3_create_function(db, "lower_utf", 1,
                               SQLITE_UTF8 | SQLITE_INNOCUOUS | SQLITE_DETERMINISTIC,
                               NULL, &sqlite3LowerUtfFunc, NULL, NULL);
  if (rc == SQLITE_OK)
  {
    rc = sqlite3_create_function(db, "upper_utf", 1,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS | SQLITE_DETERMINISTIC,
                                 NULL, &sqlite3UpperUtfFunc, NULL, NULL);
  }
  return rc;
}
