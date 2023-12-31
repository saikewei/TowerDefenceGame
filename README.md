# TowerDefenceGame
## 项目名称
TowerDefenceGame
## 项目简介
基于Unreal Engine 5开发的2D塔防游戏保卫萝卜
## 成员分工
|姓名|学号|负责工作|编写的类|贡献占比|
|---|---|---|---|---|
|黄毅成（组长）|2252634|怪物行为、动画实现<br>怪物生成逻辑实现<br>怪物波次实现<br>HUD实现<br>暂停、结束菜单实现<br>倍速、暂停功能实现<br>存档功能实现<br>索敌功能实现<br>障碍物实现<br>Android环境配置|CountdownFlipbookActor<br>GameHUD<br>GameOverMenu<br>GameWinMenu<br>HPBarWidget<br>MainMenuGameModeBase<br>MonsterPaperFlipbookActor<br>ObstaclePaperFlipbookActor<br>PauseMenu<br>SplinePathActor<br>TowerDefenceGameState<br>TowerDefenceGameModeBase<br>TowerDefenceSaveGame|35%|
|张扬|2253722|塔基功能实现<br>防御塔生成、销毁逻辑实现<br>防御塔攻击、升级逻辑实现<br>三类防御塔功能实现<br>防御塔相关动画、音效实现<br>防御塔子弹功能实现<br>防御塔建造UI与升级出售UI|TowerpaperFlipbookActor<br>TowerBase<br>Bullet<br>TBottle<br>TBottleBullet<br>TShit<br>TShitBullet<br>TFan<Br>TFanBullet<br>BuildMenu<br>UpgradeSellMenu|35%|
|奥泉瑞|2250695|游戏初始界面的UI设计<br>关卡选择界面的UI设计<br>ABOUT页面的设计<br>萝卜形象的设计及显示<br>萝卜血量的变化及显示<br>萝卜技能的实现|Carrot<br>UpgradeCarrotMenu|30%|
## 项目实现功能
### 基础功能
* 支持3种防御塔和防御塔的删除
* 支持每种防御塔的攻击特效
* 支持怪物、萝卜生命值显示
* 支持资源功能，资源可用于购买防御塔，资源可通过击杀怪物获得
* 支持每种防御塔的升级，至少可升级2次
* 支持萝卜的升级，至少可升级2次
* 支持至少3种怪物
* 支持至少2张地图
* 支持背景音乐
* 支持关卡选择界面和保存通关进度记录功能
### 扩展功能
* 支持防御塔的建造、删除特效
* 支持攻击、建造、出售、击杀时的音效
* 支持选定攻击目标
* 支持场景破坏功能，即需要先将场景中的元素破坏后再生成防御塔底座进而建造防御塔的设定
* 支持暂停游戏功能
* 支持倍速功能
* 支持重新开始关卡功能
### 加分项
* 合理使用Git控制版本，将项目开源至GitHub
* 团队成员分工合理平等
* 界面精美
* 可移植到Android平台
* 没有内存泄漏
* 运行游戏时不会发生崩溃情况
* 尽可能多地使用了C++11特性
### 使用的C++特性
* STL容器
* 迭代器
* 类和多态
* Lambda表达式
* auto关键字
* 基于范围的for循环
## 集成开发环境
Microsoft Visual Studio 2022



