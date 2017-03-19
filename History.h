/*

//2009年3月
//由于原代码丢失，按记忆恢复
//修改函数和变量定义规范以确保所有程序能检查到


2009年12月

1 调整代码结构，熟悉代码
2 修改以适应diablo 1.13ptr
3 因为1.13游戏自带显示血量和魔法值，去除命令Perm Show Orbs Toggle
  增加显示样式命令Orb Show Pattern :   1  // 0 游戏默认显示  1  80/100(80%)格式显示
4 由于1.13自带类似nohide功能，取消命令Keep Game Window Toggle
5 移除命令Show Exp Mode，用Show Exp Toggle命令赋值代替
6 移除命令Map Scroll Speed，固定值16,移除Switch Scroll Mode，可以通过重载配置来实现
7 移除命令Hidden Items Level
8 显示属性采用和属性页一致的字体,属性显示对齐
9 pet和玩家属性显示分离
10 查看对方装备时，屏蔽点击物品栏
11 优化自动强化算法
12 CFG版本信息
13 bugmf保护触发模式支持
14 新的输入法屏蔽方式,去除命令Disable IME Change
15 物品基础材料显示, 新增命令View Socket Base Items Toggle
16 新增命令Show CFGCheck Info
17 改进了跳过任务信息功能
18 屏蔽113窗口自动居中功能！！命令Windows Auto Center Toggle
19 人物头像上显示等级和场景编号
  增加命令Show Party Position Toggle
  增加命令Show Party Level Toggle
20 让鼠标中键能做快捷键
21 Ctrl+点击移动物品
   命令 Ctrl Click Swap Toggle
        Quick Drop Toggle
	废除Right Click Drop Toggle

22 属性的变量范围,命令Show Item Variable Prop Toggle

23 中文系统判断

24 win7下中文输入问题,编辑时中文乱码问题

25 额外的物品信息

26 Boss名字？

27 自动金钱

28 kill count

29 fhr count

30 状态监控(强化，bo等)

31  GameName Filter

32 nohide!

33 字体做了调整，保证和界面一致

34 CFG加载 ]   记日志加try  增加unicodesuport  unitany  MissileBlobCol  monstercoulour也允许重置
todo
卸载时清除自定义的图块(TODO:完善对于洞穴标题清除)
在停止游戏界面时卸载出错
 --TODO

任意场景指向！暂时放弃
真实游戏时间,放弃


*/