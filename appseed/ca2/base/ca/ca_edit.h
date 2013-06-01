#pragma once


namespace ca
{


   class CLASS_DECL_ca2 base_edit :
      public ::ca::data_container
   {
   public:


      base_edit(sp(::ca::application) papp);
      virtual ~base_edit();


      template < class DATA >
      inline DATA * validate_data(::ca::data * pdata)
      {
         
         if(pdata == m_spdata)
         {
            return dynamic_cast < DATA * > (pdata);
         }
         
         return NULL;

      }


      virtual void apply();
      virtual void on_apply();


   };


   template < class EDIT >
   EDIT * data::validate_edit(::ca::base_edit * pedit)
   {
         
      if(pedit->m_spdata == this)
      {
         return dynamic_cast < EDIT * > (pedit);
      }
         
      return NULL;

   }


   template < class DATA >
   class edit :
      public base_edit 
   {
   public:      

      
      edit(sp(::ca::application) papp);
      virtual ~edit();


      DATA * validate_data(::ca::data * pdata)
      {

         return base_edit::validate_data < DATA > (pdata);  

      }

   };


   template < class DATA >
   edit < DATA >::edit(sp(::ca::application) papp) :
      ca(papp),
      base_edit(papp)
   {
   }
   
   template < class DATA >
   edit < DATA >::~edit()
   {
   }


} // namespace ca



