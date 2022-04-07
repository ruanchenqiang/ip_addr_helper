[TOC]

#### 接口说明

接口名称         | 接口功能
--------         | --------
ip_addr_category | 检查ip地址类别

#### 输入

参数  | 是否必填 | 说明
----  | -------- | ----
参数1 | 是       | ip地址表达式
参数2 | 否       | ipv4掩码位数、ipv4掩码地址、ipv6前缀长度

#### 输出

返回值                      | 说明
------                      | ----
IP_ERROR                    | 参数1是非法的ip地址
IP_MASK_ERROR               | 参数2是非法的掩码或非法的前缀，只有参数2存在时才可能返回
IPV4_ADDR_ANY               | 0.0.0.0，与参数2无关
IPV4_CLASS_A_RESERVED       | 0.0.0.1~0.255.255.255，与参数2无关，A类保留地址，用做表示所有的IP地址
IPV4_CLASS_A                | 1.0.0.0~126.255.255.255，大量主机的大型网络
IPV4_ADDR_LOOPBACK          | 127.0.0.0~127.255.255.255，与参数2无关，ipv4回环测试保留地址，从A类地址中细分
IPV4_CLASS_B                | 128.0.0.0~191.255.255.255，中等规模主机数的网络
IPV4_CLASS_C                | 192.0.0.0~223.255.255.255，小型局域网
IPV4_CLASS_D                | 224.0.0.0~239.255.255.255，留给Internet体系结构委员会(IAB)使用组播地址
IPV4_CLASS_E                | 240.0.0.0~255.255.255.254，保留，仅作为搜索、Internet的实验和开发用
IPV4_ADDR_LIMITED_BROADCAST | 255.255.255.255，与参数2无关，受限广播地址，从E类地址中细分
IPV4_ADDR_NETWORK_ID        | ipv4网络地址，与参数2掩码按位与操作后主机号全为0的地址
IPV4_ADDR_BROADCAST         | ipv4直接广播地址，与参数2掩码按位与操作后主机号全为1的地址
IPV6_ADDR_UNSPECIFIED       | ::/128，ipv6未指定地址
IPV6_ADDR_LOOPBACK          | ::1/128，ipv6回环测试地址
IPV6_ADDR_V4COMPAT          | ::/96，兼容ipv4的ipv6地址
IPV6_ADDR_V4MAPPED          | ::ffff:0:0/96，映射ipv4的ipv6地址
IPV6_ADDR_LINKLOCAL         | fe80::/10，ipv6链路本地地址
IPV6_ADDR_SITELOCAL         | fec0::/10，ipv6站点本地地址
IPV6_ADDR_MULTICAST         | ff00::/8，ipv6组播地址
IPV6_ADDR_UNICAST           | ipv6单播地址

#### 测试用例

