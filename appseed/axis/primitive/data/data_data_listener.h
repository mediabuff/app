#pragma once


namespace data
{

   class data;


   class CLASS_DECL_AXIS data_listener :
      virtual public ::object
   {
   public:


      comparable_array < data * > m_dataptra;


      data_listener(sp(::axis::application) papp);
      virtual ~data_listener();


      bool listen(data * pdata, bool bListen = true);


      virtual void on_update_data(data * pdata, int32_t iHint);

   };




} // namespace data




