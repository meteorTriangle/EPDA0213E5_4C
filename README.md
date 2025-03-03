# EPDA0213E5_4C E-Paper Display Driver

This project implements a driver for the EPDA0213E5_4C e-paper display using a Raspberry Pi Pico microcontroller. The driver supports 4-color display (black, white, red, and yellow) and includes tools for converting PNG images to the required bitmap format.

## Features

- 4-color e-paper display support (black, white, red, yellow)
- Custom PNG to bitmap conversion utility
- Image retrieval by name
- SPI communication interface with the display

## Hardware Requirements

- Raspberry Pi Pico (or Pico W) microcontroller
- EPDA0213E5_4C E-Paper Display
- Connecting wires

## Pin Connections

![電子紙模組接線圖-HMD](https://hackmd.io/_uploads/rJpVUtgi1l.png)

| Pico Pin | Display Pin | Function |
|----------|-------------|----------|
| GPIO 19  | MOSI        | SPI TX   |
| GPIO 18  | CLK         | SPI SCK  |
| GPIO 17  | CS          | SPI CS   |
| GPIO 16  | DC          | Data/Command |
| GPIO 20  | RST         | Reset    |
| GPIO 21  | BUSY        | Busy Status |

## Project Structure

```
EPDA0213E5_4C/
├── EPDA0213E5_4C.cpp            # Main application code
├── extern/
│   └── EPDA0213E5_4C_RPIMCU_driver/
│       ├── epd_lib.h            # E-paper display library header
│       └── epd_lib.cpp          # E-paper display library implementation
├── png2bitmap/
│   ├── png2bit.py               # PNG to bitmap conversion tool
│   ├── png/                     # Directory for source PNG images
│   └── my_img__.c               # Generated bitmap data (auto-generated)
├── build/                       # Build directory (created during compilation)
└── CMakeLists.txt               # CMake build configuration
```

## Setup Instructions

### Prerequisites

1. Raspberry Pi Pico SDK
2. CMake
3. Python with OpenCV, NumPy, Matplotlib, and PIL libraries

### Building the Project

1. Connect your Pico to your computer
2. Clone this repository
3. Open VS code editor
4. install extension [**Raspberry Pi Pico**](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
5. import the pi pico project
6. build the project
7. Flash the firmware to your Pico:

```bash
picotool load -f EPDA0213E5_4C.uf2
```

## Image Conversion

To convert PNG images to the required bitmap format:

1. Place your PNG images in the `png2bitmap/png/` directory
2. config your project, and the conversion program will run automaticly

The program will generate `my_img__.c` with the bitmap data that can be used by the display driver.

## Color Mapping

The display supports 4 colors with the following RGB values:

- Black: (0, 0, 0)
- White: (255, 255, 255)
- Red: (255, 0, 0)
- Yellow: (255, 255, 0)

When preparing PNG images, use these exact RGB values for proper color rendering.

## API Reference

### Main Functions

- `epd_init()`: Initialize the display
- `epd_write_img(uint32_t* img_src)`: Write an image to the display
- `getimgbyname(const char* img_name)`: Retrieve an image by its filename

## Troubleshooting

- If the display shows incorrect colors, ensure your PNG uses the exact RGB values for the supported colors
- If `getimgbyname()` returns NULL, verify the image file exists in the png directory and was properly converted
- For connection issues, double-check the pin connections between the Pico and display

## License

This project is open-source and available under the MIT License.
