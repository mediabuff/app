﻿#include "framework.h"


namespace database
{


   client::client()
   {

      m_pdataserver = NULL;

   }


   void client::initialize_data_client(server * pserver)
   {

      set_data_server(pserver);

   }


   bool client::set_data_server(server * pserver)
   {

      if(pserver != NULL)
      {

         synch_lock sl(pserver->m_pmutex);

         pserver->add_client(this);

      }

      m_pdataserver = pserver;

      return true;

   }


   client::~client()
   {

      if(m_pdataserver != NULL)
      {

         synch_lock sl(m_pdataserver->m_pmutex);

         try
         {

            m_pdataserver->remove_client(this);

         }
         catch(...)
         {

         }

      }

   }

   void client::data_on_before_change(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void client::data_on_after_change(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   bool client::data_set(class id id, bool b, update_hint * phint)
   {
      UNREFERENCED_PARAMETER(phint);
      int32_t i;
      if(b)
      {
         i = 1;
      }
      else
      {
         i = 0;
      }
      return data_set(id, i, phint);
   }


   bool client::data_set(
      class id id,

      var & var,
      update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, int32_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, int64_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

#ifdef APPLEOS

   bool client::data_set(class id id, long l, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(l);
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

#endif


   bool client::data_set(class id id, const char * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, const unichar * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }


   bool client::data_set(selection & selection, const char * lpsz, update_hint * puh)
   {
      ::count iCount = selection.get_item_count();
      bool bOk = true;
      for(index iItem = 0; iItem < iCount; iItem++)
      {
         selection_item & item = selection.get_item(iItem);
         if(!data_set(item.m_id, lpsz, puh))
         {
            bOk = false;
         }

      }
      return bOk;
   }

   bool client::data_set(selection & selection, var & var, update_hint * puh)
   {
      ::count iCount = selection.get_item_count();
      bool bOk = true;
      for(index iItem = 0; iItem < iCount; iItem++)
      {
         selection_item & item = selection.get_item(iItem);
         if(!data_set(item.m_id,var,puh))
         {
            bOk = false;
         }

      }
      return bOk;
   }

   bool client::data_set(class id id, ::file::file & readable, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, readable, puh);
      }
      return false;
   }

   bool client::data_set(class id id, ::file::serializable & obj, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_save(this, id, obj, puh))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_set(class id id, ::file::istream & istream, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, istream, puh);
      }
      return false;
   }


   bool client::data_get(class id id, bool & b)
   {
      int32_t i;
      if(!data_get(id, i))
         return false;
      b = i != 0;
      return true;
   }


   bool client::data_get(class id id, var & var)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_load(this, id, var);
      }
      return false;
   }

   bool client::data_get(class id id, int32_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, int64_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

#ifdef APPLEOS
   bool client::data_get(class id id, long & l)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         l = var.int64();
         return true;
      }
      return false;
   }
#endif

   bool client::data_get(class id id, string & str)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         if(var.get_type() != var::type_string)
            return false;
         str = var.m_str;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::file & writable)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, writable))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::serializable & obj)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, obj))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::ostream & ostream)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, ostream))
            return false;
         return true;
      }
      return false;
   }


   bool client::data_pulse_change(class id id, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_pulse_change(this, id, puh))
            return false;
         return true;
      }
      return false;
   }


   client_array::client_array()
   {

   }

   client_array::~client_array()
   {
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         this->element_at(i)->m_pdataserver = NULL;
      }
   }

   void client_array::add_client(client *pclient)
   {
      if(pclient != dynamic_cast < client * > (this))
      {
         add_unique(pclient);
      }
   }


   ::count client_array::get_client_count()
   {

      return this->get_size();

   }


   client * client_array::client_at(index iClient)
   {

      return this->element_at(iClient);

   }


   void client_array::remove_client(client *pclient)
   {

      remove(pclient);

   }


   string client::calc_data_key(::database::id & id)
   {

      string str;

      str = get_data_id();

      str += ".";

      str += ::str::from(id);

      return str;

   }


   id client::get_data_id()
   {

      if (m_dataid2.m_id.is_empty() || m_bDataKeyModified)
      {

         update_data_id();

      }

      return m_dataid2;

   }


   string client::calc_data_id()
   {

      return calc_default_data_id();

   }


   void client::update_data_id()
   {

      string strDataKey = calc_data_id();

      if (strDataKey.is_empty())
      {

         strDataKey = calc_default_data_id();

      }

      if (strDataKey.replace_ci_count("&data_source=local", "") > 0)
      {

         strDataKey += "&data_source=local&";

      }

      m_dataid2 = strDataKey;

      m_bDataKeyModified = false;

   }


   string client::calc_default_data_id()
   {

      string str;

      str = Application.m_strAppName;

      if (string(Application.get_data_id().m_id).find_ci("&data_source=local") >= 0)
      {

         str += "&data_source=local&";

      }
      else
      {

         str += "://";

      }

      {

         string strType = typeid(*this).name();

         ::str::begins_eat_ci(strType, "class ");

         str += strType;

      }

      if (m_strDataKeyModifier.has_char())
      {

         str += "/";

         str += m_strDataKeyModifier;

      }

      return str;

   }


   void client::set_data_key_modifier(string strDataKeyModifier)
   {

      m_strDataKeyModifier = strDataKeyModifier;

      m_bDataKeyModified = true;

   }

   string client::get_data_key_modifier()
   {

      return m_strDataKeyModifier;

   }


   void client::add_up_data_key_modifier(string strDataKeyModifier)
   {

      if (get_data_key_modifier().find_ci(strDataKeyModifier) < 0)
      {

         set_data_key_modifier(get_data_key_modifier() + strDataKeyModifier);

      }

   }


   void client::set_local_data_key_modifier()
   {

      add_up_data_key_modifier("&data_source=local&");

   }


} // namespace database



namespace file
{


   data_trigger_ostream::data_trigger_ostream(data_trigger_ostream && d):
      byte_stream(::move(d)),
      m_file(::move(d.m_file)),
      m_id(::move(d.m_id))
   {

      m_spfile = &m_file;
      m_pclient = d.m_pclient;
      d.m_pclient = NULL;

   }


   data_trigger_ostream::data_trigger_ostream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      m_file(pclient->get_app())
   {

      m_spfile = &m_file;
      m_id = id;
      m_pclient = pclient;

   }

   data_trigger_ostream::~data_trigger_ostream()
   {

      if(m_pclient != NULL)
      {
         seek_to_begin();
         m_pclient->data_set(m_id,(::file::istream &)*this);

      }

   }

   data_trigger_istream::data_trigger_istream(data_trigger_istream && d) :
      byte_stream(::move(d)),
      m_file(::move(d.m_file))
   {
      m_spfile = &m_file;
   }

   data_trigger_istream::data_trigger_istream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      m_file(pclient->get_app())
   {
      m_spfile = &m_file;
      pclient->data_get(id,(::file::ostream &)*this);
      seek_to_begin();
   }

   data_trigger_istream::~data_trigger_istream()
   {

   }


} // namespace file


