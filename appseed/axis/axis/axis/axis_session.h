#pragma once


namespace base
{


   class CLASS_DECL_AXIS session:
      virtual public ::base::application,
      virtual public ::base::session_interface,
      virtual public ::user::schema
   {
   public:

      

      ::user::interaction *                                    m_puiMouseMoveCapture;
      ::user::interaction *                                    m_puiLastLButtonDown;

      bool                                                     m_bMatterFromHttpCache;

      bool                                                     m_bSystemSynchronizedCursor;
      point                                                    m_ptCursor;
      bool                                                     m_bSystemSynchronizedScreen;
      rect_array                                               m_rectaMonitor;
      rect_array                                               m_rectaWkspace;
      index                                                    m_iMainMonitor;
      index                                                    m_iMainWkspace;



      ::core::platform *                                       m_pcoreplatform;
      string_map < sp(::base::application) >                   m_mapApplication;
      sp(::userpresence::userpresence)                         m_puserpresence;

      bool                                                     m_bDrawCursor;


      ::visual::e_cursor                                       m_ecursor;
      ::visual::e_cursor                                       m_ecursorDefault;
      ::base::copydesk_sp                                      m_spcopydesk;


      application_ptra                                         m_appptra;
      sp(::user::interaction)                                  m_spuiFocus;
      sp(::user::str_context)                                  m_puserstrcontext;
      bool                                                     m_bZipIsDir;
      map < ::user::e_key,::user::e_key,bool,bool > *          m_pmapKeyPressed;
      sp(::base::savings)                                      m_psavings;
      bool                                                     m_bIfs;
      sp(::user::user)                                         m_spuser;




      ::user::schema_simple_impl                               m_schemasimple;




      session(sp(::base::application) papp);
      virtual ~session();

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }

      application_ptra & appptra();

      virtual bool is_session();


      void construct(sp(::base::application) papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();


      ::base::copydesk & copydesk();
      inline sp(class ::user::user)             user()         { return m_spuser; }
      inline ::base::savings &                  savings()      { return *m_psavings; }

      ::user::str_context *                     str_context();



      virtual string get_locale();
      virtual string get_schema();
      virtual string get_locale_schema_dir(const string & strLocale,const string & strSchema);
      virtual string get_locale_schema_dir(const string & strLocale);
      virtual string get_locale_schema_dir();



      virtual void set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void set_schema(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_schema(const string & lpcsz,::action::context actioncontext);


      virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::str::international::locale_schema & localeschema,const char * pszLocale,const char * pszSchema);




      virtual sp(::base::application) start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext);

      
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);

      
      virtual COLORREF get_default_color(uint64_t ui);

      virtual bool is_key_pressed(::user::e_key ekey);

      virtual void set_key_pressed(::user::e_key ekey,bool bPressed);





      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual bool set_main_monitor(index iMonitor);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index get_ui_wkspace(::user::interaction * pui);
      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual bool set_main_wkspace(index iWkspace);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace,LPRECT lprect);

      virtual bool wkspace_to_monitor(LPRECT lprect,index iMonitor,index iWkspace);
      virtual bool monitor_to_wkspace(LPRECT lprect,index iWkspace,index iMonitor);

      virtual bool wkspace_to_monitor(LPRECT lprect);
      virtual bool monitor_to_wkspace(LPRECT lprect);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index initial_frame_position(LPRECT lprect,const RECT & rect, bool bMove);

      virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const RECT & rect);

      virtual index get_zoneing(LPRECT lprect, const RECT & rect,::user::EAppearance eappearance);
      virtual index get_best_zoneing(::user::EAppearance * peappearance, LPRECT lprect,const RECT & rect);
      virtual index get_best_monitor(LPRECT lprect,const RECT & rect);
      virtual index get_best_wkspace(LPRECT lprect,const RECT & rect);
      virtual index get_good_restore(LPRECT lprect,const RECT & rect);
      virtual index get_good_iconify(LPRECT lprect,const RECT & rect);

      virtual index get_good_move(LPRECT lprect,const RECT & rect);

      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      virtual void  get_cursor_pos(LPPOINT lppoint);

      
      virtual sp(::user::interaction) get_active_guie();
      virtual sp(::user::interaction) get_focus_guie();






      virtual string matter_as_string(const char * pszMatter,const char * pszMatter2 = NULL);
      virtual string dir_matter(const char * pszMatter,const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(var varFile);
      virtual string dir_path(const char * psz1,const char * psz2,const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);

      ::file::binary_buffer_sp file_get_file(var varFile,uint32_t uiFlags);



   };


} // namespace base








inline ::base::session & sess(::base::application * papp);




























