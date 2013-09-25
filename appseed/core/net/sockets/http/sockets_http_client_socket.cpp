#include "framework.h"


namespace sockets
{


   http_client_socket::http_client_socket(base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      m_content_length((size_t)-1),
      m_content_ptr(0),
      m_b_complete(false),
      m_b_close_when_complete(false),
      m_memoryfile(h.get_app()),
      m_mutexData(h.get_app())
   {


      m_pfile           = NULL;


   }


   http_client_socket::http_client_socket(base_socket_handler & h, const string & strUrlParam) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      m_content_length((size_t)-1),
      m_content_ptr(0),
      m_b_complete(false),
      m_b_close_when_complete(false),
      m_memoryfile(h.get_app()),
      m_mutexData(h.get_app())
   {

      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_request.attr(__id(http_protocol))     = m_protocol;
      outheader(__id(host))                   = m_host;
      m_request.attr(__id(request_uri))       = strRequestUri;
      m_response.attr(__id(request_uri))      = strRequestUri;

      m_strUrl = strUrlParam;

      m_pfile = NULL;

   }


   http_client_socket::~http_client_socket()
   {
   }


   void http_client_socket::OnFirst()
   {
      if (!IsResponse())
      {
         log("OnFirst", 0, "Response expected but not received - aborting", ::core::log::level_fatal);
         SetCloseAndDelete();
      }
      m_content = m_response.attr(__id(http_version)) + " " +
                  m_response.attr(__id(http_status_code)) + " " +
                  m_response.attr(__id(http_status)) + "\r\n";
   }


   void http_client_socket::OnHeader(id key, const string & value)
   {
      m_content += key + ": " + value + "\r\n";
      m_response.m_propertysetHeader[key] = value;
      if (key == __id(content_length))
      {
         m_content_length = atoi(value);
      }
      else if (key == __id(content_type))
      {
         m_content_type = value;
      }
      else if (key == __id(set_cookie))
      {
         m_response.m_cookies.add(value);
      }
   }


   void http_client_socket::OnHeaderComplete()
   {

      http_tunnel::OnHeaderComplete();

      m_memoryfile.Truncate(0);

      if(m_content_length != ((size_t) (-1)))
      {
         m_memoryfile.allocate_internal(m_content_length);
          if(outheader(__id(content_encoding)).compare_value_ci("gzip") != 0)
          {
              
              m_iFinalSize = m_content_length;
          }
      }

      m_memoryfile.seek_to_begin();

      if(::str::ends(m_strUrl, "arialuni.ttf"))
      {
         TRACE("Debug Here : arialuni.ttf");
      }


      if(m_content_length > 0)
      {
         m_event.ResetEvent();
         m_bExpectResponse = true;
      }
      else
      {
         m_bExpectResponse = false;
      }

      if(::str::ends(m_strUrl, "en_us_international.xml"))
      {
         TRACE("Debug Here");
      }


      if(::str::ends(m_strUrl, "text_select.xml"))
      {
         TRACE("Debug Here");
      }


   }


   void http_client_socket::OnDataComplete()
   {

      if(!m_bNoClose)
      {

         SetCloseAndDelete();

      }

      m_bExpectRequest = false;

      m_bExpectResponse = false;

   }


   void http_client_socket::OnData(const char *buf,size_t len)
   {

      OnDataArrived(buf, len);

      m_content_ptr += len;

      if(m_pfile != NULL )
      {
         
         if(outheader(__id(content_encoding)).compare_value_ci("gzip") != 0)
         {
            
            m_pfile->write(buf, len);

            if (m_content_ptr == m_content_length && m_content_length && m_content_length != ((size_t) (-1)))
            {

               m_bExpectResponse = false;

            }
            else
            {

               m_event.ResetEvent();

               m_bExpectResponse = true;

            }

            return;
            
         }
         
      }

      m_memoryfile.write(buf, len);

      if (m_content_ptr == m_content_length && m_content_length && m_content_length != ((size_t) (-1)))
      {

         m_b_complete = true;

         if(outheader(__id(content_encoding)).compare_value_ci("gzip") == 0)
         {
            System.compress().ungz(m_memoryfile);
         }
         if(m_pfile != NULL)
         {
            m_pfile->write(m_memoryfile.get_data(), m_memoryfile.get_size());
            m_iFinalSize = m_pfile->get_length();
         }
         OnContent();
         if (m_b_close_when_complete)
         {
            SetCloseAndDelete();
         }

         m_bExpectResponse = false;

      }
      else
      {

         m_event.ResetEvent();

         m_bExpectResponse = true;

      }

   }


   void http_client_socket::OnDataArrived(const char * buf, size_t len)
   {

      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
   }


   void http_client_socket::OnDelete()
   {
      if (!m_b_complete)
      {
         m_b_complete = true;
         OnContent();
      }
   }

   const string & http_client_socket::GetContent()
   {
      return m_content;
   }

   size_t http_client_socket::GetContentLength()
   {
      if(m_content_length == ((size_t)-1))
      {
         return 0;
      }
      else
      {
         return m_memoryfile.get_size();
      }
   }


   size_t http_client_socket::GetContentPtr()
   {
      return m_content_ptr;
   }

   size_t http_client_socket::GetPos()
   {
      return m_content_ptr;
   }

   bool http_client_socket::Complete()
   {
      return m_b_complete;
   }

   const unsigned char *http_client_socket::GetDataPtr() const
   {

      return m_memoryfile.get_data();

   }

   size_t http_client_socket::GetDataLength() const
   {

      return m_memoryfile.get_size();

   }


   void http_client_socket::OnContent()
   {
   }

   void http_client_socket::SetCloseOnComplete(bool x)
   {
      m_b_close_when_complete = x;
   }

   const string & http_client_socket::GetUrlProtocol()
   {
      return m_protocol;
   }

   const string & http_client_socket::GetUrlFilename()
   {
      return m_url_filename;
   }

   const string & http_client_socket::GetContentType()
   {
      return m_content_type;
   }

   void http_client_socket::Url(const string & url_in, string & host, port_t & port)
   {
      string url;
      url_this(url_in, m_protocol, m_host, m_port, url, m_url_filename);
      m_request.attr("url") = url;
      host = System.url().get_server(url);
      port = (port_t) System.url().get_port(url);
   }


   void http_client_socket::request_url(string strUrlParam)
   {
      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_request.attr(__id(http_protocol))     = m_protocol;
      outheader(__id(host))                   = m_host;
      m_request.attr(__id(request_uri))       = strRequestUri;
      m_response.attr(__id(request_uri))      = strRequestUri;

      m_strUrl = strUrlParam;

      m_pfile = NULL;
   }

} // namespace sockets



