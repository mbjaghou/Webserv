#include "parsing.hpp"



int main(int ac, char **av)
{
    try 
    {
        pars pars;

        if (ac != 2)
            throw std::invalid_argument("Error whit the argment");
        pars.open_file_read(av);

		int i = 0;
		while (i < pars.count_server)
		{
			std::cout << pars.parssing[i].port[1] << std::endl;
			std::cout << pars.parssing[i].server_name[1] << std::endl;
			std::cout << pars.parssing[i].root[1] << std::endl;
			std::cout << pars.parssing[i].index[1] << std::endl;
			std::cout << pars.parssing[i].error_page[1] << std::endl;

			i++;
		}
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