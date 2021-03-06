#include "framework.h"


namespace console
{


   prompt_document::prompt_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
      ::user::document(papp)
   {

   }


   bool prompt_document::on_new_document()
   {

      if(!::user::document::on_new_document())
		   return FALSE;

      update_all_views(NULL, 0);

	   return TRUE;

   }


   prompt_document::~prompt_document()
   {

   }


 

   void prompt_document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void prompt_document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // prompt_document serialization

   /*
   void prompt_document::Serialize(CArchive& ar)
   {
	   if (ar.IsStoring())
	   {
		   // TODO: add storing code here
	   }
	   else
	   {
		   // TODO: add loading code here
	   }
   }
   */

   void prompt_document::data_on_after_change(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool prompt_document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
   //  m_prompt_document.load(str);
      
      update_all_views(NULL, 123);

      return TRUE;

   }


} // namespace prompt



