#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   stream_socket::stream_socket(base_socket_handler& h) : 
      object(h.get_app())
      ,base_socket(h)
      ,socket(h)
      ,m_bConnecting(false)
      ,m_connect_timeout(5)
      ,m_flush_before_close(true)
      ,m_connection_retry(0)
      ,m_retries(0)
      ,m_call_on_connect(false)
      ,m_b_retry_connect(false)
      ,m_shutdown(0)
   {

   }


   stream_socket::~stream_socket()
   {

   }


   void stream_socket::SetConnecting(bool x)
   {

      if (x != m_bConnecting)
      {

         m_bConnecting = x;

         if (x)
         {

            SetTimeout( GetConnectTimeout() );

         }
         else
         {

            SetTimeout( 0 );

         }

      }

   }


   bool stream_socket::Connecting()
   {

      return m_bConnecting;

   }


   bool stream_socket::Ready()
   {
      if (GetSocket() != INVALID_SOCKET && !Connecting() && !CloseAndDelete())
         return true;
      return false;
   }


   void stream_socket::SetConnectTimeout(int32_t x)
   {
      m_connect_timeout = x;
   }


   int32_t stream_socket::GetConnectTimeout()
   {
      return m_connect_timeout;
   }


   void stream_socket::SetFlushBeforeClose(bool x)
   {
      m_flush_before_close = x;
   }


   bool stream_socket::GetFlushBeforeClose()
   {
      return m_flush_before_close;
   }


   int32_t stream_socket::GetConnectionRetry()
   {
      return m_connection_retry;
   }


   void stream_socket::SetConnectionRetry(int32_t x)
   {
      m_connection_retry = x;
   }


   int32_t stream_socket::GetConnectionRetries()
   {
      return m_retries;
   }


   void stream_socket::IncreaseConnectionRetries()
   {
      m_retries++;
   }


   void stream_socket::ResetConnectionRetries()
   {
      m_retries = 0;
   }


   void stream_socket::SetCallOnConnect(bool x)
   {
      Handler().AddList(GetSocket(), LIST_CALLONCONNECT, x);
      m_call_on_connect = x;
   }


   bool stream_socket::CallOnConnect()
   {
      return m_call_on_connect;
   }


   void stream_socket::SetRetryClientConnect(bool x)
   {
      Handler().AddList(GetSocket(), LIST_RETRY, x);
      m_b_retry_connect = x;
   }


   bool stream_socket::RetryClientConnect()
   {
      return m_b_retry_connect;
   }




   void stream_socket::SetShutdown(int32_t x)
   {
      m_shutdown = x;
   }


   int32_t stream_socket::GetShutdown()
   {
      return m_shutdown;
   }

   int32_t stream_socket::Protocol()
   {
      
      throw interface_only_exception(get_app());

   }

} // namespace sockets

