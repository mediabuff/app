#pragma once



namespace prompt
{


   class CLASS_DECL_SPHERE application :
      virtual public ::filehandler::application
   {
   public:


      sp(::user::single_document_template)    m_ptemplateCommandMain;


      application();
      virtual ~application();


      void construct();


      bool initialize_application() override;
      virtual int32_t exit_application() override;


	   virtual void _001OnCmdMsg(::user::command * pcommand) override;


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace prompt
