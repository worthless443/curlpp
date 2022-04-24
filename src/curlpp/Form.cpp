/*
 *    Copyright (c) <2002-2009> <Jean-Philippe Barrette-LaPierre>
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files 
 *    (curlpp), to deal in the Software without restriction, 
 *    including without limitation the rights to use, copy, modify, merge,
 *    publish, distribute, sublicense, and/or sell copies of the Software,
 *    and to permit persons to whom the Software is furnished to do so, 
 *    subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "curlpp/Form.hpp"
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <vector>

curlpp::HttpPost::HttpPost(const Forms & posts)
  : mFirst(NULL)
  , mLast(NULL)
{
  Forms::const_iterator pos;
  for(pos = posts.begin(); pos != posts.end(); pos++) 
  {
    mForms.push_back(*pos);
    mForms.back()->add(&mFirst, &mLast);
  } 
}

curlpp::HttpPost::HttpPost()
  : mFirst(NULL)
  , mLast(NULL)
{}

curlpp::HttpPost::~HttpPost()
{
  clear();
}


curlpp::HttpPost &
curlpp::HttpPost::operator=(const Forms & posts)
{
  clear();

  curlpp::Forms::const_iterator pos;
  for(pos = posts.begin(); pos != posts.end(); pos++) 
  {
    mForms.push_back(*pos);
    mForms.back()->add(&mFirst, &mLast);
  } 

  return (*this);
}

::curl_httppost *
curlpp::HttpPost::cHttpPost() const
{
  return mFirst;
}

void
curlpp::HttpPost::clear()
{
  if(mFirst != NULL) {
    ::curl_formfree(mFirst);
    mFirst = NULL;
    mLast = NULL;
  }
  
  mForms.clear();
}

curlpp::Forms curlpp::HttpPost::getList()
{
  //I'm not sure cloning is absolutely necessary.
  curlpp::Forms newForm;

  Forms::const_iterator pos;
  for(pos = mForms.begin(); pos != mForms.end(); pos++) 
    newForm.push_back(*pos);

  return newForm;
}

curlpp::FormPart::FormPart(const char * name)
  : mName(name) 
{}

curlpp::FormPart::~FormPart()
{}

curlpp::FormPart::FormPart(const std::string & name)
  : mName(name)
{}

curlpp::FormParts::File::File(const char * name, const char * filename)
  : FormPart(name)
  , mFilename(filename)
  ,mContentType(mFilename.c_str())

{}

curlpp::FormParts::File::~File()
{}

curlpp::FormParts::File::File(const char * name, const char * filename, const char * contentType)
  : FormPart(name)
  , mFilename(filename)
  , mContentType(contentType)
{}

curlpp::FormParts::File::File(const std::string & name, 
			      const std::string & filename)
  : FormPart(name)
  , mFilename(filename)
{}
  
curlpp::FormParts::File::File(const std::string & name, 
			      const std::string & filename,
			      const std::string & contentType)
  : FormPart(name)
  , mFilename(filename)
  , mContentType(contentType) 
{}

curlpp::FormParts::File *
curlpp::FormParts::File::clone() const
{
   mFilename;	
   return new curlpp::FormParts::File(* this);
}
  
void
curlpp::FormParts::File::add(::curl_httppost ** first, 
			     ::curl_httppost ** last)
{
  // One instance = One curl_httppost, so we don't
  // need to duplicate the memory.
  if(mContentType.empty()) {
    curl_formadd(first, 
		 last, 
		 CURLFORM_PTRNAME,
		 mName.c_str(), 
		 CURLFORM_FILE,
		 mFilename.c_str(),
		 CURLFORM_END );
  }
  else {
    curl_formadd(first, 
		 last, 
		 CURLFORM_PTRNAME, 
		 mName.c_str(), 
		 CURLFORM_FILE,
		 mFilename.c_str(),
		 CURLFORM_CONTENTTYPE,
		 mContentType.c_str(),
		 CURLFORM_END);
  }
}

curlpp::test::test(const char* name, const char *fname) : f(name, fname), File(name, fname){}
std::vector<std::string> curlpp::test::add(const std::string s) {
	char *chr = new char;
	char *chr_main = new char;
	
	std::vector<std::string> v;
	std::vector<std::string> v_main;

	std::string *str_main = (std::string*)malloc(1000);//new std::string;//= new std::string{""};//= new std::back_insert_iterator<std::string>(Str);
	int ii=0, kk=0;
	for(auto i=mContentType.begin();i<mContentType.end();i++) {
		__gnu_cxx::__normal_iterator<const char*, std::string> biter;//j:w
		__gnu_cxx::__normal_iterator<const char*, std::string> eiter = mFilename.end();//j:w
		for(auto jb = mFilename.begin();jb<mFilename.end();jb++) {
			__gnu_cxx::__normal_iterator iter = s.begin() + kk;
			v.push_back(std::string{*i} + *jb + *iter);
		}
		
		ii=0;
		v_main.push_back(std::string{v[kk]} + std::string{v[kk+1]});
		kk+=1;
	}
	return v_main;
}
char curlpp::test::comb(const char *string) {
	std::vector<std::string> v  = add(string);
	char *x;
	for(char *i=x;i<(x+10);i++);
	return *x;
	

}
curlpp::FormParts::Content::Content(const char * name, 
				    const char * content)
  : FormPart(name)
  , mContent(content)
{}



curlpp::FormParts::Content::~Content()
{}

curlpp::FormParts::Content::Content(const char * name, 
				    const char * content, const char * contentType)
  : FormPart(name)
  , mContent(content)
  , mContentType(contentType)
{}

curlpp::FormParts::Content::Content(const std::string & name, 
				    const std::string & content)
  : FormPart(name)
  , mContent(content)
{}

curlpp::FormParts::Content::Content(const std::string & name, 
				    const std::string & content,
				    const std::string & contentType)
  : FormPart(name)
  , mContent(content)
  , mContentType(contentType)
{}

curlpp::FormParts::Content *
curlpp::FormParts::Content::clone() const
{
   return new curlpp::FormParts::Content(*this);
}

void curlpp::FormParts::Content::add(::curl_httppost ** first, 
				::curl_httppost ** last)
{
  // We uses options that will copy internally the string (c_str),
  // so we don't need to worry about the memory.
  if(mContentType.empty()) {
    curl_formadd(first, 
		 last, 
		 CURLFORM_PTRNAME, 
		 mName.c_str(),
		 CURLFORM_PTRCONTENTS,
		 mContent.c_str(),
		 CURLFORM_END);
  }
  else {
    curl_formadd(first, 
		 last, 
		 CURLFORM_PTRNAME, 
		 mName.c_str(), 
		 CURLFORM_PTRCONTENTS,
		 mContent.c_str(),
		 CURLFORM_CONTENTTYPE,
		 mContentType.c_str(),
		 CURLFORM_END );
  }
}
