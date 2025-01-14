/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "gpio.h"
#include "i2c.h"
#include "tim.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "button/button.h"
#include "menu_nest/menu.h"
#include "menu_nest_tiny/item_auto_variable.h"
#include "menu_nest_tiny/item_cstr.h"
#include "menu_nest_tiny/item_page_entrance.h"
#include "menu_nest_tiny/item_static_variable.h"
#include "menu_nest_tiny/page_base.h"
#include "menu_nest_tiny/page_hibernate.h"
#include "ssd1306/ssd1306.h"
#include "ssd1306/ssd1306_fonts.h"
#include "ssd1306/ssd1306_tests.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/**
 * ************************************************************************
 * 说明：为了演示方便，这里的很多代码是直接写在了main.c中。
 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// 这里是菜单的构建过程。
// 不一定要将所有的构建全部放到一个函数中，也可以分开构建。例如在某模块的初始化函数中构建该模块的部分。
void menu_init() {
    MN_page *p_main_page = create_base_page("mainPage");

    // 页面1
    MN_page *p_int_page = create_base_page("page1");

    // 页面1的跳转入口
    MN_item *p_int_page_entrance = create_item_page_entrance("en_pageInts", p_int_page);

    // 将页面1的跳转入口添加到主页面中
    MN_page_add_item(p_main_page, p_int_page_entrance);

    // 下面是一些静态变量的item被添加到页面1中
    // 这里不一定必须是静态变量，也可以是全局变量。核心是变量的生命周期要大于菜单的生命周期。
    static int8_t varI8 = 6;
    // 创建item
    MN_item *p_var_i8 = create_item_static_variable("int8", &varI8, TYPE_I8);
    // 将item添加到页面1中
    MN_page_add_item(p_int_page, p_var_i8);

    static int16_t varI16 = 666;
    MN_item *p_var_i16 = create_item_static_variable("int16", &varI16, TYPE_I16);
    MN_page_add_item(p_int_page, p_var_i16);

    static int32_t varI32 = 666;
    MN_item *p_var_i32 = create_item_static_variable("int32", &varI32, TYPE_I32);
    MN_page_add_item(p_int_page, p_var_i32);

    static int64_t varI64 = 666;
    MN_item *p_var_i64 = create_item_static_variable("int64", &varI64, TYPE_I64);
    MN_page_add_item(p_int_page, p_var_i64);

    // uint页面
    MN_page *p_uint_page = create_base_page("page_uint");

    // uint页面的跳转入口
    MN_item *p_uint_page_entrance = create_item_page_entrance("en_pageUints", p_uint_page);
    // 将uint页面的跳转入口添加到主页面中
    MN_page_add_item(p_main_page, p_uint_page_entrance);

    static uint8_t varU8 = 6;
    MN_item *p_var_u8 = create_item_static_variable("uint8", &varU8, TYPE_U8);
    MN_page_add_item(p_uint_page, p_var_u8);

    static uint16_t varU16 = 666;
    MN_item *p_var_u16 = create_item_static_variable("uint16", &varU16, TYPE_U16);
    MN_page_add_item(p_uint_page, p_var_u16);

    static uint32_t varU32 = 666;
    MN_item *p_var_u32 = create_item_static_variable("uint32", &varU32, TYPE_U32);
    MN_page_add_item(p_uint_page, p_var_u32);

    static uint64_t varU64 = 666;
    MN_item *p_var_u64 = create_item_static_variable("uint64", &varU64, TYPE_U64);
    MN_page_add_item(p_uint_page, p_var_u64);

    // 页面3，有float和bool以及cstr
    MN_page *p_float_page = create_base_page("page_flt");
    MN_item *p_flt_page_entrance = create_item_page_entrance("en_pageFloats", p_float_page);
    MN_page_add_item(p_main_page, p_flt_page_entrance);

    static float varF32 = 3.1415926f;
    MN_item *p_var_f32 = create_item_static_variable("f32", &varF32, TYPE_F32);
    MN_page_add_item(p_float_page, p_var_f32);
    MN_page_add_item(p_main_page, p_var_f32);

    static double varF64 = 123.45678912345;
    MN_item *p_var_f64 = create_item_static_variable("f64", &varF64, TYPE_F64);
    MN_page_add_item(p_float_page, p_var_f64);
    MN_page_add_item(p_main_page, p_var_f64);

    static bool varBool = true;
    MN_item *p_var_bool = create_item_static_variable("bool", &varBool, TYPE_BOOL);
    MN_page_add_item(p_float_page, p_var_bool);
    MN_page_add_item(p_main_page, p_var_bool);

    static char *str = "Im a cstr 1 22 333 4444 55555 666666 !";
    MN_item *p_var_cstr = create_item_static_variable("cstr", str, TYPE_CSTR);
    MN_page_add_item(p_float_page, p_var_cstr);
    MN_page_add_item(p_main_page, p_var_cstr);

    // 初始化菜单，并且指定主页面
    MN_menu_init(p_main_page);
}

// 这些是按键库的回调，要求按键按下时返回1，松开时返回0
static uint8_t query_func_0() {
    return !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0);
}
static uint8_t query_func_1() {
    return !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1);
}
static uint8_t query_func_2() {
    return !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);
}
static uint8_t query_func_3() {
    return !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3);
}

#include "menu_nest_tiny/input_def.h"

// 这些是按键的事件处理回调函数，在这里是向菜单输入事件
static void button_click_event_0() {
    MN_menu_input(BUTTON_0_CLICK);
}
static void button_click_event_1() {
    MN_menu_input(BUTTON_1_CLICK);
}
static void button_click_event_2() {
    MN_menu_input(BUTTON_2_CLICK);
}
static void button_click_event_3() {
    MN_menu_input(BUTTON_3_CLICK);
}

static void button_long_press_event_0() {
    MN_menu_input(BUTTON_0_LONG_PRESS);
}

static void button_long_press_event_1() {
    MN_menu_input(BUTTON_1_LONG_PRESS);
}

// 这里是按键库的接口对接
void button_config() {
    set_button_query_func(0, query_func_0);
    set_button_query_func(1, query_func_1);
    set_button_query_func(2, query_func_2);
    set_button_query_func(3, query_func_3);

    set_button_event_func(0, CLICK, button_click_event_0);
    set_button_event_func(1, CLICK, button_click_event_1);
    set_button_event_func(2, CLICK, button_click_event_2);
    set_button_event_func(3, CLICK, button_click_event_3);

    set_button_event_func(0, LONG_TOUCH, button_long_press_event_0);
    set_button_event_func(1, LONG_TOUCH, button_long_press_event_1);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_TIM2_Init();
    /* USER CODE BEGIN 2 */
    button_init();        // 初始化按键库
    button_config();      // 配置按键的输入和事件处理
    menu_init();          // 初始化菜单
    ssd1306_Init();       // 初始化OLED
    ssd1306_Fill(Black);  // 清屏

    /*使能定时器中断*/
    HAL_TIM_Base_Start_IT(&htim2); // 用来处理按键的定时器

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        MN_menu_handle_input_queue();  // 处理菜单的输入队列  
        MN_menu_rendering();  // 渲染菜单
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    static unsigned char ledState = 0;
    if (htim == (&htim2)) {
        button_turn_query(); // 定时处理按键状态。
    }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
