#include "../parsing_hpp/parsing.hpp"



int main(int ac, char **av)
{
    try 
    {
        pars pars;
        pars.parsing(ac, av);

		int i = -1;
		while (++i < pars.parssing.size())
		{
			for (std::map<int, std::string>::iterator it = pars.parssing[i].get_error_page().begin(); it != pars.parssing[i].get_error_page().end(); it++)
				std::cout << "error_page: " << it->first << " " << it->second << std::endl;
			std::cout << "size of servers: " << pars.parssing.size() << std::endl;
			std::cout << "root: " << pars.parssing[i].get_root() << std::endl;
			std::cout << "port: " << pars.parssing[i].get_port() << std::endl;
			std::cout << "address: " << pars.parssing[i].get_address() << std::endl;
			std::cout << "max_client_body_size: " << pars.parssing[i].get_max_client_body_size() << std::endl;
			std::cout << "autoindex: " << pars.parssing[i].get_autoindex() << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_server_name().begin(); it != pars.parssing[i].get_server_name().end(); it++)
				std::cout << "server_name: " << *it << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_index().begin(); it != pars.parssing[i].get_index().end(); it++)
				std::cout << "index: " << *it << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_allowed_methods().begin(); it != pars.parssing[i].get_allowed_methods().end(); it++)
				std::cout << "allowed_methods: " << *it << std::endl;
		}
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

}