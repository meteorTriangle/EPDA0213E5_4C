# EPDA0213E5_4C 電子紙顯示器驅動程式

本專案為 EPDA0213E5_4C 電子紙顯示器使用 Raspberry Pi Pico 微控制器實現的驅動程式。此驅動程式支援 4 色顯示（黑、白、紅、黃），並包含將 PNG 圖像轉換為所需點陣圖格式的工具。

## 功能特點

- 支援 4 色電子紙顯示（黑、白、紅、黃）
- 自定義 PNG 轉點陣圖轉換工具
- 依名稱檢索圖像
- 與顯示器的 SPI 通訊介面

## 硬體需求

- Raspberry Pi Pico（或 Pico W）微控制器
- EPDA0213E5_4C 電子紙顯示器
- 連接線

## 接腳連接

![電子紙模組接線圖-HMD](https://hackmd.io/_uploads/rJpVUtgi1l.png)

| Pico 接腳 | 顯示器接腳 | 功能 |
|----------|------------|------|
| GPIO 19  | MOSI       | SPI TX |
| GPIO 18  | CLK        | SPI SCK |
| GPIO 17  | CS         | SPI CS |
| GPIO 16  | DC         | 資料/命令 |
| GPIO 20  | RST        | 重置 |
| GPIO 21  | BUSY       | 忙碌狀態 |

## 專案結構

```
EPDA0213E5_4C/
├── EPDA0213E5_4C.cpp            # 主要應用程式碼
├── extern/
│   └── EPDA0213E5_4C_RPIMCU_driver/
│       ├── epd_lib.h            # 電子紙顯示器函式庫標頭
│       └── epd_lib.cpp          # 電子紙顯示器函式庫實現
├── png2bitmap/
│   ├── png2bit.py               # PNG 轉點陣圖工具
│   ├── png/                     # 原始 PNG 圖像目錄
│   └── my_img__.c               # 生成的點陣圖數據（自動生成）
├── build/                       # 構建目錄（編譯期間創建）
└── CMakeLists.txt               # CMake 構建配置
```

## 設置說明

### 前置條件

1. Raspberry Pi Pico SDK
2. CMake
3. Python 並安裝 OpenCV、NumPy、Matplotlib 和 PIL 函式庫

### 構建專案

1. 將您的 Pico 連接至電腦
2. 複製此存儲庫
3. 開啟 VS Code 編輯器
4. 安裝擴充功能 [**Raspberry Pi Pico**](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
5. 導入 Pi Pico 專案
6. 構建專案
7. 將韌體燒錄到您的 Pico 上：

```bash
picotool load -f EPDA0213E5_4C.uf2
```

## 圖像轉換

要將 PNG 圖像轉換為所需的點陣圖格式：

1. 將您的 PNG 圖像放入 `png2bitmap/png/` 目錄
2. 設定您的專案，轉換程式將自動執行

該程式將生成 `my_img__.c` 檔案，其中包含可被顯示驅動程式使用的點陣圖數據。

## 顏色對應

此顯示器支援以下 RGB 值的 4 色：

- 黑色：(0, 0, 0)
- 白色：(255, 255, 255)
- 紅色：(255, 0, 0)
- 黃色：(255, 255, 0)

準備 PNG 圖像時，請使用這些確切的 RGB 值以確保正確的顏色渲染。

## API 參考

### 主要功能

- `epd_init()`：初始化顯示器
- `epd_write_img(uint32_t* img_src)`：將圖像寫入顯示器
- `getimgbyname(const char* img_name)`：依檔名檢索圖像

## 故障排除

- 如果顯示器顯示不正確的顏色，請確保您的 PNG 使用支援的顏色的確切 RGB 值
- 如果 `getimgbyname()` 返回 NULL，請驗證圖像檔案是否存在於 png 目錄且已正確轉換
- 對於連接問題，請仔細檢查 Pico 和顯示器之間的接腳連接

## 授權

此專案為開源專案，可在 MIT 授權下使用。

| 最後更新日期: 2025-03-03
