## 🛠️ 项目文档：基于蓝牙监听的隐藏式激光电视伺服定位伸缩架

本项目面向隐藏式激光电视柜模块、超窄型电视柜集成方案和具备产品化外观要求的智能家居展示结构。系统通过 ESP32 监听目标设备蓝牙状态，控制主平台精准滑出，并联动双段式上盖完成隐藏与开启动作。

当前版本已从传统“电动推杆 + 限位停机”思路，升级为：

- **主平台精准定位**
- **前滑盖与平台同步联动**
- **双段式上盖隐藏结构**
- **支持外部层板安装与柜体整合**
- **面向产品化外观与模块化安装**

---

## 一、项目概览

### 1.1 设计目标
- 实现激光电视平台自动滑出与回收。
- 利用蓝牙连接状态作为自动动作触发信号。
- 实现平台精准定位与安全回零。
- 支持双段式上盖同步联动。
- 支持外部层板、饰面板与整柜安装。

### 1.2 已知设备条件
- 投影设备尺寸：**510 × 270 × 144 mm**
- 投影设备重量：**7.9 kg**
- 建议平台有效尺寸：**≥ 560 × 320 mm**
- 建议整机结构按 **15–20 kg** 级等效载荷设计

### 1.3 核心结构特征
- **固定后盖 + 前滑盖** 双段式上盖
- 前滑盖在平台滑出时同步后收至固定后盖下方
- 主平台采用伺服定位或带编码器驱动方案
- 框架预留外部层板与装饰件安装界面

---

## 二、文档导航

详细设计内容已拆分至 `docs/` 目录，便于按模块查阅与持续迭代。

### 2.1 结构设计与装配
````markdown name=docs/assembly-guide.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/assembly-guide.md
- 结构模块划分
- 分层结构关系
- 推荐安装顺序
- 安装基准建议
- 装配公差建议
- 维护与验收检查表
````

### 2.2 电气与接线设计
````markdown name=docs/wiring-diagram.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/wiring-diagram.md
- 系统电气模块划分
- 接线关系建议
- 电源设计原则
- 限位与原点设计
- 布线与抗干扰建议
- 电气调试顺序
````

### 2.3 故障排查与调试
````markdown name=docs/troubleshooting.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/troubleshooting.md
- 蓝牙检测类问题
- 平台运动类问题
- 滑盖联动类问题
- 外部层板集成问题
- 电控与外观问题
- 排查顺序建议
````

### 2.4 ESP32 控制版本说明
````markdown name=docs/esp32-servo-version.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/esp32-servo-version.md
- ESP32 控制架构
- 状态机设计
- 输入输出接口建议
- 软件保护建议
- 参数建议
- 扩展方向
````

### 2.5 柜体集成设计
````markdown name=docs/cabinet-integration.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/cabinet-integration.md
- 内嵌式 / 半嵌式 / 独立模块式方案
- 柜体空间规划
- 开口与安装界面建议
- 散热与维护设计
- 外观整合建议
````

### 2.6 BOM 采购与选型建议
````markdown name=docs/bom-selection.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/bom-selection.md
- 入门版 / 稳定版 / 产品化版分级
- 主控、驱动、导向、联动、电源、饰面选型建议
- 采购顺序与备件建议
````

### 2.7 外观尺寸与产品化细节
````markdown name=docs/appearance-dimensions.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/appearance-dimensions.md
- 外观比例建议
- 面板与拼缝建议
- 层板与饰面厚度建议
- 顶盖与正面视觉建议
- 产品化细节建议
````

### 2.8 联动机构设计
````markdown name=docs/mechanism-linkage.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/mechanism-linkage.md
- 同步带 / 拉索 / 连杆 / 齿条联动方案
- 优缺点对比
- 调试与校准建议
- 产品化方向建议
````

### 2.9 设计图纸说明
````markdown name=docs/design-drawings.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/design-drawings.md
- 总体结构示意
- 顶部结构关系图
- 平台与滑盖联动示意
- 柜体开口示意
- 电控与走线区示意
- 图纸标注与出图优先级建议
````

### 2.10 图纸参数与尺寸建议
````markdown name=docs/drawing-parameters.md url=https://github.com/VitoriaMy/tv-frame/blob/main/docs/drawing-parameters.md
- 平台关键尺寸
- 滑盖与后盖参数
- 层板与孔位参数
- 柜体空间与维护空间建议
- 调平与安装余量建议
````

---

## 三、系统架构摘要

```text
激光电视蓝牙状态
        ↓
   ESP32 主控
      ↓
主平台驱动控制
      ↓
平台精准滑出
      ↘
       前滑盖同步后收
```

### 3.1 动作逻辑
- 电视开机 / 蓝牙连接 → 平台滑出 + 前滑盖同步打开
- 电视关机 / 蓝牙断开 → 平台回位 + 前滑盖同步关闭

### 3.2 控制策略建议
- 优先采用 **ESP32 + 闭环驱动**
- 优先采用 **状态机控制**，避免阻塞式逻辑
- 优先采用 **单电机 + 机械联动** 方案提升同步可靠性

---

## 四、结构设计摘要

### 4.1 上盖结构
- 靠墙一侧为**固定后盖**
- 前侧为**前滑盖**
- 打开时前滑盖收入固定后盖下方
- 关闭后顶面应形成完整连续面

### 4.2 平台与承重
- 主平台承载设备重量 7.9 kg
- 建议按 15–20 kg 等效负载进行导轨和驱动选型
- 平台应满足精准定位、低偏摆、低下沉要求

### 4.3 外部层板支持
- 框架应支持安装装饰层板与功能层板
- 建议预留安装孔位、长条孔或连接支架
- 外部层板不得干涉平台、滑盖与线束运动

---

## 五、推荐阅读顺序

如果你是首次进入本项目，建议按以下顺序阅读：

1. **README.md**：了解项目整体结构与文档导航
2. **docs/assembly-guide.md**：理解结构与安装方式
3. **docs/wiring-diagram.md**：理解电气与接线设计
4. **docs/esp32-servo-version.md**：理解控制逻辑与软件架构
5. **docs/cabinet-integration.md**：理解柜体集成方式
6. **docs/mechanism-linkage.md**：理解联动机构设计
7. **docs/design-drawings.md**：理解图纸逻辑与结构关系
8. **docs/drawing-parameters.md**：查阅关键参数
9. **docs/troubleshooting.md**：用于调试与问题排查

---

## 六、建议后续补充内容

后续建议继续新增以下内容：

- `images/` 目录中的结构示意图与联动草图
- `firmware/` 下的 ESP32 初版程序框架
- 更细的 2D 尺寸图与安装孔位图
- 机构爆炸图与装配顺序图

---

## 七、结语

本项目已经完成从“概念型 DIY 方案”向“模块化、可装配、可产品化方案文档”的初步整理。README 负责项目总览与导航，详细设计内容已逐步拆分进入 `docs/` 目录，便于后续持续细化、维护与版本管理。

如果继续推进，建议下一步优先完善：
- `images/` 结构示意图
- `firmware/` 控制程序框架
- 2D / 3D 图纸输出基础
