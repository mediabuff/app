#include "framework.h"


namespace c
{
   
   c::c()
   {

      m_countReference  = 1;
      m_bHeap           = false;

   }

   c::~c()
   {
   }


   int64_t c::add_ref()
   {
         #ifdef WINDOWS
      return InterlockedIncrement64(&m_countReference);
      #else
      return __sync_add_and_fetch(&m_countReference, 1);
      #endif
   }

   int64_t c::dec_ref()
   {
      #ifdef WINDOWS
      int64_t i = InterlockedDecrement64(&m_countReference);
      #else
      int64_t i =  __sync_sub_and_fetch(&m_countReference, 1);
      #endif
      return i;
   }

   int64_t c::release()
   {
      int64_t i = dec_ref();
      if(i == 0)
      {
         delete_this();
      }
      return i;
   }



  void c::delete_this()
  {

     // quite verisimple default implementation
     delete this;

  }


  
} // namespace c



