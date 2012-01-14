#include "StdAfx.h"
#include <ShlObj.h>


namespace netnode
{


   service::service(::ca::application * papp) :
      ca(papp),
      plain_service(papp)
   {
   }

   service::~service(void)
   {
   }

   void service::ServiceThread()
   {
      ::ca::application * pcaapp = get_app();

      Sys(pcaapp).set_thread(&Sys(pcaapp->m_psystem));

      m_stopping = false;

      netnode::application * papp = &Application;

      papp->m_pscriptmanager = new dynamic_source::script_manager(pcaapp);

      App(pcaapp).m_strFontopusServer		= System.db().data_load("fontopus_server", ::database::id(), ::database::id());
      App(pcaapp).m_strDatabaseServerHost	= System.db().data_load("database_server", ::database::id(), ::database::id());
      App(pcaapp).m_iDatabaseServerPort	= System.db().data_load("database_port", ::database::id(), ::database::id());
      if(App(pcaapp).m_strDatabaseServerHost.is_empty())
      {
         App(pcaapp).m_strDatabaseServerHost = "localhost";
      }
      if(App(pcaapp).m_iDatabaseServerPort <= 0)
      {
         App(pcaapp).m_iDatabaseServerPort = 0;
      }



      stringa stra;
      stra = System.db().data_load("netnode", ::database::id(), ::database::id());
      for(int i = 0; i < stra.get_size(); i++)
         //for(int i = 0; i < 1; i++)
      {
         m_threadptra.add(AfxBeginThread < socket_thread > (get_app()));
         socket_thread * pthread = m_threadptra.last_element();
         {
            pthread->m_evInitialized.wait();
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 80;
            pthread->m_pservice = this;
            pthread->PostThreadMessage(WM_APP, 0, 0);
         }
      }
      stra = System.db().data_load("netnodes", ::database::id(), ::database::id());
      for(int i = 0; i < stra.get_size(); i++)
         //for(int i = 0; i < 1; i++)
      {
         m_threadptra.add(AfxBeginThread < socket_thread > (get_app()));
         socket_thread * pthread = m_threadptra.last_element();
         {
            pthread->m_evInitialized.wait();
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 443;
            pthread->m_pservice = this;
            pthread->m_strCat = System.db().data_load("netnodec", stra[i], ::database::id());
            pthread->PostThreadMessage(WM_APP, 0, 0);
         }
      }


      while (!m_stopping)
      {
         Sleep(1000);
      }
      Sleep(10000);

   }



} // namespace netnode


