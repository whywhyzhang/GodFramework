# God开发框架设计

## 框架概述：

God开发框架的主体为God类，每一个此类的实体就是一个世界的实体。  
God类主管整个世界（程序）的运行，可以比喻为一个进程。  

G_World类的对象表示一个世界，也就是一个运行实体，也算是一个线程。  
每个God对象可以有多个World，每个World只属于一个God。  
World对象可以表示或明或暗的世界，其中物理引擎世界可以架构到这里来，为一个World类的子类。  

G_Object类表示的是对象类，其对象是世界中的物体的实体。也是World运行时操作的主体。  
Object对象有三类分别为Input对象，Output对象，Sprit对象。  
每个World可以有多个Object，每个Object只属于一个World。  

G_Input类表示输入类，是对World进行外部刺激的类，World在没有外部刺激的时候是静止的，不运行的。  
Input类为抽象类，其中可以延伸出KeyMouse输入，Time输入，等等，可以进行自定义。而且这里是跨平台的。  
Input接受来自操作系统的Event，然后转化为Message发送给其所属的World。等待其处理。  

G_Eye类表示的是上帝的眼睛，也就是对于所有要输出的东西进行处理。  
（此类目前暂疑。）  

G_Output类表示输出类，是World里面输出的对象，显示器或者音频等。  

G_Sprit类为精灵类，可以表示为World对象中的所有要运行的实体。  
