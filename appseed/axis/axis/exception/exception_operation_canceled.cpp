#include "framework.h"


operation_canceled_exception::operation_canceled_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   ::simple_exception(papp)
{
      printf(":operation_canceled");
}


operation_canceled_exception::operation_canceled_exception(sp(::axis::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   ::simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":operation_canceled(NULL)");
      }
      else
      {
         printf(":operation_canceled(\"%s\")",pszMessage);
      }

}

operation_canceled_exception::~operation_canceled_exception()
{

}
