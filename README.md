OrPSF
=====

SFTP 上传下载的小工具
(windows与linux间文件传送)  

## 项目说明

需要在 windows 和 linux 中进行文件传送。  
使用winscp软件完全没有问题，但如果只偶尔上传下载些文件，  
又不想安装大体积软件的话，本工具就比较适合。 
下载后无需安装可直接使用(请参见使用说明)。  
  
软件运行在windows端，通讯使用SFTP协议，  
linux中开启ssh即可。  

注：SFTP通讯使用 **psftp** 模块，熟悉命令行的朋友可直接使用psftp.exe。  
　　参见: http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html

## 使用说明

bin文件夹下为release后的程序，直接双击OrPSF.exe使用。  
若自行编译，请将psftp.dat与编译生成的.exe放在同一文件夹下。  


## 写给自己

* 为实现最大兼容性，使用MFC编写。  
* 目前借用psftp.exe实现SFTP协议，后序可考虑自己实现。  

  
