# CS144
CS144-fall2020 lab反馈
因为看过一个帖子说往后的cs144lab难度有所降低，所以在网上找了前几年的来练手，锻炼自己的代码能力和加强对于网络的理解

# Lab 0
1.环境搭建：
  安装VMWare pro 在官网下载Ubantu 18.04（因为lab中有提到这个版本）
  如果有不懂的地方可以在b站上通过视频一步步下载
  然后进入ubantu后执行命令：
    apt-get install g++ git clang-tidy clang-format libpcap-dev \
      iptables mininet tcpdump telnet wireshark socat \
      netcat-openbsd doxygen graphvizclang-format libpcap-dev \ 
      iptables mininet tcpdump telnet wireshark socat netcat-openbsd \ 
      doxygen graphviz
  安装lab所需的所需的所有环境就可以愉快的开始了
  这个step和lab上写的不一样，我也是参照了一些博主的做法，觉得这样会比lab中写的更加简单一些
  如果有自己的想法或者想按照lab一步一步来的也可以按自己想法来，反正殊途同归嘛

2_1.获取网页：
    通过浏览器输入 http://cs144.keithw.org/hello 来访问会得到一个结果（具体结果可以自行实验）
    这里比较简单，可以一步一步跟着lab走，很容易得到结果
    telnet cs144.keithw.org http（用telnet工具 跟上域名 最后是协议）
    GET /hello HTTP/1.1（请求方式 请求路径 协议）
    Host: cs144.keithw.org（请求域名）
    Connection: close
    再回车（敲完之后一定要再进行这个回车才会返回结果，告诉服务器本次连接结束返回结果）
    就可以得到网页一模一样的内容

    作业：
      比较简单，把请求路径更改成/lab0/~，波浪线处可以是任何字符，本人用的自己学号进行测试得出了结果
        HTTP/1.1 200 OK
        Date: Tue, 15 Oct 2024 08:03:57 GMT
        Server: Apache
        X-You-Said-Your-SunetID-Was: ~
        X-Your-Code-Is: ~
        Content-length: 111
        Vary: Accept-Encoding
        Connection: close
        Content-Type: text/plain
        
        Hello! You told us that your SUNet ID was "~". Please see the HTTP headers (above) for your secret code.
        Connection closed by foreign host.
      除了波浪线其他都是返回的结果，有需要的可以参考一下

2_2.发送电子邮件：
    这里因为没有stanford的id，我通过查找资料使用了网易163邮箱进行了实验
    ![image](https://github.com/user-attachments/assets/05fdff8d-ca72-470b-82fc-1e6aa5c9682a)








      
