#include "parsing.hpp"



int main(int ac, char **av)
{
    try 
    {
        pars pars;

        if (ac != 2)
            throw std::invalid_argument("Error whit the argment");
        pars.open_file_read(av);


        // std::vector<std::string>::iterator it = pars.listen.begin();
        // for (;it != pars.listen.end(); ++it)
        //     std::cout << *it << std::endl;
        //std::cout << pars.listen[1] << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

}