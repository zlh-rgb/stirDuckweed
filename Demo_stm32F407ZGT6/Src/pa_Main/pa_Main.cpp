extern "C"
{
#include "pa_Main.h"
// #include "pa_CommonLib/src/service/display/st7789/lcd.h"
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/service/display/ili9341/pa_ILI9341.h"

#include "pa_CommonLib/src/service/input/touchScreen/pa_touchScreen.h"
#include "pa_CommonLib/src/service/TI_Chips/Ads_112c04/Ads_112c04.h"
#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
#include "pa_Lvgl/pa_Lvgl_C.h"
#include "stdio.h"
#include "pa_Lvgl/GUIs/MainGUI/MainGUI.h"
#include "pa_CommonLib/src/drv/pa_PWM/pa_PWM.h"
#include "pa_Motor/pa_Motor.h"
#include "pa_CommonLib/src/service/sensors/attitude/bno055/bno055.h"
#include "pa_CommonLib/src/service/sensors/other/GY906/GY906.h"

    // #include "pa_CommonLib/src/service/display/ssd1306/pa_oled.h"
}
#include "pa_CommonLib/src/service/sensors/distance/VL53L0X/VL53L0X.h"
int cnt = 0;
int run = 0;
int encoder1 = 0;
int encoder1_delta = 0;
int encoder2 = 0;
int encoder2_delta = 0;
extern TIM_HandleTypeDef htim2, htim3, htim4, htim5;
//
void pa_Main()
{
    pa_PWM::initPWMs();
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(&htim2);

    // HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,(GPIO_PinState)0);
    // LCD_Init();
    // LCD_Fill(0,0,100,100,GREEN);
    // LCD_ShowString(0,0,(const unsigned char *)"helloWorld",GREEN,BLACK,12,0);
    pa_ILI9341 &ili9341 = pa_ILI9341::instance;
    pa_touchScreen &touch = pa_touchScreen::instance;
    // Ads_112c04 &ads112c04 = Ads_112c04::instance;

    // pa_BNO055_init();
    // OLED_Init(Protocal::Protocal_IIC);
    // OLED_ShowString(0,0,"helloWorld",12);
    touch.init(240, 320, 235, 3800, 451, 3884, 30);

    // pa_delayMs(100);
    ili9341.init(pa_ILI9341::Rotation::Rotation_VERTICAL_2);
    // pa_delayMs(100);
    ili9341.flush(0, 0, 235, 100, 0xff00);
    ili9341.flush(0, 101, 235, 150, 0xff00);
    // pa_delayMs(100);
    // bool a = false;

    //    ads112c04         ////////////////////////////////////////////////////////////////////////////////////
    // ads112c04.init(Ads_112c04::AxState::DGND,
    //                Ads_112c04::AxState::DGND);
    // ads112c04.configRegister0(Ads_112c04::Gain::GAIN_1);
    // ads112c04.configRegister1(Ads_112c04::SpeedOfSample::SPS_1000,
    //                           Ads_112c04::Mode::Mode_Normal,
    //                           Ads_112c04::ConvMode::Continuous);
    // ads112c04.startConv();
    //////////////////////////////////////////////////////////////////////////////////////
    if (!VL53L0X::instance.init())
    {

        while (1)
        {
        }
    }
    VL53L0X::instance.startContinuous();
    lv_init();
    pa_Lvgl_init();
    //button
    GUI::initMainGUI();

    // pa_delayMs(100);

    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1000);
    // for (;;){
    // }
    // touch.Hardware_SetCS(0);
    run = 0;
    encoder1 = encoder2 = 0;
    encoder1_delta = encoder2_delta = 0;
    for (;;)
    {
        //        run++;
        // lv_tick_inc(10);
        //    motor         ////////////////////////////////////////////////////////////////////////////////////
        pa_Motor::setSpeed(0, cnt * 1.0 / 1000);
        pa_Motor::setSpeed(1, cnt * 1.0 / 1000);
        //////////////////////////////////////////////////////////////////////////////////////

        //    bno055         ////////////////////////////////////////////////////////////////////////////////////
        // bno055_vector_t att=pa_BNO055_getVector();
        // GUI::updateAttitude(att.x,att.y,att.z);
        //////////////////////////////////////////////////////////////////////////////////////

        //    ads112c04         ////////////////////////////////////////////////////////////////////////////////////
        // float adc=0.5;
        // if(!ads112c04.getDrdyState()){
        //     adc=ads112c04.readADC();

        GUI::updateAdc(VL53L0X::instance.readRangeContinuousMillimeters());
        // }
        //////////////////////////////////////////////////////////////////////////////////////

        { //lv
            GUI::updateRuningTime(run);
            GUI::updateEncoder(encoder1, encoder1_delta, encoder2, encoder2_delta);

            lv_task_handler(); //lvgl刷新显示内容
        }

        // if(touch.isPressed()){
        //     GUI::updateRuningTime(1);
        // }else{
        //     GUI::updateRuningTime(0);
        // }
        pa_delayMs(10);
        // if (touch.isPressed())
        // {
        //     lv_label_set_text(label, "Pressed");
        // }
        // else
        // {
        //     lv_label_set_text(label, "not Pressed");
        // }
    }
}
extern uint64_t pa_milliCnt;
void tim_1ms_tick()
{
    pa_milliCnt++;
    cnt++;
    if (cnt == 1000)
    {
        cnt = 0;
        run++;
    }

    if (cnt % 50 == 0)
    {
        encoder1_delta = (short)(__HAL_TIM_GET_COUNTER(&htim4));
        encoder2_delta = (short)(__HAL_TIM_GET_COUNTER(&htim5));
        TIM4->CNT = 0;
        TIM5->CNT = 0;
        encoder1 += encoder1_delta;
        encoder2 += encoder2_delta;
    }

    lv_tick_inc(1);
}
