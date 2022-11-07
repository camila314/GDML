//
//  GDML.hpp
//  GDML
//
//  Created by Full Name on 7/17/20.
//  Copyright © 2020 camila314. All rights reserved.
//
#include <vector>
#include <string>

using namespace std;

#ifndef GDML_
#define GDML_

#define FCAST(a, b) reinterpret_cast<decltype(&a)>(b)
typedef void(*func_t)();
/* The classes below are exported */
#pragma GCC visibility push(default)

struct OriginalNotFoundException : public exception
{
  const char * what () const throw ()
  {
    return "Cannot find the original address of this function";
  }
};

struct ModNotFoundException : public exception
{
  const char * what () const throw ()
  {
    return "Cannot find the mod container given the name";
  }
};

class BaseContainer {
protected:
    long address;
    size_t byteCount;
    char* originalBytes;
    char* moddedBytes;
    
public:
    virtual ~BaseContainer();
    void enable();
    void disable();
    friend class ModContainer;
};

class MemoryContainer : public BaseContainer{
public:
    MemoryContainer(long address, size_t byteCount, char* bytes);
    ~MemoryContainer();
};

class HookContainer : public BaseContainer {
public:
    HookContainer(long address, func_t function);
    func_t getOriginal();
    ~HookContainer();
private:
    func_t original;
    
    
};

class ModContainer
{
public:
    static vector<ModContainer*> containers;
    template <typename S>
    static ModContainer* containerByName(S name) {
        for(ModContainer* i : ModContainer::containers) {
            std::string cmp(i->containerName);
            if(cmp==name) {
                return i;
            }
        }
        throw ModNotFoundException();
    }
    ModContainer(char const* name);
    ~ModContainer();
    void enable();
    void disable();
    void registerWrite(long address, size_t byteCount, char* bytes);

    template <typename F>
    F registerHook(long address, F function);
    func_t getOriginal(long address);
    char const* getName();
private:
    vector<BaseContainer*> mods;
    char const* containerName;
};

long getBase();

void inject(void) __attribute__((constructor));
#pragma GCC visibility pop
#endif
