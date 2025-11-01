#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>



enum class OpType{
    INSERT, REMOVE, REPLACE
};

struct Operation{
    OpType type;

    std::size_t pos;
    std::string newValue;
    std::string oldValue;

    Operation(){
        this->oldValue = "oldValue";
        this->newValue = "newValue";
        this->pos = 0;
    };

    Operation(std::string oldValue, std::string newValue, std::size_t pos, OpType type){
        this->oldValue = oldValue;
        this->newValue = newValue;
        this->pos = pos;
        this->type = type;
    }


};






#endif // OPERATION_H
