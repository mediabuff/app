#pragma once

#if defined(LINUX) || defined(APPLEOS)
#include <sys/types.h>
#include <sys/sem.h>
#endif

class CLASS_DECL_AURA event :
   public event_base
{
public:

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int32_t           m_iSignalId;  // meaningful only when m_bManualEvent
   void *            m_pcond; // pthread_cond_t
   void *            m_pmutex; // pthread_mutex_t;
#endif


   event(::aura::application * papp, bool bInitiallyOwn = FALSE, bool bManualReset = FALSE, const char * lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
   virtual ~event()
#ifdef METROWIN
       { }
#else
      ;
#endif

  // using event_base::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using sync_object::unlock;
   virtual bool unlock();

   virtual void * get_os_data() const;

   bool SetEvent();
   bool set_event() {return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

/**
* \brief	Session independent waitables (windows version)
*/

	///  \brief		waits for an event forever
	virtual wait_result wait ();

	///  \brief		waits for an event for a specified time
	///  \param		duration time period to wait for an event
	///  \return	waiting action result as WaitResult
   virtual wait_result wait (const duration & duration);

   bool is_signaled() const;

};

