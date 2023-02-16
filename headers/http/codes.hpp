/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:37:54 by ylabtaim          #+#    #+#             */
/*   Updated: 2023/02/16 19:07:38 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define RUNNING 1
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <map>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <set>
#include <fstream>
#include <fcntl.h>
#include <ctime>
#include <string>
// #include "./../parsing/ServerContext.hpp"
// #include "./../parsing/ConfigFileParser.hpp"

enum Code
{
	Continue           				= 100,
	SwitchingProtocols 				= 101,
	Processing         				= 102,
	EarlyHints         				= 103,

	OK                         		= 200,
	Created                    		= 201,
	Accepted                   		= 202,
	NonAuthoritativeInformation		= 203,
	NoContent                  		= 204,
	ResetContent               		= 205,
	PartialContent             		= 206,
	MultiStatus                		= 207,
	AlreadyReported            		= 208,
	IMUsed                     		= 226,

	MultipleChoices   				= 300,
	MovedPermanently  				= 301,
	Found             				= 302,
	SeeOther          				= 303,
	NotModified       				= 304,
	UseProxy          				= 305,
	TemporaryRedirect 				= 307,
	PermanentRedirect 				= 308,

	BadRequest                  	= 400,
	Unauthorized                	= 401,
	PaymentRequired             	= 402,
	Forbidden                   	= 403,
	NotFound                    	= 404,
	MethodNotAllowed            	= 405,
	NotAcceptable               	= 406,
	ProxyAuthenticationRequired 	= 407,
	RequestTimeout              	= 408,
	Conflict                    	= 409,
	Gone                        	= 410,
	LengthRequired              	= 411,
	PreconditionFailed          	= 412,
	PayloadTooLarge             	= 413,
	URITooLong                  	= 414,
	UnsupportedMediaType        	= 415,
	RangeNotSatisfiable         	= 416,
	ExpectationFailed           	= 417,
	ImATeapot                   	= 418,
	UnprocessableEntity         	= 422,
	Locked                      	= 423,
	FailedDependency            	= 424,
	UpgradeRequired             	= 426,
	PreconditionRequired        	= 428,
	TooManyRequests             	= 429,
	RequestHeaderFieldsTooLarge 	= 431,
	UnavailableForLegalReasons  	= 451,

	InternalServerError          	= 500,
	NotImplemented               	= 501,
	BadGateway                   	= 502,
	ServiceUnavailable           	= 503,
	GatewayTimeout               	= 504,
	HTTPVersionNotSupported      	= 505,
	VariantAlsoNegotiates        	= 506,
	InsufficientStorage          	= 507,
	LoopDetected                 	= 508,
	NotExtended                  	= 510,
	NetworkAuthenticationRequired	= 511
};
