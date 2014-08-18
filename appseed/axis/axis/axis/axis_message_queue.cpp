#include "framework.h"


message_queue::message_queue(sp(::axis::application) papp) :
   element(papp)
{

   m_plistener          = NULL;

}

message_queue::~message_queue()
{

}


bool message_queue::create_message_queue(const char * pszName, ::message_queue_listener * plistener)
{

   m_plistener = plistener;

   return ::user::interaction::create_message_queue(pszName);

}


void message_queue::message_handler(signal_details * pobj)
{
   
   message_queue_message_handler(pobj);

   if(pobj->m_bRet)
      return;

   return ::user::interaction::message_handler(pobj);

}


void message_queue::message_queue_message_handler(signal_details * pobj)
{

   if(m_plistener != NULL)
   {

      m_plistener->message_queue_message_handler(pobj);

   }

}




