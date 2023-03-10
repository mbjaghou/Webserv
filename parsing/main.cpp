#include "parsing.hpp"



int main(int ac, char **av)
{
    try 
    {
        pars pars;
        pars.parsing(ac, av);


		// int i = 0;
		// while (i < pars.count_server)
		// {
		// 	std::cout << pars.parssing[i].port[0] << std::endl;
		// 	std::cout << pars.parssing[i].server_name[0] << std::endl;
		// 	std::cout << pars.parssing[i].root[0] << std::endl;
		// 	std::cout << pars.parssing[i].index[0] << std::endl;
		// 	std::cout << pars.parssing[i].error_page[0] << std::endl;

		// 	i++;
		// }
		// std::cout << pars.conf_file << std::endl;
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