# TxOpenClassTask

readme太空了没意思所以把我的零基础起步笔记放在这里，一边做一边写的比较随心，点到为止。

> 配合UE官方的第一人称模板项目食用更佳

## C++如何输出日志
### UE_LOG宏
输出日志： https://dev.epicgames.com/documentation/en-us/unreal-engine/logging-in-unreal-engine
可以使用c风格格式化输出： `UE_LOG(LogTemp, Warning, TEXT("VisualTextExisting - %s"), (VisualText ? "true" : "false"));`

日志中文乱码解决： ue编辑器Settings有个Region & Language，里面EditorLanguage和EditorLocale都改成English的

### AddOnScreenDebugMessage
`GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hit on!"));`
`GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("Hit on!"));`

FString可以借助它的格式化字符串的API `FString::Printf`和`FString::Format`
`FString::Printf(TEXT("actor: %s"), *OtherActor->GetName()));`
```c++
args.Add(*OtherActor->GetName());
auto log = FString::Format(TEXT("actor: {0}"), args);
// 好像有点编码问题中文有概率乱码
```

## Gameplay框架
### Concepts
#### UObject
UObject是UE所有内置类的基类

#### Actor
> Actor is the base class for an Object that can be placed or spawned in a level.

Actor是UE游戏中的重要组成部分。
UE和Unity很像，按组加载游戏中的对象，对象身上携带若干组件来实现自己的特性。在Unity中，就是按Scene加载GameObject，GameObject身上携带若干Component。在UE中，是按Level加载Actor，Actor自身可以被继承改写，Actor携带若干Component。

Actor还提供了生命周期函数如BeginPlay、Tick，分别对应游戏开始和游戏每帧。以及Actor的构造函数，和BeginPlay的区别是构造函数在编辑器内就会被调用。

Actor自身也可以被继承，UE提供了很多如Camera Actor，Static Mesh Actor
不同的Actor（以及Comopnent）体现在两方面：
- 写代码使用
- 编辑器使用

不同Actor会被编辑器解析出不同的数据配置项

#### Level
Level存放Actor，也就相当于Unity的Scene

#### GameMode
定义游戏运行的规则。

你可以在ProjectSettings - Maps & Modes中找到Default Modes - Default GameMode，以官方的第一人称模板为例，默认引用的是一个蓝图类（.uasset文件）

这个蓝图类是纯数据蓝图，没有任何定义的逻辑，唯一做的是配了一堆数据。

### Scripting
Blueprint vs C++

你可以用c++重写actor和component并使用
blueprint更像unity的prefab，而且是可以连连看逻辑的prefab，与之对应的unity的prefab其实是一个data-only blueprint

## UE第一人称模板
### BP_PickUp_Rifle
这是捡枪的蓝图类

继承自Actor，我一开始有点懵，一看底下一堆乱七八糟的逻辑AActor类里都没有啊，后来才发现他用了自己写的Component。
一共是TP_PickUpComponent和TP_WeaponComponent，源文件在C++文件夹里面
里面包括OnPickUp委托的实现，AttchWeapon的实现等等

TP_WeaponComponent.Fire()为开枪，生成了ATxOpenClassTaskProjectile这个Actor
ATxOpenClassTaskProjectile中实现了OnHit方法，这个方法作为子弹Actor碰撞箱组件的碰撞事件的响应。

## UMG
ue的ui解决方案：umg、slate
其实umg是对slate的一种封装，2DGUI用umg可以很高效的开发，但是3DGUI或底层GUI开发还是需要使用slate

**创建widget blueprint**
umg通过在ue资源管理器中创建widget blueprint来实现，双击以后可以打开一个可视化的design tool。ue5的界面中可以在右上角切换designer mode和graph mode，graph mode是我们更为熟悉的普通蓝图编辑界面。

常用控件？
canvas panel
button

**实例化**
CreateWidget实例化umg
实例化后还没完，显示到界面还需要用Add to Viewport节点

**InputMode**
因为区分了GameInput和UI Input，会冲突

**level streaming**
不阻塞前台ui的情况下加载level
这里区分了persistent level和sub level
笔者第一次看到的时候最迷惑的就是nm这个持久关卡到底是什么wy是独立uasset吗还是蓝图资源，最后才发现原来是存储当前选中的level资源里的配置项。

window菜单找到level窗口打开，窗口中会展示当前level的persistent level和sub level设置。persistent level不能被流式加载要一直存在，sub level才是你要流式加载的

配置好了以后就可以用蓝图的load stream level节点加载了

**delegate**
cpp中的声明宏叫 DECLARE_DELEGATE
还有 区分 dynamic multicast 的委托

**加载level的三种方式（蓝图）**
Open Level
Load Level Instance
Load Stream Level

https://zhuanlan.zhihu.com/p/395615335

### Character和PlayerController
ue模板项目的人物移动是如何实现的？
move-input -> XXXCharacter::Move -> AddMovementInput

## 动画（骨骼动画）
**区分名词static mesh, skeleton, skinning, skeletal mesh**

static mesh，mesh即模型，静态网格体就是没有动画的模型物体

接下来是skeletal mesh，我们需要先了解骨架（Skeleton）
Skeleton是纯骨骼动画，无模型

现在需要加上模型，详细来说，我们需要每个骨骼(bones)和模型的顶点(vertices)的影响程度关系，这一步叫蒙皮(Skinning)/刷权重，然后我们就得到了有骨骼动画的模型，这就是skeletal mesh

**创建一个动画+蓝图播放（animation blueprint）**
https://www.youtube.com/watch?v=etRZu5UG_S0
创建一个animation blueprint，它也是一个蓝图
在Event Graph旁边可以找到Anim Graph，Output Pose就是最后要播放的动作。

最简单的办法：把一个动画文件拖进来就能播放。
但是我们要介绍一个高级的，用state machine，需要你在蓝图界面右键创建state machine节点。
<!-- 实际上这个状态机节点是专门给动画用的，所以你会见到里面有很多动画相关的逻辑。-->

**在具体的Actor上使用**
你需要一个Character，然后在Details中的Animation栏中，动画模式调为use animation blueprint，Anim class使用制作好的Animation Blueprint。

还没完，接下来还有变量的传递，在animation blueprint的event graph中，使用Try Get Pawn Onwer节点获取当前的Pawn或Pawn子类（如Character），就可以访问了

## 其他API
### 蓝图
**Vector**
MakeVector构造向量
BreakVector获取向量分量
