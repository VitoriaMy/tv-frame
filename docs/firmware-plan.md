# 固件结构规划说明

## 1. 文档目标

本文档用于规划 `firmware/esp32_servo_platform/` 目录的初始代码组织方式，帮助将现有文档中的控制逻辑逐步落地为实际工程结构。

---

## 2. 推荐目录结构

```text
firmware/
└─ esp32_servo_platform/
   ├─ src/
   │  ├─ main.cpp
   │  ├─ state_machine.h
   │  ├─ state_machine.cpp
   │  ├─ motion_controller.h
   │  ├─ motion_controller.cpp
   │  ├─ bluetooth_manager.h
   │  ├─ bluetooth_manager.cpp
   │  ├─ safety_manager.h
   │  ├─ safety_manager.cpp
   │  ├─ config.h
   │  └─ ui_feedback.h
   │  └─ ui_feedback.cpp
   └─ platformio.ini
```

---

## 3. 模块职责建议

### 3.1 main.cpp
- 系统初始化
- 主循环调度
- 调用输入采集、状态机执行和输出更新逻辑

### 3.2 state_machine
- 定义系统状态
- 处理状态切换逻辑
- 管理自动运行与手动模式流程

### 3.3 motion_controller
- 封装平台运动控制接口
- 提供 move、stop、home、getPosition 等能力
- 隔离底层驱动器细节

### 3.4 bluetooth_manager
- 扫描或检测目标设备状态
- 管理 MAC 绑定与稳定状态输出
- 对外输出在线 / 离线 / 不确定状态

### 3.5 safety_manager
- 检查限位、急停、动作超时、未到位等异常
- 输出故障状态与故障码

### 3.6 ui_feedback
- 串口日志输出
- LED 指示控制
- 蜂鸣器输出

### 3.7 config.h
- 集中定义位置参数、超时参数和 I/O 映射

---

## 4. 建议实现顺序

1. 搭建目录结构
2. 完成 `config.h`
3. 完成 `motion_controller` 基础接口
4. 完成 `state_machine` 基础状态切换
5. 完成 `bluetooth_manager` 基础接口
6. 完成 `safety_manager`
7. 最后接入日志与 UI 反馈模块

---

## 5. 推荐开发原则

- 优先实现可运行的最小状态机
- 所有动作接口尽量非阻塞
- 日志要覆盖状态切换与故障事件
- 参数集中管理，不分散硬编码
- 先实现框架，再逐步替换为真实硬件逻辑
