#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   listen_socket_base::listen_socket_base(base_socket_handler & h) :
      object(h.get_app()),
      base_socket(h),
      socket(h),
      m_depth(0),
      m_bDetach(false)
   {

   }


   listen_socket_base::~listen_socket_base()
   {

   }


   /** close file descriptor. */
   void listen_socket_base::close()
   {

      if (GetSocket() != INVALID_SOCKET)
      {

         close_socket(GetSocket());

      }

   }

   /** Bind and listen to any interface.
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(port_t port,int32_t depth)
   {
      if (IsIpv6())
      {
         ::net::address ad(AF_INET6, port);
         return Bind(ad, depth);
      }
      else
      {
         ::net::address ad(AF_INET, port);
         return Bind(ad, depth);
      }
   }

   int32_t listen_socket_base::Bind(const ::net::address & ad,int32_t depth)
   {
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }

   /** Bind and listen to any interface, with optional protocol.
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(port_t port,const string & protocol,int32_t depth)
   {
      if (IsIpv6())
      {
         ::net::address ad(AF_INET6, port);
         return Bind(ad.u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         ::net::address ad(AF_INET, port);
         return Bind(ad.u.m_addr.sin_addr, port, protocol, depth);
      }
   }

   /** Bind and listen to specific interface.
   \param intf Interface hostname
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const string & intf,port_t port,int32_t depth)
   {
      ::net::address ad(intf, port);
      if (ad.is_valid())
      {
         return Bind(ad, depth);
      }
#ifdef DEBUG
      log("Bind", 0, "name resolution of interface name failed", ::aura::log::level_fatal);
#endif
      return -1;
   }

   /** Bind and listen to specific interface.
   \param intf Interface hostname
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const string & intf,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(intf, port);
      if (ad.is_valid())
      {
         return Bind(ad, protocol, depth);
      }
#ifdef DEBUG
      log("Bind", 0, "name resolution of interface name failed", ::aura::log::level_fatal);
#endif
      return -1;
   }

   /** Bind and listen to ipv4 interface.
   \param a Ipv4 interface address
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in_addr a,port_t port,int32_t depth)
   {
      ::net::address ad(a, port);
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }
   /** Bind and listen to ipv4 interface.
   \param a Ipv4 interface address
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in_addr a,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(a, port);
      return Bind(ad, protocol, depth);
   }

   /** Bind and listen to ipv6 interface.
   \param a Ipv6 interface address
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in6_addr a,port_t port,int32_t depth)
   {
      ::net::address ad(a, port);
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }
   /** Bind and listen to ipv6 interface.
   \param a Ipv6 interface address
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in6_addr a,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(a, port);
      return Bind(ad, protocol, depth);
   }

   /** Bind and listen to network interface.
   \param ad Interface address
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const ::net::address & ad,const string & protocol,int32_t depth)
   {

      SOCKET s;
      m_iBindPort = ad.get_service_number();
      if ( (s = CreateSocket(ad.get_family(), SOCK_STREAM, protocol)) == INVALID_SOCKET)
      {
         return -1;
      }
      //::net::address a = ad;
      //if (ad.get_family() == AF_INET6)
      //{
      //
      //   ::net::ip_enum_sp e(allocer());

      //   ::array < ::net::address > ipa;

      //   e->enumerate(ipa);

      //   for (auto & item : ipa)
      //   {

      //      if (item.get_family() == AF_INET6)
      //      {

      //         if (!memcmp(&item.u.m_addr6.sin6_addr, &ad.u.m_addr6.sin6_addr, sizeof(ad.u.m_addr6.sin6_addr)))
      //         {

      //            a = item;

      //            break;

      //         }

      //      }

      //   }

      //}

      if (bind(s, ad.sa(), ad.sa_len()) == -1)
      {
#ifdef DEBUG
         log("bind() failed for port " + ::str::from(ad.get_service_number()), Errno, bsd_socket_error(Errno), ::aura::log::level_fatal);
#endif
         close_socket(s);
         return -1;
      }
      if (listen(s, depth) == -1)
      {
#ifdef DEBUG
         log("listen", Errno, bsd_socket_error(Errno), ::aura::log::level_fatal);
#endif
         close_socket(s);
         throw simple_exception(get_app(), "listen() failed for port " + ::str::from(ad.get_service_number()) + ": " + bsd_socket_error(Errno));
         return -1;
      }
      m_depth = depth;
      attach(s);
      return 0;
   }

   /** Return assigned port number. */
   //         port_t GetPort()
   //       {
   //        return GetSockPort();
   //   }

   /** Return listen queue depth. */
   int32_t listen_socket_base::GetDepth()
   {
      return m_depth;
   }

   /** OnRead on a listen_socket_base receives an incoming connection. */
   void listen_socket_base::OnRead()
   {
      char sz[sizeof(sockaddr_in6)];
      struct sockaddr * psa = (sockaddr *)sz;
      socklen_t sa_len = sizeof(sz);
      SOCKET a_s = accept(GetSocket(), psa, &sa_len);

      if (a_s == INVALID_SOCKET)
      {
#ifdef DEBUG
         log("accept", Errno, bsd_socket_error(Errno), ::aura::log::level_error);
#endif
         return;
      }
      if (!Handler().OkToAccept(this))
      {
#ifdef DEBUG
         log("accept", -1, "Not OK to accept", ::aura::log::level_warning);
#endif
         close_socket(a_s);
         return;
      }
      if (Handler().get_count() >= FD_SETSIZE)
      {
#ifdef DEBUG
         log("accept", (int32_t)Handler().get_count(), "base_socket_handler fd_set limit reached", ::aura::log::level_fatal);
#endif
         close_socket(a_s);
         return;
      }
      sp(socket) tmp = create_listen_socket();
      tmp->m_strCat = m_strCat;
      tmp->m_strCipherList = m_strCipherList;
      tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
      tmp -> SetIpv6( IsIpv6() );
      tmp -> set_parent(this);
      tmp -> attach(a_s);
      tmp -> SetNonblocking(true);
      tmp->SetRemoteHostname(::net::address(*psa));
      tmp->m_iBindPort = m_iBindPort;
      tmp -> SetConnected(true);
      tmp -> Init();
      tmp -> SetDeleteByHandler(true);
      Handler().add(tmp);
      if(m_bDetach)
      {
         tmp->detach();
      }
      if (tmp -> IsSSL()) // SSL Enabled socket
      {
         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
         // %! If that happens and negotiation fails, the 'tmp' instance is
         // %! still added to the list of active sockets in the sockethandler.
         // %! See bugfix for this in socket_handler::Select - don't set rwx
         // %! flags if CloseAndDelete() flag is true.
         // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
         // %! the add problem altogether, so ignore the above.
         // %! (OnSSLAccept does no longer call SSLNegotiate().)
         tmp -> OnSSLAccept();
      }
      else
      {
         tmp -> OnAccept();
      }


   }

   /** Please don't use this method.
   "accept()" is handled automatically in the OnRead() method. */
   SOCKET listen_socket_base::Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
   {
      return accept(socket, saptr, lenptr);
   }

   bool listen_socket_base:: HasCreator()
   {
      return false;
   }

   void listen_socket_base::OnOptions(int32_t,int32_t,int32_t,SOCKET)
   {
      SetSoReuseaddr(true);
   }


   sp(socket) listen_socket_base::create_listen_socket()
   {
      return NULL;
   }


} // namespace sockets





