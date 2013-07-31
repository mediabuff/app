#include "framework.h"


namespace user
{


   frame_window_interface::frame_window_interface()
   {

      m_pdocumenttemplate = NULL;
      m_bAutoWindowFrame      = true;
      m_bWindowFrame          = true;


   }


   frame_window_interface::~frame_window_interface()
   {

   }

   bool frame_window_interface::_001IsFrameWnd()
   {
      return true;
   }

   void frame_window_interface::GetBorderRect(LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
   }


   void frame_window_interface::SetBorderRect(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

/*   ::user::OleFrameHook * frame_window_interface::GetNotifyHook()
   {
      return NULL;
   }*/

   void frame_window_interface::NotifyFloatingWindows(uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);
   }

   string frame_window_interface::get_window_default_matter()
   {

      if(m_pdocumenttemplate == NULL)
      {
         return "frame";
      }

      return m_pdocumenttemplate->m_strMatter;

   }

   ::user::interaction::e_type frame_window_interface::get_window_type()
   {
      return type_frame;
   }


   bool frame_window_interface::on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult)
   {

      if(::database::user::interaction::on_simple_command(ecommand, lparam, lresult))
         return true;

      return false;

   }


   void frame_window_interface::_guserbaseOnInitialUpdate(::ca2::signal_object * pobj)
   {
      SCAST_PTR(::ca2::message::base, pbase, pobj)
         FrameInitialUpdate * pfiu = (FrameInitialUpdate *) pbase->m_lparam.m_lparam;
      if(pfiu != NULL)
      {
         sp(::user::frame_window) pframe = (this);
         // if the frame does not have an active ::user::view, set to first pane
         sp(::user::view) pview = NULL;
         if (pframe->GetActiveView() == NULL)
         {
            sp(::user::interaction) pWnd = pframe->GetDescendantWindow("pane_first");
            if (pWnd != NULL && base < ::user::view >::bases(pWnd))
            {
               pview =  (pWnd.m_p);
               pframe->SetActiveView(pview, FALSE);
            }
         }

         if (pfiu->m_bMakeVisible)
         {
            // send initial update to all views (and other controls) in the frame
            pframe->SendMessageToDescendants(WM_INITIALUPDATE, 0, (LPARAM) 0, TRUE, TRUE);

            // give ::user::view a chance to save the focus (CFormView needs this)
            if (pview != NULL)
               pview->OnActivateFrame(WA_INACTIVE, pframe);

            // finally, activate the frame
            // (send the default show command unless the main desktop ::ca2::window)
            int32_t nCmdShow = -1;      // default
            ::ca2::application* pApp = &System;
            if (pApp != NULL && pApp->GetMainWnd() == pframe)
            {
               nCmdShow = pApp->m_nCmdShow; // use the parameter from WinMain
               pApp->m_nCmdShow = -1; // set to default after first time
            }
            bool bFullScreen;
            data_get("FullScreen", ::ca2::system::idEmpty, bFullScreen);
            if(bFullScreen)
            {
               WfiFullScreen(bFullScreen, false);
            }
            else
            {
               pframe->ActivateFrame(nCmdShow);
            }
            if (pview != NULL)
               pview->OnActivateView(TRUE, pview, pview);

         }

         sp(::user::document) pdoc = pfiu->m_pdoc;
         // update frame counts and frame title (may already have been visible)
         if(pdoc != NULL)
            pdoc->update_frame_counts();
         pframe->on_update_frame_title(TRUE);

         _001RedrawWindow();
      }
      pbase->set_lresult(0);
   }

   void frame_window_interface::install_message_handling(::ca2::message::dispatch *pinterface)
   {
//      ::user::frame_window_interface::install_message_handling(pinterface);
      database::user::interaction::install_message_handling(pinterface);
      IGUI_MSG_LINK(::ca2::message_frame_initial_update, pinterface, this, &frame_window_interface::_guserbaseOnInitialUpdate);
   }

   void frame_window_interface::_000OnDraw(::draw2d::graphics * pdc)
   {
      if(!m_bVisible)
         return;
      if(GetExStyle() & WS_EX_LAYERED
         || m_etranslucency == TranslucencyTotal
         || m_etranslucency == TranslucencyPresent)
      {
         sp(::user::interaction) pui;
         if(m_pguie != NULL)
            pui = m_pguie->get_bottom_child();
         else
            pui = get_bottom_child();

         while(pui != NULL)
         {
            if(pui->IsWindowVisible() && !base < MetaButton > ::bases(pui))
            {
               pui->_000OnDraw(pdc);
            }
            pui = pui->above_sibling();
         }
         _001DrawThis(pdc);
         if(m_pguie != NULL)
            pui = m_pguie->get_bottom_child();
         else
            pui = get_bottom_child();
         while(pui != NULL)
         {
            if(pui->IsWindowVisible() && base < MetaButton > ::bases(pui))
            {
               pui->_000OnDraw(pdc);
            }
            pui = pui->above_sibling();
         }
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }

   void frame_window_interface::_001OnDraw(::draw2d::graphics *pdc)
   {
      if((m_bWindowFrame
         || m_etranslucency == TranslucencyTotal
         || m_etranslucency == TranslucencyPresent) &&
         !Session.savings().is_trying_to_save(::ca2::resource_display_bandwidth))
      {
         ::uinteraction::frame::WorkSetClientInterface::_001OnDraw(pdc);
      }
      else
      {
         rect rect;
         sp(::user::interaction) pwnd = get_guie();
         pwnd->GetClientRect(rect);
         pdc->FillSolidRect(rect, ARGB(184 + 49 + 21 + 1, 184 + 49, 184 + 49, 177 + 49));
         //m_workset.OnDraw(pdc);
      }
   }

   bool frame_window_interface::WfiOnMove(bool bTracking)
   {
      if(!bTracking)
      {
         WindowDataSaveWindowRect();
      }
      return true;
   }

   
   bool frame_window_interface::WfiOnSize(bool bTracking)
   {
      
      if(!bTracking)
      {
         
         WindowDataSaveWindowRect();
         
      }
      
      return true;
      
   }

   
   void frame_window_interface::WfiOnClose()
   {
      
      post_message(WM_CLOSE);
      
   }
   

   void frame_window_interface::WfiOnMaximize()
   {
      
      _001WindowMaximize();
      
   }
   

   void frame_window_interface::WfiOnMinimize()
   {
      
      ShowWindow(SW_MINIMIZE);
      
   }
   

   void frame_window_interface::WfiOnRestore()
   {

      _001WindowRestore();

      class rect rectWindow;

      GetWindowRect(rectWindow);

      bool bOk;

      if(rectWindow.area() <= 0)
      {

         bOk = false;

      }
      else
      {

         bOk = false;

         class rect rectSession;

         for(int32_t i = 0; i < Session.get_monitor_count(); i++)
         {

            Session.get_monitor_rect(i, rectSession);

            if(rectSession.contains(rectWindow))
            {
               bOk = true;
               break;
            }

         }

      }

      if(!bOk)
      {
         SetWindowPos(ZORDER_TOP, 0, 0, 500, 400, SWP_SHOWWINDOW);
      }

   }


   bool frame_window_interface::DeferFullScreen(bool bFullScreen, bool bRestore)
   {
      if(bFullScreen)
      {
         sp(::user::interaction) pwndParentFrame = GetParentFrame();
         if(pwndParentFrame == NULL)
         {
            if(!WfiIsFullScreen())
            {
               WfiFullScreen(true, false);
               return true;
            }
            else
            {
               return false;
            }
         }
         frame_window_interface * pframe = dynamic_cast < frame_window_interface * > (pwndParentFrame.m_p);
         if(pframe == NULL)
         {
            if(!WfiIsFullScreen())
            {
               WfiFullScreen(true, false);
               return true;
            }
            else
            {
               return false;
            }
         }

         if(pframe->DeferFullScreen(bFullScreen, bRestore))
            return true;

         if(!WfiIsFullScreen())
         {
            WfiFullScreen(true, false);
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         if(WfiIsFullScreen())
         {
            WfiFullScreen(false, bRestore);
            return true;
         }
         sp(::user::interaction) pwndParentFrame = GetParentFrame();
         if(pwndParentFrame == NULL)
         {
            return false;
         }
         frame_window_interface * pframe = dynamic_cast < frame_window_interface * > (pwndParentFrame.m_p);
         if(pframe == NULL)
         {
            return false;
         }
         return pframe->DeferFullScreen(bFullScreen, bRestore);
      }
   }

   /*
   const char * frame_window_interface::GetIconWndClass(uint32_t dwDefaultStyle, const char * pszMatter)
   {
   HICON hIcon = ::ExtractIcon(
   System.m_hInstance,
   System.dir().path(Application.dir().matter(pszMatter), "icon.ico"),
   1);
   if (hIcon != NULL)
   {
   CREATESTRUCT cs;
   memset(&cs, 0, sizeof(CREATESTRUCT));
   cs.style = dwDefaultStyle;
   pre_create_window(cs);
   // will fill lpszClassName with default WNDCLASS name
   // ignore instance handle from pre_create_window.

   WNDCLASS wndcls;
   if (cs.lpszClass != NULL &&
   GetClassInfo(System.m_hInstance, cs.lpszClass, &wndcls) &&
   wndcls.hIcon != hIcon)
   {
   // register a very similar WNDCLASS
   return System.RegisterWndClass(wndcls.style,
   wndcls.hCursor, wndcls.hbrBackground, hIcon);
   }
   }
   return NULL;        // just use the default
   }
   */
   void frame_window_interface::defer_synch_layered()
   {
      bool bCalcLayered = calc_layered();
      if(is_different((GetExStyle() & WS_EX_LAYERED) != 0, bCalcLayered) != FALSE)
      {
         if(bCalcLayered)
         {
            ModifyStyleEx(0, WS_EX_LAYERED);
         }
         else
         {
            ModifyStyleEx(WS_EX_LAYERED, 0);
         }
         _001RedrawWindow();
      }
   }


   bool frame_window_interface::calc_layered()
   {
      if(m_bLayered)
      {
         return !Session.savings().is_trying_to_save(::ca2::resource_processing)
            && !Session.savings().is_trying_to_save(::ca2::resource_display_bandwidth);
      }
      else
      {
         return false;
      }
   }


   void frame_window_interface::data_on_after_change(::ca2::signal_object * pobj)
   {
      database::user::interaction::data_on_after_change(pobj);
      SCAST_PTR(database::change_event, phint, pobj);
      if(phint->m_key.m_idKey == "ca2"
         && phint->m_key.m_idIndex == "savings")
      {
         defer_synch_layered();
      }
   }

   bool frame_window_interface::IsFullScreen()
   {
      return WfiIsFullScreen();
   }

   bool frame_window_interface::ShowWindowFullScreen(bool bFullScreen, bool bRestore)
   {
      return WfiFullScreen(bFullScreen, bRestore);
   }

   void frame_window_interface::on_set_parent(sp(::user::interaction) pguieParent)
   {
      UNREFERENCED_PARAMETER(pguieParent);
      m_workset.m_pwndEvent = m_pimpl->m_pguie;

      if(m_bAutoWindowFrame)
      {
         if(pguieParent == NULL)
         {
            m_bWindowFrame = true;
            m_workset.Enable(true);
         }
         else
         {
            m_bWindowFrame = false;
            m_workset.Enable(false);
         }
      }
   }

   void frame_window_interface::assert_valid() const
   {
   }

   void frame_window_interface::dump(dump_context & dc) const
   {
      UNREFERENCED_PARAMETER(dc);
   }


} // namespace user


