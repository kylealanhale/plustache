/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */
#ifndef PLUSTACHE_CONTEXT_H
#define PLUSTACHE_CONTEXT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace Plustache {

class Context;

typedef std::map<std::string, std::string> Object;
typedef std::vector<Object> Collection;

class Context {
  public:
    Context ();
    ~Context ();
    int add(const std::string& key, const std::string& value);
    int add(const std::string& key, Collection& c);
    int add(const std::string& key, const Object& o);
    int add(const Object& o);
    Collection get(const std::string& key) const;

  private:
    /* data */
    std::map<std::string, Collection> ctx;
};

} // namespace Plustache
#endif
