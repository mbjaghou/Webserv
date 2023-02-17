#include "parsing.hpp"



int main(int ac, char **av)
{
    pars pars;

    if (ac != 2)
    {
        std::cout << "Error\n";
        exit (1);
    }
    pars.open_file_read(av);
    std::vector<std::string>::iterator it = pars.config.begin();
    for (;it != pars.config.end(); ++it)
        std::cout << *it << std::endl;

}