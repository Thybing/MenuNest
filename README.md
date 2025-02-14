# MenuNest

MenuNest是一个C语言实现的菜单框架。为嵌入式项目提供菜单开发的基本框架。将可扩展性作为框架的主要目标之一，使用大量回调函数和void*。将解耦合性作为框架的另一个目标，做到可以使嵌入式项目将此菜单作为一个模块使用，而不是使整个嵌入式程序跑在菜单框架之上。

为了方便使用，已经用该框架实现了一个菜单menu_nest_tiny。

TODO：该框架的最初目的是为了开发一个丝滑菜单，所以后续应该会移植一些图形库然后去写丝滑菜单。

## 快速开始

### 不想二次开发，只想找一个嵌入式菜单？
先至少阅读到核心步骤 , 然后直接在Example中获取基于tiny的示例工程。

### 添加库

将 menu_nest_lib 文件夹拷贝到项目中。将 menu_nest_lib/inc/ 文件夹添加到includePath。将 menu_nest_lib/src/ 中所需的c文件添加到需要编译的文件列表中。

如果只需要框架，可以将menu_nest_tiny删除。

### 进行简单的接口实现

1, 添加断言
在 menu_nest_lib/inc/menu_nest/common.h中找到
```c
#define MN_assert(x)
```

在这里添加断言宏(可以include开发板的头文件)。请务必要添加，防止找不到错误的位置。如果实在不会写，也可以陷入一个死循环，并且点亮一个灯作为标识，防止程序在错误下继续执行。
例如:
```c
#include "some_headfile_for_your_assert.h"

#define MN_assert(x) assert_func_of_this_board(x)
// 可以勉强用下面这样，或者自己写其它的
#define MN_assert(x) do{ \
    if(!(x)) { \
        assert_led_on(); \
        while(1); \
    } \
}while(0)
```

基础的框架已经完成了。接下来是在此基础上移植menu_nest_tiny的过程

2, 实现menu_nest_tiny/display.c中的绘制接口(为移植方便，暂仅有几个函数)。修改menu_nest_tiny/display.h中的显示参数宏定义(文件内有提示)。


### 如何使用？

#### 核心步骤

1.首先include头文件，#include "menu_nest/menu.h"

2.创建一个页面。调用MN_menu_init并将刚刚的页面作为主页面传入。

3.程序中如果检测到输入，那么将输入添加到输入队列中。(MN_menu_input(XXX))

4.在主循环中调用
MN_menu_handle_input_queue()
MN_menu_rendering()
来处理你的输入队列和显示你的当前页面。

#### 如何输入与菜单进行交互？

要编写相应的交互函数，然后作为menu/page/item的回调函数传入。

在输入触发时调用MN_menu_input(XXX)将输入添加到输入队列中。

在主循环调用MN_menu_handle_input_queue()，它会自动的按照一定次序调用交互模块。

对于menu_nest_tiny，库中的page与item都已经编写并设置了相应的回调函数。menu_nest_tiny/display.c 中定义了一些按键输入。在对应的按键触发后，调用函数MM_menu_input(XXX)将输入添加到菜单的输入队列中。示例中有完整过程。示例中用到了我写的一个[按键库](https://github.com/Thybing/Button)来检测按键触发。

详细请直接阅读框架中的注释。

#### 如何创建page或item？

调用框架相应的create函数生成对象，然后写好它们所需的各种回调函数，并且设置好这些回调函数。生成的item调用函数添加到page中。

在menu_nest_tiny中已经写好了一些比较常用的item和page。能够满足简单的嵌入式项目的使用。如果有满足不了需要的地方可以自己根据框架进行二次开发。


#### menu_nest_tiny库看着有点简陋？
由于可移植性的考量和tiny库编写时没有可用的图形库的限制。调用的绘制函数相当有限(从对接的接口也看出来了。只有显示字符串，清屏，画横线竖线)，所以tiny库中的渲染效果比较(非常)简陋。当然可以自己进行二次开发，重写其中的渲染回调。


## 基本设计思路
菜单框架整体有五部分构成。
menu、page、item、interaction、render，分别为菜单、页面、物体、交互器和渲染器。

menu是单例对象，维护一个页面跳转的历史记录栈。像是一个菜单页面的管理器。
page中有着菜单列表，记录着page中的所有的item。
item是页面的具体物体。可以被添加到page中。

menu、每一个page、每一个item都有一个指针指向一个interaction模块，并且这些interaction中也有一个指针指向模块的所有者，用来告诉模块是谁持有了自己。这些interaction交互模块用来处理菜单的输入。

每一个page、item、都有一个指针指向其render渲染模块。同上，render渲染模块中也会有一个指针指向其所有者。这些render模块用来进行菜单的渲染任务。菜单是以页面作为渲染调度的单位，会进行当前页面的渲染任务。所以没有给menu对象添加渲染模块。

## 第三方库

在示例中的stm32_f103的示例内，使用了Stm32CubeMX生成的工程模板。

在示例中的stm32_f103的示例内，使用了ssd1306驱动屏幕的驱动库。来自仓库[https://github.com/afiskon/stm32-ssd1306](https://github.com/afiskon/stm32-ssd1306)

在menu_nest_tiny的示例中调用了我之前写过的一个按键库。[Button](https://github.com/Thybing/Button)
