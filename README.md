# GDML
## the best and only gd mod library for mac

GDML lets you create and enable/disable any sort of mod possible, from hooks to just writing some memory. Heres an example: 

    #include "GDML.hpp"
    #include <iostream>

    ModContainer* container;
    void* onUndo(void* a, void* b) {
        void* ret = FCAST(test, container->getOriginal(getBase()+0xb830))(a, b);
        std::cout<< "called the undo" << std::endl;
        return ret;
    }
    void inject() {


        container = new ModContainer("P");


        container->registerHook(getBase()+0xb830, (func_t)onUndo);


        container->enable();
    }
it technically could be used for any program but i made it with gd in mind

### credit for a lot of the low-level code goes to Dmitry Rodionov at [rd_route](https://github.com/rodionovd/rd_route)
