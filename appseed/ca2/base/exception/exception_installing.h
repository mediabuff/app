#pragma once


#include "exception_installing.h"


class CLASS_DECL_ca2 installing_exception : 
   virtual public temporary_exception
{
public:


   installing_exception(sp(::ca::application) papp, const char * pszTip = NULL);
   installing_exception(const installing_exception & e);
   virtual ~installing_exception();


};
