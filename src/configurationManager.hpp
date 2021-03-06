#ifndef CONFIGURATIONMANAGER_HPP
#define CONFIGURATIONMANAGER_HPP 


#include <memory>
#include <string>
#include <boost/any.hpp>

class ConfigurationManager
{
public:
   static std::unique_ptr<ConfigurationManager> create();
   
   template< typename T>
   T getOption(const std::string& name)
   {
      return boost::any_cast<T>(getAny(name));
   }

   template <typename T>
   void setOption(const std::string& name, T thing)
   {
      setAny(name,thing);
   }

   virtual ~ConfigurationManager()
   {}

private:
   virtual boost::any getAny(const std::string& name) = 0;
   virtual void setAny(const std::string&name ,boost::any thing) = 0;
};
   

#endif /* CONFIGURAIONMANAGER_HPP */
