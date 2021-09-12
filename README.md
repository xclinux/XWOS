
# 介绍

玄武操作系统（简称XWOS）是一款运行在嵌入式控制器上的通用微内核国产操作系统，主要面向
可靠、实时、安全的应用领域，包括汽车、物联网、工控等。XWOS的内核支持多核系统(MP) ，
也支持单核系统(UP) 。

XWOS开发于2015年，目前在车载领域已经量产4年。当前已经支持以下特性：

+   高可移植性，支持的架构：PowerPC、ARM、RISC-V。
+   开发环境支持多平台：Linux/Windows/MacOS；
+   便于扩展的编译系统，可快速集成各种组件；
+   提供单核CPU与多核CPU两种内核：
    -   单核CPU的内核可以裁减到只有10+KiB的尺寸，满足低成本的MCU；
+   支持多种语言混合开发：
    -   已经支持的语言：C、C++、Lua；
    -   正在支持的语言：Rust；
+   集成Lua-5.4终端，可通过串口直接将Lua函数当作命令运行，也可执行文件系统中的Lua脚本；
+   自身的命名前缀与命名空间，防止集成第三方组件时发生命名冲突；
+   自带电源管理框架，支持线程**冻结**，支持**"Suspend To RAM"**的休眠方式，唤醒后
    程序状态可恢复，也可从复位开始重新运行。


# 文档

可通过下列任意连接查看XWOS的文档：

+   <https://xwos.tech/>
+   <http://xwos.tech/>
+   <https://xwos.org/>
+   <http://xwos.org/>

若域名访问过慢，也可尝试：

+   <https://xwos.gitee.io/>
+   <https://xwos.github.io/>


# 开源协议

#### MPL-2.0

XWOS核心代码采用[**MPL-2.0**](http://mozilla.org/MPL/2.0/)发布：

-   适用范围：```xwos```、```xwmd```文件夹下的源码；
-   **MPL-2.0**是对商业友好的协议，所有**适用范围的源码文件**只包含了**附录A**中的声明，
    即**Exhibit A - Source Code Form License Notice**，也就是说用户可以
    以任意形式（源码文件、静态库）将XWOS集成到自己的商业的应用场景中，
    在[**MPL-2.0**](http://mozilla.org/MPL/2.0/)中被称为**Larger Work**。

#### Apache-2.0

XWOS的外围代码[**Apache-2.0**](http://www.apache.org/licenses/LICENSE-2.0)发布：

-   适用范围：```xwcd```、```xwbd```、```xwam```、```xwbs```文件夹下的源码；
