#pragma once


namespace axis
{


   class CLASS_DECL_AXIS application :
      virtual public ::aura::application,
      virtual public ::database::client
   {
   public:


      bool                                            m_bAxisProcessInitialize;
      bool                                            m_bAxisProcessInitializeResult;

      bool                                            m_bAxisInitializeInstance;
      bool                                            m_bAxisInitializeInstanceResult;

      bool                                            m_bAxisInitialize1;
      bool                                            m_bAxisInitialize1Result;

      bool                                            m_bAxisInitialize;
      bool                                            m_bAxisInitializeResult;

      string                                          m_strLicense;


      ::http::application                             m_http;

      ::simpledb::simpledb                            m_simpledb;

      string                                          m_strDataIdAddUp;


      bool                                            m_bUpdateMatterOnInstall;


      int32_t                                         m_iWaitCursorCount;         // for wait cursor (>0 => waiting)






      static UINT                                     APPM_LANGUAGE;
      static WPARAM                                   WPARAM_LANGUAGE_UPDATE;

      ::user::interaction *                           m_pwndMain;




      application();
      virtual ~application();


      virtual string get_cred(const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive);
      virtual string get_cred(string & strUsername, string & strPassword, string strToken);
      virtual void set_cred(string strToken, const char * pszUsername, const char * pszPassword);
      virtual void set_cred_ok(string strToken, bool bOk);



      virtual string load_string(id id);
      virtual bool load_string(string & str, id id);
      virtual void load_string_table();
      virtual      bool load_cached_string(string & str, id id, bool bLoadStringTable);
      virtual   bool load_cached_string_by_id(string & str, id id, bool bLoadStringTable);
      virtual   void load_string_table(const string & pszApp, const string & pszId);



      virtual bool is_system();
      virtual bool is_session();
      virtual bool is_serviceable();



      inline class ::http::application &        http() { return m_http; }

      inline class ::simpledb::simpledb         & simpledb() { return m_simpledb; }









      virtual bool verb();




      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();



      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();

      virtual bool initialize_application();
      virtual int32_t exit_application() override;

      virtual bool initialize();
      virtual bool finalize();



      virtual int32_t run();

      virtual bool pre_run();
      virtual int32_t main();
      virtual int32_t on_run();
      virtual int32_t application_pre_run();
      virtual bool initial_check_directrix();
      virtual bool os_native_bergedge_start();

      virtual bool InitApplication();

      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool system_add_app_install(const char * pszId);



      virtual bool update_appmatter(::sockets::socket_handler & handler, sp(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative);
      virtual bool update_appmatter(::sockets::socket_handler & handler, sp(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const string & strLocale, const string & strStyle);


      virtual void SetCurrentHandles();



      virtual bool get_temp_file_name_template(string & str, const char * pszName, const char * pszExtension, const char * pszTemplate);

      virtual bool get_temp_file_name(string & str, const char * pszName, const char * pszExtension);





      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool final_handle_exception(::exception::exception & e);




      virtual sp(::aura::application) assert_running(const char * pszAppId);

      virtual bool is_running();



      virtual void on_request(sp(::create) pcreatecontext);



      virtual bool assert_user_logged_in();

      virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);

      virtual bool file_is_read_only(const char * pszPath);



      inline ::database::server &               dataserver() { return *m_simpledb.get_data_server(); }



      virtual void on_create_keyboard();




      virtual int32_t simple_message_box(::user::primitive * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box_timeout(::user::primitive * pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle);
      int32_t simple_message_box(const char * pszMessage, UINT fuStyle);
      virtual string message_box(const string & pszMatter, property_set & propertyset);



      virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);


      virtual void process_message_filter(int32_t code, signal_details * pobj);



      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end

      virtual void _001CloseApplication();


      virtual string get_license_id();




      virtual void construct(const char * pszAppId);


      virtual bool process_initialize();





      virtual void TermThread(HINSTANCE hInstTerm);


      virtual void set_env_var(const string & var, const string & value);


      virtual sp(::aura::printer) get_printer(const char * pszDeviceName);


      virtual ::visual::icon * set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon);

      virtual ::visual::icon * get_icon(object * pobject, bool bBigIcon) const;

      virtual void on_service_request(sp(::create) pcreatecontext);

      virtual string get_mutex_name_gen();

      virtual void draw2d_factory_exchange();

      virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg);
      virtual ::user::primitive * window_from_os_data(void * pdata);


      virtual bool set_keyboard_layout(const char * pszPath, ::action::context actioncontext);
      virtual int32_t hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = NULL) override;


      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void on_update_view(::user::impact * pview, ::user::impact * pviewSender, LPARAM lHint, object* pHint);

      virtual bool keyboard_focus_is_focusable(::user::elemental * pue);
      virtual bool keyboard_focus_OnSetFocus(::user::elemental * pue);


      virtual bool on_open_document(::user::document * pdocument, var varFile);
      virtual bool on_save_document(::user::document * pdocument, var varFile);


      virtual int32_t hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = NULL);


      virtual bool check_install() override;

      inline ::html::html * html() { return m_pauraapp->m_paurasystem->m_phtml; }

      virtual ::html::html * create_html();

   };


} // namespace axis










