#include "framework.h"


CLASS_DECL_ca vsstring i64toa_dup(int64_t i, int32_t iBase)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);

   return sz;

}


CLASS_DECL_ca vsstring i64toa_dup(int64_t i)
{

   return i64toa_dup(i, 10);

}



CLASS_DECL_ca vsstring ui64toa_dup(int64_t i, int32_t iBase)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);

   return sz;

}


CLASS_DECL_ca vsstring ui64toa_dup(int64_t i)
{

   return ui64toa_dup(i, 10);

}



