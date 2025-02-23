# 桥牌游戏项目

本项目包含两个桥牌游戏实现，均利用`/dev/urandom`生成随机数。

## 项目一：桥牌发牌程序

- **文件**：`hw6.3_done_by_rddevice.cpp`
- **可执行文件**：`main1`
- **功能**：模拟发牌，每位玩家13张牌。

## 项目二：桥牌库程序

- **核心文件**：`bridgepoker_lib.cpp`
- **辅助文件**：`hw7.2_done_by_rddevice.cpp`, `random.h`
- **可执行文件**：`main2`
- **功能**：提供游戏逻辑和管理功能。

## `main1`和`main2`都
- 利用`/dev/urandom`确保洗牌和发牌的随机性。
- 可独立编译运行。
