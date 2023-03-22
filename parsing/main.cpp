#include "../parsing_hpp/parsing.hpp"

int main(int ac, char **av)
{
    try 
    {
        pars pars;
        pars.parsing(ac, av);

		std::cout << "size of servers: " << pars.parssing.size() << std::endl;
		int i = -1;
		while (++i < pars.parssing.size())
		{
			for (std::map<std::string, long>::iterator it = pars.parssing[i].listen.begin(); it != pars.parssing[i].listen.end(); it++)
				std::cout << "listen: " << it->first << " " << it->second << std::endl;
			for (std::map<int, std::string>::iterator it = pars.parssing[i].error_page.begin(); it != pars.parssing[i].error_page.end(); it++)
				std::cout << "error_page: " << it->first << " " << it->second << std::endl;
			std::cout << "root: " << pars.parssing[i].get_root() << std::endl;
			std::cout << "max_client_body_size: " << pars.parssing[i].get_max_client_body_size() << std::endl;
			std::cout << "autoindex: " << pars.parssing[i].get_autoindex() << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_server_name().begin(); it != pars.parssing[i].get_server_name().end(); it++)
				std::cout << "server_name: " << *it << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_index().begin(); it != pars.parssing[i].get_index().end(); it++)
				std::cout << "index: " << *it << std::endl;
			for (std::vector<std::string>::iterator it = pars.parssing[i].get_allowed_methods().begin(); it != pars.parssing[i].get_allowed_methods().end(); it++)
				std::cout << "allowed_methods: " << *it << std::endl;
			int j = -1;
			std::cout << "\033[32m" << "start location" << "\033[0m" << std::endl;
			while (++j < pars.parssing[i].location.size())
			{
				std::cout << "location uploade: " << pars.parssing[i].location[j].get_uploade_path() << std::endl;
				std::cout << "location root: " << pars.parssing[i].location[j].get_root() << std::endl;
				for (std::vector<std::string>::iterator it = pars.parssing[i].location[j].index.begin(); it != pars.parssing[i].location[j].index.end(); it++)
					std::cout << "location index: " << *it << std::endl;
				for (std::map<int, std::string>::iterator it = pars.parssing[i].location[j].error_page.begin(); it != pars.parssing[i].location[j].error_page.end(); it++)
					std::cout << "location error_page: " << it->first << " " << it->second << std::endl;
				std::cout << "location return: " << pars.parssing[i].location[j].return_page.first <<  " " <<  pars.parssing[i].location[j].return_page.second <<std::endl;

				for(std::vector<std::string>::iterator it = pars.parssing[i].location[j].allowed_methods.begin(); it != pars.parssing[i].location[j].allowed_methods.end(); it++)
					std::cout << "location allowed_methods: " << *it << std::endl;
				std::cout << "location autoindex: " << pars.parssing[i].location[j].autoindex << std::endl;
				std::cout << "location max_client_body_size: " << pars.parssing[i].location[j].max_client_body_size << std::endl;
				std::cout << "location cgi_extension : " << pars.parssing[i].location[j].cgi_extension << std::endl;
				std::cout << "location cgi_path : " << pars.parssing[i].location[j].cgi_path << std::endl;
				std::cout << "location cgi_script : " << pars.parssing[i].location[j].cgi_script << std::endl;
			}
			
		}
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

}