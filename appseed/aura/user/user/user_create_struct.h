#pragma once


namespace user
{


   class CLASS_DECL_AURA create_struct :
#ifdef WINDOWSEX
      public CREATESTRUCTW
#else
      public CREATESTRUCTA
#endif
   {
      public:


         create_struct & operator = (const RECT & rect)
         {

            x = rect.left;
            y = rect.top;
            cx = rect.right - rect.left;
            cy = rect.bottom - rect.top;

            return *this;

         }


         create_struct & operator = (LPCRECT lpcrect)
         {

            if (lpcrect == NULL)
            {

               x = 0;
               y = 0;
               cx = 0;
               cy = 0;

            }
            else
            {

               operator = (*lpcrect);

            }

            return *this;

         }


   };


} // namespace user


