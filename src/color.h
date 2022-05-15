#ifndef _COLOR_H_
#define _COLOR_H_

#define NONE          "\e[0m"          //清除颜色，即之后的打印为正常输出，之前的不受影响
#define BLACK         "\e[0;30m"       //深黑
#define RED           "\e[0;31m"       //深红，暗红
#define GREEN         "\e[0;32m"       //深绿，暗绿
#define BROWN         "\e[0;33m"       //深黄，暗黄
#define YELLOW        "\e[1;33m"       //鲜黄
#define BLUE          "\e[0;34m"       //深蓝，暗蓝
#define PURPLE        "\e[0;35m"       //深粉，暗粉，偏暗紫
#define CYAN          "\e[0;36m"       //暗青色
#define GRAY          "\e[0;37m"       //灰色
#define WHITE         "\e[1;37m"       //白色，字体粗一点，比正常大，比bold小
#define BOLD          "\e[1m"          //白色，粗体
#define UNDERLINE     "\e[4m"          //下划线，白色，正常大小
#define BLINK         "\e[5m"          //闪烁，白色，正常大小
#define REVERSE       "\e[7m"          //反转，即字体背景为白色，字体为黑色


#endif