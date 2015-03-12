#pragma once


namespace file
{


   class CLASS_DECL_AURA stream :
      virtual public ostream,
      virtual public istream
   {
   public:

      
      stream();
      stream(buffer_sp pbuffer);
      stream(const stream & stream);
      virtual ~stream();

      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

      virtual void * get_internal_data();
      virtual ::primitive::memory_size get_internal_data_size() const;
      virtual bool set_internal_data_size(::primitive::memory_size c);
      virtual file_position get_position() const;


   };


} // namespace file


