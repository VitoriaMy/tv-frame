# 图像目录与绘图规范

## 1. 文档目标

本文档用于规范 `images/` 目录中的图像命名、绘制风格、导出格式和更新方式，便于后续统一管理结构草图、装配图、联动示意图和柜体接口图。

---

## 2. 推荐目录内容

建议后续在 `images/` 目录中逐步补充以下文件：

```text
images/
├─ README.md
├─ overall-structure.png
├─ top-cover-relation.png
├─ platform-linkage-diagram.png
├─ cabinet-opening-layout.png
├─ wiring-layout-diagram.png
├─ maintenance-access-diagram.png
└─ exploded-view.png
```

---

## 3. 命名规则

- 使用小写英文
- 单词之间使用连字符 `-`
- 优先采用“主题 + 类型”命名方式
- 避免中文文件名、空格和版本号直接写进文件名

示例：
- `overall-structure.png`
- `platform-linkage-diagram.svg`
- `cabinet-opening-layout.png`

若需要版本区分，建议通过 Git 提交历史管理，而不是频繁改文件名。

---

## 4. 绘图风格建议

### 4.1 视角建议
- 总体结构图：等轴测视角
- 顶盖关系图：顶视图 + 侧剖图
- 联动图：侧视图或俯视示意图
- 柜体开口图：顶视图 + 前视图
- 维护图：前视图 / 后视图 / 分层剖视图

### 4.2 颜色建议
- 运动平台：蓝色
- 前滑盖：橙色
- 固定后盖：深灰色
- 基础框架：黑色或深灰色
- 电控区：绿色或青色
- 柜体边界：浅灰色
- 维护区域：虚线框 + 浅色高亮

### 4.3 标注建议
- 平台前进方向：实心箭头
- 联动反向关系：反向箭头
- 安装基准：细虚线或基准线符号
- 维护开口：虚线框
- 模块名称：统一放在图外侧或统一编号后配图例

---

## 5. 导出格式建议

### 5.1 推荐格式
- `PNG`：用于 README 和普通文档预览
- `SVG`：用于持续编辑和小改动迭代
- `PDF`：用于打印或评审归档（可选）

### 5.2 推荐输出尺寸
- README 展示图：宽度建议 1600 px 左右
- 普通文档配图：宽度建议 1200 px 左右
- 若使用 SVG，可无损放大并保留一份编辑源

---

## 6. 更新规则建议

每次新增或更新图像时，建议同步确认：
- 文件命名是否符合规范
- 是否与 `docs/image-plan.md` 中的目标一致
- 是否需要在 `README.md` 中新增引用
- 是否需要同步更新相关文档中的说明文字

---

## 7. 优先绘制顺序

建议按以下顺序落地图像：

1. `overall-structure.png`
2. `top-cover-relation.png`
3. `platform-linkage-diagram.png`
4. `cabinet-opening-layout.png`
5. `wiring-layout-diagram.png`
6. `exploded-view.png`
7. `maintenance-access-diagram.png`

---

## 8. 推荐绘图工具

可选工具包括：
- draw.io / diagrams.net
- Figma
- PowerPoint / Keynote
- CAD 软件截图
- 三维建模软件截图

建议：
- 初版优先快速出图
- 定版后再替换为更标准的 CAD / 三维截图版本
