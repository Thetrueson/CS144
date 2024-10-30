# CS144
CS144_lab反馈
因为看过一个帖子说往后的cs144lab难度有所降低，所以在网上找了前几年的来练手，锻炼自己的代码能力和加强对于网络的理解【这里是后期，因为过去lab文件的丢失，所以大部分还是参照的fall2023进行qwq】

# Lab 0
1.环境搭建：
  安装VMware pro 在官网下载Ubantu 18.04（因为lab中有提到这个版本）【这里是后期，建议23.10版本，具体原因见后qwq】
  如果有不懂的地方可以在b站上通过视频一步步下载
  然后进入ubantu后
  
      执行命令：
      apt-get install g++ git clang-tidy clang-format libpcap-dev iptables mininet tcpdump telnet wireshark socat netcat-openbsd doxygen graphviz
        
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

3_1.构建启动代码：
    这里我遇到了点小问题，第一个是lab给出的sponge文件没有的qwq，所以我去参照了fall2024的step，这里又有点小插曲
    因为要用到cmake进行构建，所以我安装了cmake，但是可能是由于ubantu版本太低的原因，导致cmake版本不够lab要求
    所以我又去重装了23.10版的ubantu，然后把前面的步骤再做一遍就可以继续做lab了~
    这里跟着step操作即可没有特别要注意的东西

3_2.c++风格：
    这里就是强调一些编码要点，还有一些注意事项

3_3.阅读文档：
    这里因为我找不到文档，所以就没看，我直接啃的源码，很难受qwq

3_4.编写webget
    这里需要知道封装库中有哪些函数可以使用，然后结合前面做的几个小step来实现代码，总体来说思路不难，难的是不知道要调用什么函数，需要看源码，了解清楚类的关系和具体的函数

      TCPSocket client_socket;
      Address server_address(host,"http");
      client_socket.connect(server_address);
      cout << "Connected to server" << endl;
      string request = "GET "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: Close\r\n\r\n";
      client_socket.write(request);
      client_socket.shutdown(SHUT_WR);
      cout << "Request sent" << endl;
      string response;
      cout << "Response received: " << endl;
      while(!client_socket.eof()){
    	client_socket.read(response);
    	cout << response;
      }
      client_socket.close();

    这是我代码的主要逻辑，这里request就用到了我们前面step中学到的知识
    我运行代码是可以得到结果的，但是test过不去不知道为什么，但是我看其他博主的代码好像差不多就也没去多管了【好吧，后面知道用错测试程序了qwq，代码成功通过了】

      这是我的测试结果：
        Connected to server
        Request sent
        Response received: 
        HTTP/1.1 200 OK
        Date: Wed, 16 Oct 2024 13:00:54 GMT
        Server: Apache
        Last-Modified: Thu, 13 Dec 2018 15:45:29 GMT
        ETag: "e-57ce93446cb64"
        Accept-Ranges: bytes
        Content-Length: 14
        Connection: close
        Content-Type: text/plain
        
        Hello, CS144!

4.可靠字节流传输：
  这个需要我们实现一个基于内存的通信管道，我的想法是利用队列（一边存一边取嘛）
  这里要注意的是他是字节流，所以他的capacity是值存储的字节，但是我们的queue可以是string类型，这里就需要我们注意类型转换了（突然莫名想念python qwq）
  函数的定义都已给出，需要自己在定义几个类型变量，这个每个人可以有自己的看法，我定义了一个queue，两个数值类型来记录总数和存的数量。
  然后就可以在.cc文件中写出自己的实现（这是主体）总体难度不大，但要注意一些细枝末节，比如queue是否为空，在某些函数下会报错，需要自己进行一定的判断。
  因为代码过长，我直接上传了，有需要的可以自取并自行查看。（lab0->minnow->src->byte_stream.__）

    这里有个超级坑的点，lab给的minnow文件中有隐藏的.git文件，导致我的如果上传整个文件夹的话会在github上失效
    所以我只能上传lab0_4的代码，不过也无伤大雅，其他代码在我的笔记中也有

————————————————————Lab0结束——————————————————


