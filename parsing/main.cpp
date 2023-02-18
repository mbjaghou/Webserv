#include "parsing.hpp"



int main(int ac, char **av)
{
    try 
    {
        pars pars;

        if (ac != 2)
            throw std::invalid_argument("Error whit the argment");
        pars.open_file_read(av);


        std::cout << pars.tmp1;
        // std::vector<std::string>::iterator it = pars.config.begin();
        // for (;it != pars.config.end(); ++it)
        //     std::cout << *it << std::endl;
        //std::cout << pars.listen[1] << std::endl;
        // std::cout << pars.index.size() << std::endl;
        // std::vector<std::string>::iterator it1 = pars.root.begin();
        // for (;it1 != pars.root.end(); ++it1)
        //     std::cout << *it1 << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

}