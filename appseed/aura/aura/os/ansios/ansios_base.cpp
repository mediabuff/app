

CLASS_DECL_AURA void sleep(const duration & duration)
{
   
   timespec t;
   
   t.tv_sec = duration.m_iSeconds;
   
   t.tv_nsec = duration.m_iNanoseconds;
   
   ::nanosleep(&t, NULL);

}
