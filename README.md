# stm32
stm32 开发环境和工程
这是在Linux下的stm32开发环境。当然你还要安装arm-none-gcc系列工具。
如果想从头开始搭建或者想熟悉这个开发环境，强烈建议阅读这里唯一的PDF文件：
HowTo_ToolChain_STM32_Ubuntu.pdf
至于下载工具，可以参考博客：
[Ubuntu环境下使用stlink调试和下载stm32f4-discovery程序]
http://blog.csdn.net/xiaofeng1234/article/details/38083211
该博客提到的下载工具：我只安装成功了第一个版本，版本二安装不上。我的开发环境是
Ubuntu16.04。
文件和文件夹说明：
inc:头文件，这里的头文件来自于一个开发板，我的工程中没有用到。忽略。
libs:官方库和头文件
other:和inc中的头文件一样，来自于一个开发板，其他代码，忽略就好。
src:这个文件夹下的文件夹请忽略，而文件是工程文件和Makefile。
README.md：本文件
Makefile,Makefile.common:Makefile
