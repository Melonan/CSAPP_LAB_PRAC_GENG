# CSAPPLAB_NOTE

- Enviroment: Docker from [Docker and Problems set](https://github.com/Maecenas/ICS-15213-CSAPP3e-CMU)
`docker run -p 15213:22 --name csapplab -v "`pwd`"/labs:/usr/src/app/ -itd lx70716/cmu-15213`
- -p mapping host's 15213 port to docker's 22 port which is the ssh login port, hence i could login docker from my laptop through access th    e cloud server-
- v mount the local directory called /labs to the dockers path: /usr/src/app/
- i it：这个选项是-i和-t的组合13。-i表示以交互模式运行容器，即保持标准输入（stdin）打开13。-t表示为容器分配一个伪终端（pseudo-tty）13。这样
可以让你在容器中执行命令，就像在本地终端一样。
- d d daemon 守护进程, docker 后台运行
--------
但是仍然无法ssh远程登陆，
安装 'net-tools'
`netstat -nltp`发现22端口并未被监听，该docker并未启动ssh
安装sshd
`apt-get install openssh-server`
运行sshd 
`/usr/sbin/sshd`
报错:
'Missing privilege separation directory: /run/sshd'
`mkdir -p /run/sshd`
再次启动，22端口成功监听
---------
## [MyLabNotes](./csapp_lab.md)

### Finish Data Lab: 8/Feb/2023

Attention that the last Function in DataLab "floatPower2" would be TLE without extra command option "-T 15",which extend time from 10s to 15s

> ./btest -f floatPower2 -T 15
