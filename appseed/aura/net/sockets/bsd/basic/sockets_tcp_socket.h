﻿/** \file tcp_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#pragma once

#include "aura/net/sockets/bsd/internal/ssl_ticket_key.h"
#include "sockets_stream_socket.h"


#define TCP_BUFSIZE_READ (16400)
#define TCP_OUTPUT_CAPACITY 1024000

namespace sockets
{



   /** socket implementation for TCP.
   \ingroup basic */
   class CLASS_DECL_AURA tcp_socket :
      virtual public stream_socket
   {
      /** \defgroup internal Internal utility */
   public:

      array < ssl_ticket_key >   m_ticketkeya;


      static bool s_bReuseSession; // Default System Wide Setting

      /** Output buffer struct.
      \ingroup internal */
      string m_strTlsHostName;
      struct OUTPUT
      {
         OUTPUT() : _b(0), _t(0), _q(0) {}
         OUTPUT(const char *buf, int32_t len) : _b(0), _t(len), _q(len)
         {
            memcpy(_buf, buf, len);
         }
         int32_t Space()
         {
            return TCP_OUTPUT_CAPACITY - _t;
         }
         void add(const char *buf, int32_t len)
         {
            memcpy(_buf + _t, buf, len);
            _t += len;
            _q += len;
         }
         int32_t remove(int32_t len)
         {
            _b += len;
            _q -= len;
            return _q;
         }
         const char *Buf()
         {
            return _buf + _b;
         }
         int32_t Len()
         {
            return _q;
         }
         int32_t _b;
         int32_t _t;
         int32_t _q;
         char _buf[TCP_OUTPUT_CAPACITY];
      };
      typedef list<OUTPUT> output_list;

      ::file::circular_file ibuf; ///< Circular input buffer
      string m_strUrl;

      mutex *        m_pmutexSslCtx;
      //
      bool m_b_input_buffer_disabled;
      uint64_t m_bytes_sent;
      uint64_t m_bytes_received;
      memory         m_memRead;
      output_list m_obuf; ///< output buffer
      OUTPUT *m_obuf_top; ///< output buffer on top
      size_t m_transfer_limit;
      size_t m_output_length;

      bool     m_bReuseSession;
      int32_t m_socks4_state; ///< socks4 support
      char m_socks4_vn; ///< socks4 support, temporary var
      char m_socks4_cd; ///< socks4 support, temporary var
      uint16_t m_socks4_dstport; ///< socks4 support
      uint32_t m_socks4_dstip; ///< socks4 support

      string m_strConnectHost;
      port_t m_iConnectPort;

      int32_t m_resolver_id; ///< Resolver id (if any) for current open call

      bool m_bReconnect; ///< Reconnect on lost connection flag
      bool m_bTryingReconnect; ///< Trying to reconnect
      string m_strHost;

      bool m_bCertCommonNameCheckEnabled;

      bool                       m_bClientSessionSet;
      string                     m_strInitSSLClientContext;

      /** Constructor with standard values on input/output buffers. */
      tcp_socket(base_socket_handler& );
      /** Constructor with custom values for i/o buffer.
      \param h base_socket_handler reference
      \param isize Input buffer size
      \param osize Output buffer size */
      tcp_socket(base_socket_handler& h,size_t isize,size_t osize);
      virtual ~tcp_socket();


      using ::sockets::stream_socket::open;
      bool open(const ::net::address & address, bool skip_socks = false);
      bool open(const ::net::address & address, const ::net::address & addressBind,bool skip_socks = false);
      /** open connection.
      \param host Hostname
      \param port Port number */
      bool open(const string &host,port_t port);

      /** Connect timeout callback. */
      void OnConnectTimeout();
#ifdef _WIN32
      /** Connection failed reported as exception on win32 */
      void OnException();
#endif

      /** close file descriptor - internal use only.
      \sa SetCloseAndDelete */
      void close();

      /** Send buffer of bytes.
      \param buf buffer pointer
      \param len Length of data
      \param f Dummy flags -- not used */
      using ::sockets::socket::write;
      virtual void write(const void *buf, memory_size_t c);
      /** This callback is executed after a successful read from the socket.
      \param buf Pointer to the data
      \param len Length of the data */
      virtual void OnRawData(char *buf,size_t len);

      /** Called when output buffer has been sent.
      Note: Will only be called IF the output buffer has been used.
      Send's that was successful without needing the output buffer
      will not generate a call to this method. */
      virtual void OnWriteComplete();
      /** Number of bytes in input buffer. */
      size_t GetInputLength();
      /** Number of bytes in output buffer. */
      size_t GetOutputLength();

      /** Callback fires when a socket in line protocol has read one full line.
      \param line Line read */
      void OnLine(const string & line);
      /** get counter of number of bytes received. */
      uint64_t GetBytesReceived(bool clear = false);
      /** get counter of number of bytes sent. */
      uint64_t GetBytesSent(bool clear = false);

      /** Socks4 specific callback. */
      void OnSocks4Connect();
      /** Socks4 specific callback. */
      void OnSocks4ConnectFailed();
      /** Socks4 specific callback.
      \return 'need_more' */
      bool OnSocks4Read();

      /** Callback executed when resolver thread has finished a resolve request. */
      void OnResolved(int32_t id, const ::net::address & addr);
      /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
      void OnSSLConnect();
      /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
      void OnSSLAccept();
      /** This method must be implemented to initialize
      the ssl context for an outgoing connection. */
      virtual void InitSSLClient();
      /** This method must be implemented to initialize
      the ssl context for an incoming connection. */
      virtual void InitSSLServer();

      /** Flag that says a broken connection will try to reconnect. */
      void SetReconnect(bool = true);
      /** Check reconnect on lost connection flag status. */
      bool Reconnect();
      /** Flag to determine if a reconnect is in progress. */
      void SetIsReconnect(bool x = true);
      /** socket is reconnecting. */
      bool IsReconnect();

      void DisableInputBuffer(bool = true);

      void OnOptions(int32_t,int32_t,int32_t,SOCKET);

      void SetLineProtocol(bool = true);

      // TCP options
      bool SetTcpNodelay(bool = true);

      virtual string get_connect_host();
      virtual port_t get_connect_port();

      virtual int32_t Protocol();

      /** Trigger limit for callback OnTransferLimit. */
      void SetTransferLimit(size_t sz);
      /** This callback fires when the output buffer drops below the value
      set by SetTransferLimit. Default: 0 (disabled). */
      virtual void OnTransferLimit();


      void OnRead();
      using ::sockets::stream_socket::read;
      virtual int read(void * buf, int n);
      virtual int recv(void * buf, int n);
      virtual void on_read(const void * buf, int n );
      void OnWrite();


      virtual long cert_common_name_check(const char * common_name);
      virtual void enable_cert_common_name_check(bool bEnable = true);

      /** SSL; Initialize ssl context for a client socket.
      \param meth_in SSL method */
      void InitializeContext(const string & context, const SSL_METHOD *meth_in = NULL);
      /** SSL; Initialize ssl context for a server socket.
      \param keyfile Combined private key/certificate file
      \param password Password for private key
      \param meth_in SSL method */
      void InitializeContext(const string & context, const string & keyfile, const string & password, const SSL_METHOD *meth_in = NULL);
      /** SSL; Initialize ssl context for a server socket.
      \param certfile Separate certificate file
      \param keyfile Combined private key/certificate file
      \param password Password for private key
      \param meth_in SSL method */
      void InitializeContext(const string & context, const string & certfile, const string & keyfile, const string & password, const SSL_METHOD *meth_in = NULL);
      /** SSL; Password callback method. */
      /** SSL; get pointer to ssl context structure. */
      virtual SSL_CTX *GetSslContext();
      /** SSL; get pointer to ssl structure. */
      virtual SSL *GetSsl();
      /** ssl; still negotiating connection. */
      bool SSLNegotiate();
      /** SSL; get ssl password. */
      const string & GetPassword();


      virtual string get_url();

      virtual string get_short_description();


      /** the actual send() */
      int try_write(const void * buf, int len);
      /** add data to output buffer top */
      void buffer(const void * buf, int len);



   };

   extern "C"
   int32_t tcp_socket_SSL_password_cb(char *buf,int32_t num,int32_t rwflag,void *userdata);


} // namespace sockets



