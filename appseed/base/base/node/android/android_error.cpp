#include "framework.h"

string get_error_message(DWORD dwError)
{
   LPSTR lpBuffer;
   FormatMessage(
      FORMAT_MESSAGE_ALLOcaTE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      0,
      (LPSTR) &lpBuffer,
      1,
      NULL);
      string str = lpBuffer;
//   string str = ::ca2::international::unicode_to_utf8(lpBuffer);
// xxx   LocalFree(lpBuffer);
   return str;
}
