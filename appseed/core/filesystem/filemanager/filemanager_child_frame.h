#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE child_frame :
      public simple_child_frame
   {
   public:



      child_frame(::aura::application * papp);
      virtual ~child_frame();

      void install_message_routing(::message::sender * pinterface) override;

      void OnChangeEditSearch();

      sp(manager) get_filemanager_template();


      void GetSelected(::fs::item_array &itema);

      bool on_create_bars() override;
      bool DestroyBars();
      virtual void _001OnCmdMsg(::user::command * pcommand) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);
      DECL_GEN_SIGNAL(_001OnShowWindow);


   };


} // namespace filemanager




