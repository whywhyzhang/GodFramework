# God Framework

This is a small framework developed by C++.  
And that's my C++ homework.  
^_^  

The next will be writed by Chinese, if you don't know Chinese, Please use Google Translator. Thank You.  

# 介绍：

	God开发框架是一个跨平台的可扩展的C++开发框架。  
	采用面向对象的方法，抽象所有运行实体为类结构。  
	采用消息触发机制，由消息驱使程序运行状态的改变。  
	封装消息队列和对象管理，采用树形结构管理。  
	
# 框架特性：

	框架分为7个基本类：  
	God类为程序主体，是框架程序的运行所需的载体，理论上程序只需一个God对象就可运行，但是并不限制。  
	G_World类为程序一个线程的主体，God对象可以有多个World对象，一个World对象只属于一个God对象，World对象负责调配其内部所有对象之间的运行关系，管理其所有的消息队列并进行消息的分发。多个World对象可以进行通信。  
	G_Object类为所有World内对象的虚基类，其负责管理对象序列号，以及处理与其所属World的关系，一个World可以有多个Object，但是一个Object只属于一个World。以下四个均属于此类的子类。  
	G_Input类为抽象所有外部输入设备，包括键盘鼠标计时器等，为驱使程序运行的唯一条件，其内部通过对Event的管理来处理硬件设备的中断消息并且发送响应的Message。  
	G_Output类为抽象所有外部输出设备，包括显示器打印机音响等等，为程序向外部展示的唯一出口。其内部通过消息处理函数借口来抽象消息的处理。  
	G_Eye类为抽象所有的视窗管理设备，负责对所有的可以为输出设备所用的Sprit对象进行管理，可以藉此实现2D和3D等的转换。  
	G_Sprit类为抽象的所有程序运行的精灵，包括所有控件，辅助对象类等等。其内部负责处理各种对于Sprit必要的属性。默认Sprit对象是相对于Eye可视的。  
	
	在God框架下构建程序，只需完成每个Sprit类的子类，并且赋予其所属World合适的消息就可以运行，God类和G_World类不能改变。  
	
	框架具有可移植性，目前版本只完成基于Linux的Xlib，只需完成特定的Output和Input的子类即可。  
	
	框架具有可扩展性，可以自己实现各种功能的Sprit，目前实现类Button，Label，Image三个空间。也可以根据需要进行Eye的设计，还有Tool的设计。  
	
	Tool文件内为各种工具，可以自己实现特定的工具，目前只实现了Picture工具。  
	
	完全的封装性，对于内部不可知。  
	
	Window独立于框架，只是一个集合了少量输入输出设备的集合体。  
	
# 框架不足：

	效率偏低，因为过于考虑框架的可扩展性，导致框架的抽象层次过高，无法保证高效的实现。  
	封装性不足，Public方法过多，需要通过友元来改进。  
	安全性不足，安全检测过少，可能导致安全问题。  
	未实现多线程来加速多个World的运行。  
	未实现大量常用框架和设备。  
	具体Document还没写，关于各个类的详细使用方法还未完成。  
	
# 安装：

	需要安装xlib库，为了L_Window的顺利使用。  
	sudo apt-get install libx11-dev
	
	需要安装jpeg库，为了Tool的Picture的顺利使用。  
	http://libjpeg.sourceforge.net/
	
	Example中为示例程序，可以通过make来进行编译运行。  
	
	注：此框架目前只支持Linux系统。  
