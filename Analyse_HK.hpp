// Analyse.hpp

#ifndef ANALYSE_HPP
#define ANALYSE_HPP

#include <vector>
#include <string>
#include <iostream>
#include "verification_HK.hpp"
#include "userPrompt.hpp"


class Analyse_HK {
public:
    virtual void analyse();//fonction virtuelle qui peut être personnaliser dans les classes fille (polymorphisme); 
    virtual void display_menu() = 0;
    void countseq();
    void length(); 
    void show_headers(); 
    void show_sequences();
    void total_length();   
};
#endif // ANALYSE_HPP
