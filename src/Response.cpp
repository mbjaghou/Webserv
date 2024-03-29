/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:16:38 by ylabtaim          #+#    #+#             */
/*   Updated: 2023/03/27 21:42:44 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../headers/http/Response.hpp"

Response::Response(Request req) {
	_Headers = req.getHeaders();
	_Headers["Date"] = getDate();
	_Status = req.getStatus();
	_ErrorPage = req.getErrorPage();
	_Index = req.getIndex();
	_AutoIndex = req.getAutoIndex();
	_Body = req.getBody();
	_Cookie = _Headers["Cookie"];
	_Method = req.GetMethod();
}

std::string const & Response::GetCookie() {
	return _Cookie;
}

Response::~Response() {}

std::string Response::deleteFile(std::string const & path) {
	std::ostringstream	headers;
	std::fstream file(path);

	if (file.is_open())
		file.close();
	int status = std::remove(path.c_str());
	if (status != 0)
		_Status = Forbidden;
	else
		_Status	= NoContent;

	headers << "HTTP/1.1 " << _Status << " " << ReasonPhrase(_Status) << "\r\n"
	<< "Date: " << _Headers["Date"] << "\r\n"
	<< "Content-Type: text/plain\r\nContent-Length: 0\r\n"
	<< "Connection: " << _Headers["Connection"] << "\r\n"
	<< "\r\n";

	return headers.str();
}

std::string Response::uploadFile(pars &pars, const std::string &path) {
	std::string 	body;
	std::string		filename;
	std::string		boundary;
	std::string		content;
	std::string		upload_path;
	size_t			pos;
	size_t			delpos;
	size_t			endpos;

	for (size_t i = 0; i < pars.locations_upload.size(); ++i) {
		if (pars.locations_upload[i].location_path == path)
			upload_path = pars.locations_upload[i].upload_store;
	}
	if (upload_path[upload_path.size() - 1] != '/')
		upload_path.append("/");

	pos = _Headers["Content-Type"].find("boundary");
	if (pos == std::string::npos)
		return sendErrorPage(BadRequest);
	boundary = _Headers["Content-Type"].substr(pos + 9, _Headers["Content-Type"].size() - pos - 9);
	for (size_t i = 0; i < _Body.size(); ++i) {
		body.append(_Body[i]);
	}

	delpos = body.find(boundary);
	while (delpos != std::string::npos) {
		std::ofstream	file;
		pos = body.find("filename", delpos);
		endpos = body.find("\"", pos + 10);
		if (pos == std::string::npos || endpos == std::string::npos)
			return sendErrorPage(BadRequest);
		filename = body.substr(pos + 10, endpos - pos - 10);
		if (pathIsFile(upload_path + filename) == 1)
			return sendErrorPage(BadRequest);

		pos = body.find("\r\n\r\n", delpos);
		endpos = body.find(boundary, pos);
		if (pos == std::string::npos || endpos == std::string::npos)
			return sendErrorPage(BadRequest);
		content = body.substr(pos + 4, endpos - pos - 6);

		file.open(upload_path + filename);
		if (!file.is_open())
			return sendErrorPage(BadRequest);
		file << content;
		delpos = body.find(boundary, delpos + 1);
		if (body[delpos + boundary.size()] == '-' && body[delpos + boundary.size() + 1] == '-')
			break;
	}

	std::ostringstream	headers;
	std::string success = "<html>\r\n<head><title>Success</title></head>\r\n<body>\r\n<center><h1>";
	success.append("Files uploaded successfully");
	success.append("</h1></center>\r\n</body>\r\n</html>");

	headers << "HTTP/1.1 200 OK\r\n"
	<< "Date: " << _Headers["Date"] << "\r\n"
	<< "Content-Type: " << "text/html\r\n"
	<< "Content-Length: " << success.size() << "\r\n"
	<< "Connection: close\r\n\r\n";

	return (headers.str() + success);
}
std::string Response::getEnv(Request const &obj)
{
	std::string env;
    env.append("SERVER_SOFTWARE=webserv\n");
    env.append("SERVER_NAME=localhost\n");
    env.append("GATEWAY_INTERFACE=CGI/1.1\n");
    env.append("SERVER_PROTOCOL=HTTP/1.1\n");
    env.append("SERVER_PORT=");env.append(obj.getPort());env.append("\n");
    env.append("REQUEST_METHOD=");env.append(obj.GetMethod());env.append("\n");
	env.append("QUERY_STRING=");env.append(obj.GetQuery());env.append("\n");
	env.append("PATH_INFO=");env.append(obj.getLocation()->cgi_path);env.append("\n");
	env.append("SCRIPT_FILENAME=");env.append(obj.getLocation()->cgi_script);env.append("\n");
    env.append("DOCUMENT_ROOT=");env.append(obj.getLocation()->root);env.append("\n");
	env.append("REDIRECT_STATUS=");env += obj.getLocation()->return_page.first;env.append("\n");
	if(obj.getHeaders().find("Cookie") != obj.getHeaders().end())
		env.append("HTTP_COOKIE=");env.append(obj.getHeaders().find("Cookie")->second);env.append("\n");
   	if (obj.GetMethod() == "POST") {
		for(std::vector<std::string>::const_iterator it = obj.getBody().begin(); it != obj.getBody().end(); ++it)
		{
			std::string str = *it;
			int count = 0;
			for(size_t i = 0; i < str.size(); i++)
			{
				if (str[i] == '&')
					count++;
			}
			while(count >= 0)
			{
				std::string key = str.substr(0, str.find("="));
				std::string value = str.substr(str.find("=") + 1, str.find("&") - str.find("=") - 1);
				env.append(key);env.append("=");env.append(value);env.append("\n");
				str = str.substr(str.find("&") + 1, str.size() - str.find("&") - 1);
				count--;
			}
		}
	}
	env.append("");
	return env;
}

#include <signal.h>
void handle_alarm(int sig) {
	(void)sig;
    exit(EXIT_FAILURE);
}
void free_env(char **env) {
	for (size_t i = 0; env[i]; ++i)
		delete[] env[i];
	delete[] env;
}
std::string Response::cgi(Request const &obj){
	chdir(obj.getPath().c_str());
    std::vector<std::string> envp = ft_split(getEnv(obj), "\n");
    char **env = new char*[envp.size() + 1];
    for (size_t i = 0; i < envp.size(); ++i) {
        env[i] = new char[envp[i].size() + 1];
        strcpy(env[i], envp[i].c_str());
    }
    env[envp.size()] = NULL;
    std::string cgi_path = obj.getLocation()->cgi_path;
    std::string cgi_script = obj.getLocation()->cgi_script;
    if(access(cgi_script.c_str(), X_OK) == -1)
	{
		free_env(env);
        return sendErrorPage(Forbidden);
	}
	if(access(cgi_path.c_str(), F_OK) == -1)
	{
		free_env(env);
		return sendErrorPage(NotFound);
	}
    char* argv[] = {const_cast<char*>(cgi_path.c_str()), const_cast<char *>(cgi_script.c_str()), NULL};
	int pipefd[2];
    std::ostringstream	headers;
	headers << "HTTP/1.1 200 OK\r\n";
    if(pipe(pipefd) == -1)
	{
		free_env(env);
        return sendErrorPage(InternalServerError);
	}
    pid_t pid = fork();
	if (pid < 0)
	{
		free_env(env);
		return sendErrorPage(InternalServerError);
	}
    else if(pid == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
		    struct sigaction sa;
		sa.sa_handler = handle_alarm;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(2);
		
        execve(argv[0], argv, env);
		free_env(env);
        return sendErrorPage(InternalServerError);
    }
    else
    {
		free_env(env);
        close(pipefd[1]);
        std::string cgi_output;
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            cgi_output.append(buffer, bytes_read);
        }
        close(pipefd[0]);
		if(cgi_output.find("\r\n\r\n") != std::string::npos)
		{
			headers << cgi_output.substr(0, cgi_output.find("\r\n\r\n") + 2);
			cgi_output = cgi_output.substr(cgi_output.find("\r\n\r\n") + 4, cgi_output.size() - cgi_output.find("\r\n\r\n") - 4);
		}
        int status;
        if(waitpid(pid, &status, 0) == -1)
			return sendErrorPage(InternalServerError);
		
        if (WIFEXITED(status)) {
			if(WEXITSTATUS(status) != 0)
				return sendErrorPage(InternalServerError);
            
            headers << "Date: " << _Headers["Date"] << "\r\n"
            << "Content-Length: " << cgi_output.size() << "\r\n"
            << "Connection: close\r\n\r\n";
            return (headers.str() + cgi_output);
        }
        else
            return sendErrorPage(LoopDetected);
    }
    return "";
}

std::string Response::sendHeaders(const std::string &filename) {
	std::ifstream file(filename);
	std::ostringstream headers;

	std::size_t i = filename.find_last_of(".");
	std::string ext = (i != std::string::npos) ? filename.substr(i + 1) : "";

	if (ext != "") {
		std::string type = getMediaType(ext);
		_Headers["Content-Type"] = type.empty() ? "text/plain" : type;
	} else {
		_Headers["Content-Type"] = "text/plain";
	}
	std::string cc;
	cc.append("Set-Cookie: " + _Cookie + "\r\n");
	headers << "HTTP/1.1 " << _Status << " " << ReasonPhrase(_Status) << "\r\n"
		<< "Date: " << _Headers["Date"] << "\r\n"
		<< "Content-Type: " << _Headers["Content-Type"] << "\r\n"
		<< "Content-Length: " << getFileLength(filename) << "\r\n"
		<< "Connection: " << _Headers["Connection"] << "\r\n";
		if (_Cookie.compare("") != 0)
			headers << cc;
		headers << "\r\n";
	return headers.str();
}

std::string Response::sendErrorPage(int status) {
	std::stringstream ss;
	std::string strStatus;

	ss << status;
	ss >> strStatus;

	if (_ErrorPage[_Status] != "" && pathIsFile(_ErrorPage[_Status]) == 1) 
		return sendFile(_ErrorPage[_Status]);
	else {
		std::string error = "<html>\r\n<head><title>Error</title></head>\r\n<body>\r\n<center><h1>";
		error.append(strStatus + "\t" + ReasonPhrase(status));
		error.append("</h1></center>\r\n</body>\r\n</html>");

		std::ostringstream headers;

		headers << "HTTP/1.1 " << _Status << " " << ReasonPhrase(_Status) << "\r\n"
		<< "Date: " << _Headers["Date"] << "\r\n"
		<< "Content-Type: " << "text/html\r\n"
		<< "Content-Length: " << error.size() << "\r\n"
		<< "Connection: " << "close\r\n";
		if (_Headers.find("Location") != _Headers.end())
			headers << "Location: " << _Headers["Location"] << "\r\n";
		headers << "\r\n";

		return (headers.str() + error);
	}
}

std::string Response::sendFile(const std::string &filename) {
	std::ifstream file(filename);
	std::stringstream ss;
	std::string response;

	response = sendHeaders(filename);
	ss << file.rdbuf();
	response += ss.str();
	return response;
}


std::string Response::sendDir(const char *path, const std::string &host) {
	if (_Index != "") {
		int fd = open(_Index.c_str(), O_RDWR);
		if (fd == -1) {
			return sendErrorPage(Forbidden);
		} else {
			close (fd);
			return sendFile(_Index);
		}
	}
	if (_AutoIndex == false)
		return sendErrorPage(Forbidden);
	std::ostringstream headers;
	std::string dirName(path);
	struct dirent *dirEntry;
    DIR *dir = opendir(path);
    std::string page = "<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title>" + dirName + "</title>\r\n\
	</head>\r\n<body>\r\n<h1>Webserv</h1>\r\n<p>\r\n";
    while ((dirEntry = readdir(dir)) != NULL)
		page += getLink(std::string(dirEntry->d_name), dirName, host);
    page += "</p>\r\n</body>\r\n</html>\r\n";
	closedir(dir);
	headers << "HTTP/1.1 " << _Status << " " << ReasonPhrase(_Status) << "\r\n"
		<< "Date: " << _Headers["Date"] << "\r\n"
		<< "Content-Type: " << "text/html\r\n"
		<< "Content-Length: " << page.size() << "\r\n"
		<< "Connection: " << _Headers["Connection"] << "\r\n"
		<< "\r\n";
	return (headers.str() + page);
}

std::string Response::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host) {
    std::stringstream	ss;

	std::string dir;
	if (dirName[dirName.length() - 1] != '/')
		dir = dirName + "/" + dirEntry;
	else
        dir = dirName + dirEntry;
	if (pathIsFile(dir) == 1)
		ss << "<p> <a style=\"color:black;text-decoration:none\"";
	else if (!pathIsFile(dir))
		ss << "<p> <a style=\"color:red;\"";
	ss <<" href=\"http://" + host << dir + "\">" + dirEntry + "</a></p>\r\n";
	return ss.str();
}

const int &Response::getStatus() const {
	return _Status;
}