# Lab1
我要吐槽一下，从这里开始感觉lab纯靠面向测试编程，lab文档写的非常模糊，但是你仔细想又在情理之中qwq
这次的lab是要实现一个接收端的重组器，要实现两个函数，一个插入函数，一个返回缓存几个字节的函数，这里面以为文档说的不够详细，所以我也踩了很多坑（也可能是自己太菜了hhh）

    这里记录一个雷点，在运行lab0 lab1的test时，时不时通过，或者一连串AddressSanitizer：DEADLYSIGNAL
    解决方案：
      禁止Linux地址空间布局随机化 ASLR
      echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
      具体原因：菜鸟的我就不知道了，只是提供一种解决方案，希望能够有帮助。
      注意，每次重启虚拟机都需要执行一次，经验之谈，也不懂为啥hhh


    insert函数：
      有三个参数，index，data和is_last，这里的index是指字节的序号，并不是data这个子字符串的序号，index是可能会重复的，而且重复的子字符串的内容可能不同
      有可能是错误的内容，也有可能是重复的内容，对于错误的内容（这里认为是已经输入的字符序列号）也就是后到的已输入内容，可以不处理，直接跳过，
      但是这个子字符串可能还存在有用的数据，需要自己判断，data和lab0中的data类似，
      但是注意，这里的capacity依然是字节，所以index指的是data的第一个字节，对于已经输入且正确的字节这里也是可以直接跳过
      is_last这里我是定义了一个bool变量去记录，当重组器为空，且index为最后一个子字符串的最后一个字节时即可调用类中的output_的close函数进行关闭

    byte_pending函数：
      这里也有很多坑，首先这个返回值不能大于capacity，而且只要是有序的子字符串都不能认为是缓存（从0开始到最后一个有序子字符串），需要直接push到output_里面
      所以这个记录要从第一个无序段开始记录，这里记录的也是字节，所以你需要遍历每个可count的子字符串，而且不能只看不同的子字符串，
      你需要把他们相对有序的子字符串拼在一起去重（相邻），这里我用的set
      最大的返回值不能大于等于capacity，就相当于lab中给出图的红色部分

 ![image](https://github.com/user-attachments/assets/8dc39002-df11-4cf6-a38c-8091a0aa5b36)

    我们可以看到，byte_pending返回的是绿色部分，在容器里面但是不返回的是红色部分，已经push的是蓝色部分

老样子，代码我也上传了，写的比较潦草也比较匆忙请见谅，但是已经用过format和tidy了，已经通过check，希望能帮到你

————————————————————Lab1结束——————————————————


# Lab2
这个lab的难度比上一个低，但是lab说明书依旧很模糊，RST和未收到SYN就丢弃这些特性都是通过面向test编程得出的结果；
这个实验分两个部分，第一个是32位和64位互转的方法，这个是后面接收端实现的基础，第二个是接收端receive和send方法的实现；
具体的消息体结构和序号类别在lab中都有一定的说明，这里就不再赘述，下面我来说下要注意的点：

    wrap和unwrap：这里面要注意的就是checkpoint，这个数不是具体的数，也可能比转换后的数大或者小，所以这里的比较范围要稍微宽一点
                  在receive中的checkpoint可以给个大概，和ackno差不多就行，因为32位他可能会有几个轮次的交替，所以误差很小

    receive：这里面的一些信息全靠test去理解qwq，第一个seqno，这是个32位的数，以字节为单位，而且SYN和FIN都占一个单位
             SYN和FIN可能会同时出现也可能倒着出现，他们的payload可能会有可能没有，没有收到SYN之前，所有的消息全部丢弃
             reassembler发送的index是以字节为单位，所以要考虑有数据的时候seqno.unwrap（）-1
             window_size直接用UINT16_MAX和available_capability的最小值就行
             这里让我最难受的是ackno的记录，我刚开始并没有想到用之前实现过的类方法去解决这个问题
             我是用一个集合去记录出现过的数，然后再筛选，这样我再recorder_more这个测试集中超时了
             所以我在网上看一下大佬们的博客，发现可以直接用is_start+btyes_pushed+is_closed直接秒了
             我当初人都傻了，不过能学到东西就行qwq，还是得多考虑使用之前的东西

    send：这个没什么可说的，如果收到了SYN就封装上述的ackno，window_size直接一个式子就解决了
          这可能要注意的就是RST这个状态，如果有就直接置错然后返回，具体的做法我也是参考大佬的，因为这里说明书并没有给出
          //在receive中，RST_是一个bool类型
          if ( message.RST ) {
            reassembler_.reader().set_error();
            RST_ = reassembler_.reader().has_error();
            return;
          } else if ( RST_ ) {
            return;
          }
          //在send中
          message.RST = reassembler_.reader().has_error();


除了next这个问题，其他的部分我感觉还行，不是很难，一些细节部分需要自己把控好，代码已通过测试，我也已经发出来了（但是效率可能不是很高），供大家参考

————————————————————Lab2结束——————————————————

Lab3有点劝退qwq，有机会再更新吧

      
