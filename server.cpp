#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket创建失败" << std::endl;
        return -1;
    }

    // 设置socket选项
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt失败" << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 绑定socket到8080端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "绑定失败" << std::endl;
        return -1;
    }

    // 开始监听
    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "监听失败" << std::endl;
        return -1;
    }

    std::cout << "服务器正在8080端口监听..." << std::endl;
    std::cout << "按Ctrl+C停止服务器" << std::endl;

    // 持续接受连接
    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cerr << "接受连接失败" << std::endl;
            continue;
        }

        std::cout << "收到新连接" << std::endl;

        // 发送简单响应
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<html><head><meta charset='utf-8'></head><body><h1>8080端口已开启!</h1><p>服务器运行正常</p></body></html>";
        send(new_socket, response, strlen(response), 0);

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
