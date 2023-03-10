/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:16:39 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 17:18:26 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LOCATION_HPP
#define PARSE_LOCATION_HPP

#include <iostream>

class location
{
    private:
        std::string root;
    public:
        std::string get_root(void);
    
};

#endif