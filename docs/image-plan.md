# 图像与草图规划说明

## 1. 文档目标

本文档用于规划本项目后续需要补充到 `images/` 目录中的结构草图、联动示意图、柜体接口图和装配说明图，便于后续绘制 PNG、SVG、CAD 截图或手绘整理版图示。

---

## 2. 推荐图像分类

建议后续在 `images/` 目录中增加以下文件：

```text
images/
├─ overall-structure.png
├─ top-cover-relation.png
├─ platform-linkage-diagram.png
├─ cabinet-opening-layout.png
├─ wiring-layout-diagram.png
├─ maintenance-access-diagram.png
└─ exploded-view.png
```

---

## 3. 推荐草图清单

### 3.1 overall-structure.png
内容建议：
- 整机分层关系
- 顶层 / 滑盖层 / 平台层 / 导轨层 / 电控层
- 柜体外壳与内部机构关系

用途：
- 首页展示
- 总体结构说明
- 向协作者快速介绍项目结构

### 3.2 top-cover-relation.png
内容建议：
- 固定后盖与前滑盖的关闭状态
- 前滑盖收纳至固定后盖下方的开启状态
- 盖板拼缝与顶面关系

用途：
- 说明双段式上盖设计逻辑
- 用于外观和结构沟通

### 3.3 platform-linkage-diagram.png
内容建议：
- 主平台前进方向
- 前滑盖后收方向
- 同步带 / 连杆 / 拉索的联动关系
- 推荐标注“主动件 / 被动件”

用途：
- 联动机构设计说明
- 机械装配和调试参考

### 3.4 cabinet-opening-layout.png
内容建议：
- 顶部开口区域
- 前部可视开口
- 后部线束与散热区域
- 维护入口位置

用途：
- 柜体设计与施工沟通
- 定制柜体对接

### 3.5 wiring-layout-diagram.png
内容建议：
- 电源区、驱动区、ESP32 区、端子排、线槽布局
- 动力线和信号线分区
- 推荐维护区域

用途：
- 电控布置与走线说明
- 现场安装参考

### 3.6 maintenance-access-diagram.png
内容建议：
- 可拆饰板位置
- 电控维护口位置
- 联动张紧调整点
- 原点开关和驱动器接近路径

用途：
- 维护说明
- 安装可达性验证

### 3.7 exploded-view.png
内容建议：
- 基础框架
- 导轨与平台
- 后盖与前滑盖
- 联动机构
- 外部层板
- 电控模块

用途：
- 装配说明
- 模块关系展示
- 后续产品化文档基础

---

## 4. 图像绘制风格建议

### 4.1 建议统一规则
- 尽量统一透视角度
- 关键运动件使用高亮色
- 固定件和可拆件颜色区分
- 尺寸标注与说明文字使用统一样式

### 4.2 标注建议
- 前进方向使用箭头
- 联动方向使用反向箭头
- 关键安装面使用基准线标识
- 可维护区域可用虚线框标出

---

## 5. 推荐绘制顺序

1. `overall-structure.png`
2. `top-cover-relation.png`
3. `platform-linkage-diagram.png`
4. `cabinet-opening-layout.png`
5. `wiring-layout-diagram.png`
6. `exploded-view.png`
7. `maintenance-access-diagram.png`

---

## 6. 推荐文件来源方式

后续图像可来自以下任一方式：
- 手绘草图整理
- PowerPoint / Keynote 绘制
- draw.io / diagrams.net
- Figma
- CAD 截图
- 三维建模爆炸图截图

---

## 7. 后续落地建议

建议先完成：
- 结构总图
- 顶盖关系图
- 联动机构图

因为这三张图对理解整个项目最关键。
