# 图像与草图规划说明

## 1. 文档目标

本文档用于规划本项目后续需要补充到 `images/` 目录中的结构草图、联动示意图、柜体接口图和装配说明图，便于后续绘制 PNG、SVG、CAD 截图或手绘整理版图示，并作为实际绘图执行时的统一规范依据。

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
**建议视角：**
- 右前上方等轴测视角

**必须包含：**
- 整机分层关系
- 顶层 / 滑盖层 / 平台层 / 导轨层 / 电控层
- 柜体外壳与内部机构关系

**必须标注：**
- 平台前进方向
- 前滑盖后收方向
- 柜体外边界
- 电控区位置

**推荐输出格式：**
- PNG 用于 README 展示
- SVG 用于后续迭代编辑

**关联文档：**
- `README.md`
- `docs/design-drawings.md`
- `docs/cabinet-integration.md`

**用途：**
- 首页展示
- 总体结构说明
- 向协作者快速介绍项目结构

### 3.2 top-cover-relation.png
**建议视角：**
- 顶视图 + 侧剖示意组合

**必须包含：**
- 固定后盖与前滑盖的关闭状态
- 前滑盖收纳至固定后盖下方的开启状态
- 盖板拼缝与顶面关系

**必须标注：**
- 固定后盖
- 前滑盖
- 闭合拼缝
- 收纳路径

**推荐输出格式：**
- PNG + SVG

**关联文档：**
- `docs/appearance-dimensions.md`
- `docs/design-drawings.md`
- `docs/assembly-guide.md`

**用途：**
- 说明双段式上盖设计逻辑
- 用于外观和结构沟通

### 3.3 platform-linkage-diagram.png
**建议视角：**
- 侧视图或俯视透明示意图

**必须包含：**
- 主平台前进方向
- 前滑盖后收方向
- 同步带 / 连杆 / 拉索的联动关系
- “主动件 / 被动件”区分

**必须标注：**
- 平台
- 前滑盖
- 联动路径
- 张紧点或关键连接点

**推荐输出格式：**
- SVG 优先，便于后期改图

**关联文档：**
- `docs/mechanism-linkage.md`
- `docs/design-drawings.md`

**用途：**
- 联动机构设计说明
- 机械装配和调试参考

### 3.4 cabinet-opening-layout.png
**建议视角：**
- 顶视图 + 前视图

**必须包含：**
- 顶部开口区域
- 前部可视开口
- 后部线束与散热区域
- 维护入口位置

**必须标注：**
- 安装基准边
- 检修口位置
- 散热区
- 线束进出方向

**推荐输出格式：**
- PNG + SVG

**关联文档：**
- `docs/cabinet-integration.md`
- `docs/drawing-parameters.md`

**用途：**
- 柜体设计与施工沟通
- 定制柜体对接

### 3.5 wiring-layout-diagram.png
**建议视角：**
- 顶视布置图

**必须包含：**
- 电源区、驱动区、ESP32 区、端子排、线槽布局
- 动力线和信号线分区
- 推荐维护区域

**必须标注：**
- 动力线走向
- 信号线走向
- 接地位置
- 检修可达区域

**推荐输出格式：**
- PNG

**关联文档：**
- `docs/wiring-diagram.md`
- `docs/design-drawings.md`

**用途：**
- 电控布置与走线说明
- 现场安装参考

### 3.6 maintenance-access-diagram.png
**建议视角：**
- 前视图 + 后视图或分层剖视图

**必须包含：**
- 可拆饰板位置
- 电控维护口位置
- 联动张紧调整点
- 原点开关和驱动器接近路径

**必须标注：**
- 拆装路径
- 调节点
- 检修区域边界

**推荐输出格式：**
- PNG

**关联文档：**
- `docs/assembly-guide.md`
- `docs/cabinet-integration.md`
- `docs/troubleshooting.md`

**用途：**
- 维护说明
- 安装可达性验证

### 3.7 exploded-view.png
**建议视角：**
- 爆炸等轴测视角

**必须包含：**
- 基础框架
- 导轨与平台
- 后盖与前滑盖
- 联动机构
- 外部层板
- 电控模块

**必须标注：**
- 模块名称
- 装配顺序编号
- 主要安装方向

**推荐输出格式：**
- PNG 用于说明
- SVG 或 CAD 截图用于持续修订

**关联文档：**
- `docs/assembly-guide.md`
- `docs/design-drawings.md`

**用途：**
- 装配说明
- 模块关系展示
- 后续产品化文档基础

---

## 4. 图像绘制风格建议

### 4.1 建议统一规则
- 尽量统一透视角度。
- 关键运动件使用高亮色。
- 固定件和可拆件颜色区分。
- 尺寸标注与说明文字使用统一样式。
- 柜体边界建议使用浅灰色或低饱和辅助线。

### 4.2 标注建议
- 平台前进方向使用实心箭头。
- 联动方向使用反向箭头。
- 关键安装面使用基准线标识。
- 可维护区域可用虚线框标出。
- 尺寸和说明文字建议统一使用无衬线字体。

### 4.3 颜色建议
- 运动平台：蓝色
- 前滑盖：橙色
- 固定后盖：深灰色
- 基础框架：黑色或深灰
- 电控区：绿色或青色
- 柜体边界：浅灰色

---

## 5. 推荐绘制顺序

1. `overall-structure.png`
2. `top-cover-relation.png`
3. `platform-linkage-diagram.png`
4. `cabinet-opening-layout.png`
5. `wiring-layout-diagram.png`
6. `exploded-view.png`
7. `maintenance-access-diagram.png`

说明：
- 前三张图最适合优先落地，因为它们最能快速帮助理解整体方案。
- 若时间有限，建议至少先完成结构总图、顶盖关系图和联动机构图。

---

## 6. 推荐文件来源方式

后续图像可来自以下任一方式：
- 手绘草图整理
- PowerPoint / Keynote 绘制
- draw.io / diagrams.net
- Figma
- CAD 截图
- 三维建模爆炸图截图

建议：
- 初版优先用 draw.io / Figma 快速形成统一风格图。
- 定版后再替换为 CAD 或三维建模截图版本。

---

## 7. 图像执行任务卡建议

后续每张图建议至少补充以下执行字段：
- 绘制状态：未开始 / 草图中 / 已完成 / 待修订
- 负责人
- 使用软件
- 最近更新日期
- 是否已同步 README 或文档引用

这样有利于多人协作和版本管理。

---

## 8. 后续落地建议

建议先完成：
- 结构总图
- 顶盖关系图
- 联动机构图

因为这三张图对理解整个项目最关键。
