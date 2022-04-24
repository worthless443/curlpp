#include "curlpp/cURLpp.hpp"
#include "curlpp/Exception.hpp"

#include <cstdlib>
#include <iostream>


namespace 
{

	
  struct libcURLInstance
  {
    libcURLInstance();

    ~libcURLInstance()
      { curlpp::terminate(); }
  };
}


void curlpp::initialize(long flags)
{
  CURLcode code;
  code = curl_global_init(flags);
  libcurlRuntimeAssert("cannot initialize curlpp", code);
}


void curlpp::terminate()
{
  curl_global_cleanup();
}


curlpp::Cleanup::Cleanup()
{
  curlpp::initialize();
}


curlpp::Cleanup::~Cleanup()
{}

curlpp::curlOps::curlOps(std::string &url_, std::string &name_) : url{url_}, name{name_} {
  curlpp::initialize();
}
curlpp::curlOps::curlOps(std::string &url_) : url{url_} {
  curlpp::initialize();
}


std::string curlpp::curlOps::escape()
{
   std::string buffer;
   std::string p = curl_escape(url.c_str(), (int)url.size());
   if(!p.c_str()) {
      throw std::runtime_error("unable to escape the string"); //we got an error
   }
   else {
     std::cout << "success";
     //curl_free((char*)p.c_str());
   }

   return p;
}


std::string
curlpp::curlOps::unescape()
{
   std::string buffer;
   char* p = curl_unescape(url.c_str(), (int)url.size());
   if (!p)
   {
      throw RuntimeError("unable to escape the string"); //we got an error
   }
   else
   {
      buffer = p;
      curl_free(p);
   }
   return buffer;
}
std::string
curlpp::curlOps::getenv()
{
   std::string buffer;
   char* p = curl_getenv(name.c_str());
   if (!p)
   {
      throw RuntimeError("unable to get the environnement string"); //we got an error
   }
   else
   {
      buffer = p;
      free(p);
   }
   return buffer;
}


std::string
curlpp::curlOps::libcurlVersion()
{
  char* p = curl_version();
   if (!p)
   {
      throw RuntimeError("unable to get the libcurl version"); //we got an error
   }
      
   return std::string(p);
}


time_t 
curlpp::curlOps::getdate(const std::string & date, time_t * now)
{
  time_t return_value = curl_getdate(date.c_str(), now);
   if(!return_value)
   {
      throw RuntimeError("unable to get the date");
   }

   return return_value;
}
