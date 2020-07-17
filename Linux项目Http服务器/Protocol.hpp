#pragma once

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>

class HttpRequest{
    private:
        std::string request_line;
        std::string request_header;
        std::string blank;
        std::string request_text;
    private:
        std::string method;
        std::string url;
        std::string version;

        std::unordered_map<std::string, std::string> header_kv;
    public:
        HttpRequest():blank("\n"){
        }
        void SetRequestLine(std::string &line){
            request_line = line;
        }
        void SetRequestHeader(std::string &header){
            request_header = header;
        }
        //GET /index.html HTTP/1.0\n 
        void RequestLineParse()
        {
            std::stringstream ss(request_line);
            ss >> method >> url >> version;
            std::cout << "Method: " << method << std::endl;
            std::cout << "url: " << url << std::endl;
            std::cout << "version: " << version << std::endl;
        }
        void RequestHeaderParse(){
            std::size_t pos = request_header.find('\n');
            int start = 0;
            while(pos != std::string::npos){
                string sub = str.substr(start, pos-start); //abcd\n
                //sub -> kv
                Util::MakeKV(header_kv, sub); //Content-Length: 30
                start = pos + 1;
                pos = str.find('\n', pos+1);
            }
        }
        bool IsMethodOk(){
            //Get, get, GeT, GeT
            if(strcasecmp(method.c_str(), "GET") == 0 || strcasecmp(method.c_str(), "POST") == 0){
                return true;
            }
            return false;
        }
        bool IsGet(){
            return strcasecmp(method.c_str(), "GET") == 0;
        }
        ~HttpReqeust(){
        }
};

class HttpResponse{
    private:
        std::string status_line;
        std::string response_header;
        std::string blank;
        std::string response_text;
};

class Connect{
    private:
        int sock;
    public:
        Connect(int _sock):sock(_sock){}

        //1. \r
        //2. \r\n
        //3. \n
        //   \r&\n&\r\n -> \n
        //4. read one char
        int RecvLine(std::string &line)
        {
            char c = 'X';
            while(c != '\n'){
                ssize_t s = recv(sock, &c, 1, 0);
                if(s > 0){
                    if(c == '\r'){
                        recv(sock, &c, 1, MSG_PEEK); //窥探
                        if(c == '\n'){
                            recv(sock, &c, 1, 0);
                        }
                        else{//?
                            c = '\n';
                        }
                    }
                    //normal char, \n, \r\n -> \n, \r -> \n
                    line.push_back(c);
                }
                else{
                    LOG(Warning, "recv request error!");
                    break;
                }
            }
            return line.size();
        }
        void RecvHttpRequestLine(std::string &request_line)
        {
            RecvLine(request_line);
        }
        void RecvHttpRequestHeader(std::string &request_header)
        {
            std::string line = "";
            do{
                line = "";
                RecvLine(line);
                if(line != "\n"){
                    request_header += line;
                }
            }while(line != "\n");
        }
        //读取http请求的请求行，请求报头，包括空行
        void RecvHttpRequest(HttpRequest *rq)
        {
            std::string request_line;
            std::string request_header;
            RecvHttpRequestLine(request_line);
            RecvHttpRequestHeader(request_header);

            rq->SetRequestLine(request_line);
            rq->SetRequestHeader(request_header);
        }

        ~Connect()
        {}
};


class Entry{
    public:
        static void *HandlerRequest(void *args){
            int sock = (int)args;

            Connect *conn = new Connect(sock);
            HttpRequest *rq = new HttpRequest();
            HttpResponse *rsp = new HttpResponse();

            conn->RecvHttpRequest(rq);
            rq->RequestLineParse();

            //Method is Ok? GET, POST
            if(!rq->IsMethodOk()){
                LOG(Warning, "request Method is not ok!");
                //TODO
            }
            //分析url: path, paramter
            rq->RequestHeaderParse();
            //url: 域名/资源文件?x=XX&&y=YY
            if(rq->IsGet()){
                //url -> 
            }
            else{
                //post
                //
            }


            //recv request
            //parse request
            //make response
            //send response
            delete conn;
            delete rq;
            delete rsp;
        }
};