```
返回 IP_ERROR
./ip_addr_category x.x.x.x
./ip_addr_category xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx

返回 IP_MASK_ERROR
./ip_addr_category 192.168.0.1 mask
./ip_addr_category 192.168.0.1 -1
./ip_addr_category 192.168.0.1 0
./ip_addr_category 192.168.0.1 33
./ip_addr_category 2021::1001 -1
./ip_addr_category 2021::1001 0
./ip_addr_category 2021::1001 129

返回 IPV4_ADDR_ANY
./ip_addr_category 0.0.0.0
./ip_addr_category 0.0.0.0 8
./ip_addr_category 0.0.0.0 16
./ip_addr_category 0.0.0.0 24
./ip_addr_category 0.0.0.0 32
./ip_addr_category 0.0.0.0 255.0.0.0
./ip_addr_category 0.0.0.0 255.255.0.0
./ip_addr_category 0.0.0.0 255.255.255.0
./ip_addr_category 0.0.0.0 255.255.255.255

返回 IPV4_CLASS_A_RESERVED
./ip_addr_category 0.0.0.1
./ip_addr_category 0.0.0.1 8
./ip_addr_category 0.0.0.1 16
./ip_addr_category 0.0.0.1 24
./ip_addr_category 0.0.0.1 32
./ip_addr_category 0.0.0.1 255.0.0.0
./ip_addr_category 0.0.0.1 255.255.0.0
./ip_addr_category 0.0.0.1 255.255.255.0
./ip_addr_category 0.0.0.1 255.255.255.255
./ip_addr_category 0.255.255.254
./ip_addr_category 0.255.255.254 8
./ip_addr_category 0.255.255.254 16
./ip_addr_category 0.255.255.254 24
./ip_addr_category 0.255.255.254 32
./ip_addr_category 0.255.255.254 255.0.0.0
./ip_addr_category 0.255.255.254 255.255.0.0
./ip_addr_category 0.255.255.254 255.255.255.0
./ip_addr_category 0.255.255.254 255.255.255.255
./ip_addr_category 0.255.255.255
./ip_addr_category 0.255.255.255 8
./ip_addr_category 0.255.255.255 16
./ip_addr_category 0.255.255.255 24
./ip_addr_category 0.255.255.255 32
./ip_addr_category 0.255.255.255 255.0.0.0
./ip_addr_category 0.255.255.255 255.255.0.0
./ip_addr_category 0.255.255.255 255.255.255.0
./ip_addr_category 0.255.255.255 255.255.255.255

返回 IPV4_ADDR_LOOPBACK
./ip_addr_category 127.0.0.0
./ip_addr_category 127.0.0.0 8
./ip_addr_category 127.0.0.0 16
./ip_addr_category 127.0.0.0 24
./ip_addr_category 127.0.0.0 32
./ip_addr_category 127.0.0.0 255.0.0.0
./ip_addr_category 127.0.0.0 255.255.0.0
./ip_addr_category 127.0.0.0 255.255.255.0
./ip_addr_category 127.0.0.0 255.255.255.255
./ip_addr_category 127.0.0.1
./ip_addr_category 127.0.0.1 8
./ip_addr_category 127.0.0.1 16
./ip_addr_category 127.0.0.1 24
./ip_addr_category 127.0.0.1 32
./ip_addr_category 127.0.0.1 255.0.0.0
./ip_addr_category 127.0.0.1 255.255.0.0
./ip_addr_category 127.0.0.1 255.255.255.0
./ip_addr_category 127.0.0.1 255.255.255.255
./ip_addr_category 127.255.255.254
./ip_addr_category 127.255.255.254 8
./ip_addr_category 127.255.255.254 16
./ip_addr_category 127.255.255.254 24
./ip_addr_category 127.255.255.254 32
./ip_addr_category 127.255.255.254 255.0.0.0
./ip_addr_category 127.255.255.254 255.255.0.0
./ip_addr_category 127.255.255.254 255.255.255.0
./ip_addr_category 127.255.255.254 255.255.255.255
./ip_addr_category 127.255.255.255
./ip_addr_category 127.255.255.255 8
./ip_addr_category 127.255.255.255 16
./ip_addr_category 127.255.255.255 24
./ip_addr_category 127.255.255.255 32
./ip_addr_category 127.255.255.255 255.0.0.0
./ip_addr_category 127.255.255.255 255.255.0.0
./ip_addr_category 127.255.255.255 255.255.255.0
./ip_addr_category 127.255.255.255 255.255.255.255

返回 IPV4_CLASS_A
./ip_addr_category 1.0.0.0
./ip_addr_category 1.0.0.1
./ip_addr_category 126.255.255.254
./ip_addr_category 126.255.255.255
./ip_addr_category 10.0.0.1 8
./ip_addr_category 10.0.0.1 16
./ip_addr_category 10.0.0.1 24
./ip_addr_category 10.0.0.1 255.0.0.0
./ip_addr_category 10.0.0.1 255.255.0.0
./ip_addr_category 10.0.0.1 255.255.255.0

返回 IPV4_CLASS_B
./ip_addr_category 128.0.0.0
./ip_addr_category 128.0.0.1
./ip_addr_category 191.255.255.254
./ip_addr_category 191.255.255.255
./ip_addr_category 128.144.3.120 16
./ip_addr_category 128.144.3.120 24
./ip_addr_category 128.144.3.120 255.255.0.0
./ip_addr_category 128.144.3.120 255.255.255.0

返回 IPV4_CLASS_C
./ip_addr_category 192.0.0.0
./ip_addr_category 192.0.0.1
./ip_addr_category 223.255.255.254
./ip_addr_category 223.255.255.255
./ip_addr_category 192.168.3.130 24
./ip_addr_category 192.168.3.130 255.255.255.0

返回 IPV4_CLASS_D
./ip_addr_category 224.0.0.0
./ip_addr_category 224.0.0.1
./ip_addr_category 224.0.0.1 8
./ip_addr_category 224.0.0.1 16
./ip_addr_category 224.0.0.1 24
./ip_addr_category 224.0.0.1 32
./ip_addr_category 224.0.0.1 255.0.0.0
./ip_addr_category 224.0.0.1 255.255.0.0
./ip_addr_category 224.0.0.1 255.255.255.0
./ip_addr_category 224.0.0.1 255.255.255.255
./ip_addr_category 239.255.255.254
./ip_addr_category 239.255.255.255

返回 IPV4_CLASS_E
./ip_addr_category 240.0.0.0
./ip_addr_category 240.0.0.1
./ip_addr_category 240.0.0.1 8
./ip_addr_category 240.0.0.1 16
./ip_addr_category 240.0.0.1 24
./ip_addr_category 240.0.0.1 32
./ip_addr_category 240.0.0.1 255.0.0.0
./ip_addr_category 240.0.0.1 255.255.0.0
./ip_addr_category 240.0.0.1 255.255.255.0
./ip_addr_category 240.0.0.1 255.255.255.255
./ip_addr_category 255.255.255.254

返回 IPV4_ADDR_NETWORK
./ip_addr_category 10.0.0.0 8
./ip_addr_category 10.5.0.0 16
./ip_addr_category 10.5.6.0 24
./ip_addr_category 10.0.0.0 255.0.0.0
./ip_addr_category 10.5.0.0 255.255.0.0
./ip_addr_category 10.5.6.0 255.255.255.0
./ip_addr_category 128.0.0.0 16
./ip_addr_category 192.0.0.0 24
./ip_addr_category 128.0.0.0 255.255.0.0
./ip_addr_category 192.0.0.0 255.255.255.0
./ip_addr_category 10.0.0.0 255.0.0.0
./ip_addr_category 10.5.0.0 255.255.0.0
./ip_addr_category 10.5.6.0 255.255.255.0
./ip_addr_category 128.0.0.0 255.255.0.0
./ip_addr_category 192.0.0.0 255.255.255.0

返回 IPV4_ADDR_BROADCAST
./ip_addr_category 10.255.255.255 8
./ip_addr_category 10.5.255.255 16
./ip_addr_category 10.5.6.255 24
./ip_addr_category 10.255.255.255 255.0.0.0
./ip_addr_category 10.5.255.255 255.255.0.0
./ip_addr_category 10.5.6.255 255.255.255.0
./ip_addr_category 191.255.255.255 16
./ip_addr_category 223.255.255.255 24
./ip_addr_category 191.255.255.255 255.255.0.0
./ip_addr_category 223.255.255.255 255.255.255.0
./ip_addr_category 10.255.255.255 255.0.0.0
./ip_addr_category 10.5.255.255 255.255.0.0
./ip_addr_category 10.5.6.255 255.255.255.0
./ip_addr_category 191.255.255.255 255.255.0.0
./ip_addr_category 223.255.255.255 255.255.255.0

返回 IPV4_ADDR_LIMITED_BROADCAST
./ip_addr_category 255.255.255.255
./ip_addr_category 255.255.255.255 8
./ip_addr_category 255.255.255.255 16
./ip_addr_category 255.255.255.255 24
./ip_addr_category 255.255.255.255 32
./ip_addr_category 255.255.255.255 255.0.0.0
./ip_addr_category 255.255.255.255 255.255.0.0
./ip_addr_category 255.255.255.255 255.255.255.0
./ip_addr_category 255.255.255.255 255.255.255.255

返回 IPV6_ADDR_UNSPECIFIED
./ip_addr_category ::
./ip_addr_category ::0.0.0.0
./ip_addr_category 0:0:0:0:0:0:0:0
./ip_addr_category 0000:0000:0000:0000:0000:0000:0000:0000

返回 IPV6_ADDR_LOOPBACK
./ip_addr_category ::1
./ip_addr_category ::0.0.0.1
./ip_addr_category 0:0:0:0:0:0:0:1
./ip_addr_category 0000:0000:0000:0000:0000:0000:0000:0001

返回 IPV6_ADDR_V4COMPAT
./ip_addr_category ::2
./ip_addr_category ::0.0.0.2
./ip_addr_category ::0:0:0:2
./ip_addr_category ::127.0.0.1
./ip_addr_category ::7F00:0001
./ip_addr_category ::FFFF:FFFE
./ip_addr_category ::255.255.255.254
./ip_addr_category ::FFFF:FFFF
./ip_addr_category ::255.255.255.255

返回 IPV6_ADDR_V4MAPPED
./ip_addr_category ::FFFF:0.0.0.0
./ip_addr_category ::FFFF:0000:0000
./ip_addr_category ::FFFF:0.0.0.1
./ip_addr_category ::FFFF:0000:0001
./ip_addr_category ::FFFF:127.0.0.1
./ip_addr_category ::FFFF:7F00:0001
./ip_addr_category ::FFFF:255.255.255.254
./ip_addr_category ::FFFF:FFFF:FFFE
./ip_addr_category ::FFFF:255.255.255.255
./ip_addr_category ::FFFF:FFFF:FFFF

返回 IPV6_ADDR_LINKLOCAL
./ip_addr_category fe80::
./ip_addr_category fe80::1
./ip_addr_category febf:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category febf:ffff:ffff:ffff:ffff:ffff:ffff:ffff

返回 IPV6_ADDR_SITELOCAL
./ip_addr_category fec0::
./ip_addr_category fec0::1
./ip_addr_category feff:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category feff:ffff:ffff:ffff:ffff:ffff:ffff:ffff

返回 IPV6_ADDR_MULTICAST
./ip_addr_category ff00::
./ip_addr_category ff00::1
./ip_addr_category ff02::1
./ip_addr_category ffff:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff

返回 IPV6_ADDR_UNICAST
./ip_addr_category 0000:0000:0000:0000:0000:0001:0000:0000
./ip_addr_category 0000:0000:0000:0000:0000:0001:0000:0001
./ip_addr_category 0000:0000:0000:0000:0000:0001:ffff:fffe
./ip_addr_category 0000:0000:0000:0000:0000:0001:ffff:ffff
./ip_addr_category 0000:0000:0000:0000:0000:fffe:0000:0000
./ip_addr_category 0000:0000:0000:0000:0000:fffe:0000:0001
./ip_addr_category 0000:0000:0000:0000:0000:fffe:ffff:fffe
./ip_addr_category 0000:0000:0000:0000:0000:fffe:ffff:ffff
./ip_addr_category 0000:0000:0000:0000:0001:0000:0000:0000
./ip_addr_category 0000:0000:0000:0000:0001:0000:0000:0001
./ip_addr_category 0000:0000:0000:0000:0001:ffff:ffff:fffe
./ip_addr_category 0000:0000:0000:0000:0001:ffff:ffff:ffff
./ip_addr_category 0000:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category 0000:ffff:ffff:ffff:ffff:ffff:ffff:ffff
./ip_addr_category 0001:0000:0000:0000:0000:0000:0000:0000
./ip_addr_category 0001:0000:0000:0000:0000:0000:0000:0001
./ip_addr_category 0001:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category 0001:ffff:ffff:ffff:ffff:ffff:ffff:ffff
./ip_addr_category fe7f:0000:0000:0000:0000:0000:0000:0000
./ip_addr_category fe7f:0000:0000:0000:0000:0000:0000:0001
./ip_addr_category fe7f:ffff:ffff:ffff:ffff:ffff:ffff:fffe
./ip_addr_category fe7f:ffff:ffff:ffff:ffff:ffff:ffff:ffff
```
