#include "framework.h"


namespace user
{


   LRESULT message::send()
   {
      return m_pguie->send_message(m_uiMessage, m_wparam, m_lparam);
   }

   UINT message::ThreadProcSendMessage(LPVOID lp)
   {
      message * pmessage = (message *) lp;
      pmessage->send();
      delete pmessage;
      return 0;
   }

   void message::post(sp(::user::interaction) puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, ::ca2::e_scheduling_priority epriority)
   {
      message * pmessage = new message;
      pmessage->m_pguie = puie;
      pmessage->m_uiMessage = uiMessage;
      pmessage->m_wparam = wparam;
      pmessage->m_lparam = lparam;
      __begin_thread(puie->get_app(), &ThreadProcSendMessage, pmessage, epriority);
   }

}
