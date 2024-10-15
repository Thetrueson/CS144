# CS144
CS144-fall2020 lab反馈
因为看过一个帖子说往后的cs144lab难度有所降低，所以在网上找了前几年的来练手，锻炼自己的代码能力和加强对于网络的理解

# Lab 0
1.环境搭建：
  安装VMware pro 在官网下载Ubantu 18.04（因为lab中有提到这个版本）
  如果有不懂的地方可以在b站上通过视频一步步下载
  然后进入ubantu后
  
      执行命令：
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
    
      通过这里把smtp协议设置为许可状态
    
  ![image](https://github.com/user-attachments/assets/4e780c47-c224-4e08-810c-0c9c08dafe7a)
    
      这里会获得一个密钥，一定一定要保存，在后面有用！！！
    
    过程：
      telnet smtp.163.com smtp（域名是官方提供的，用来专为163邮箱使用的smtp服务器，lab中则是stanford的服务器）
      Trying 117.135.214.13...
      Connected to smtp163.mail.ntes53.netease.com.
      Escape character is '^]'.
      220 163.com Anti-spam GT for Coremail System (163com[20141201])
      HELO mycomputer.163.com（HELO后面的域名随意，用来标识自己的主机）
      250 OK
      AUTH LOGIN（登录命令）
      334 dXNlcm5hbWU6
      （输入163邮箱经过base64编码过后的形式）
      334 UGFzc3dvcmQ6
      （输入当初给的密钥经过base64编码过后的形式）
      235 Authentication successful（这里表示成功登录）
      MAIL FROM:<~>（163邮箱，发送方）
      250 Mail OK
      RCPT TO:<~>（163邮箱，接受方）
      250 Mail OK
      DATA（输入邮件的命令）
      354 End data with <CR><LF>.<CR><LF>
      【以下为邮箱内容】
      From:~
      To:~
      SUbject:TEst email via telnet
      （换行）
      hello cs144（正文）
      .（以单行.为结束符）
      250 Mail OK queued as gzga-smtp-mtada-g0-2,_____wBnVacbPw5nKdjHBA--.60317S5 1728987167
      QUIT
      221 Bye
      Connection closed by foreign host.

  作业的话和操作差不多只是改了个邮箱地址，这里就不演示了

2_3.监听和连接：
    这里不难，按照step一步一步来就能达到想要的结果
    但是从这个task我们可以得到一些结论：
    
      telnet是用来访问或者发送请求用来建立连接的
      netcat是用来等待请求的

    他们二者建立连接后可以互通消息
    






      
