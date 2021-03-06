
extern "C"
{
#include "pa_Lvgl.h"
#include "pa_CommonLib/src/service/display/ili9341/pa_ILI9341.h"

#include "pa_CommonLib/src/service/input/touchScreen/pa_touchScreen.h"
#include <stdlib.h>
#include "GUIs/MainGUI/MainGUI.h"
}
// void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
// bool my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);

// void pa_Lvgl_init()
// {
//     static lv_disp_buf_t disp_buf;
//     static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10]; /*Declare a buffer for 1/10 screen size*/
//     static lv_indev_drv_t indev_drv;                             /*Descriptor of a input device driver*/
//     static lv_disp_drv_t disp_drv;                                      /*Descriptor of a display driver*/

//     lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10); /*Initialize the display buffer*/

//     lv_disp_drv_init(&disp_drv);       /*Basic initialization*/
//     disp_drv.flush_cb = my_disp_flush; /*Set your driver function*/
//     disp_drv.buffer = &disp_buf;       /*Assign the buffer to the display*/
//     lv_disp_drv_register(&disp_drv);   /*Finally register the driver*/

//     lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
//     indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
//     indev_drv.read_cb = my_touchpad_read;   /*Set your driver function*/
//     lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/
// }
// unsigned char arr1[100];
void pa_Lvgl_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    pa_ILI9341::instance.setAddress(area->x1, area->y1, area->x2, area->y2);
    int32_t x, y;
    pa_ILI9341::instance.setDC(1);
    pa_ILI9341::instance.setCS(0);
    int cnt = 0;
    int step = 0;
    // unsigned char * arr=(unsigned char *)pvPortMalloc((area->x2-area->x1)*(area->x2-area->x1)*2);
    // vPortFree(arr);
    int left = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1) * 2;
    int total = left / 500;
    left = left % 500;
    for (y = area->y1; y <= area->y2; y++)
    {
        for (x = area->x1; x <= area->x2; x++)
        {

            pa_ILI9341::instance.pa_ILI9341_burst_buffer[cnt] = color_p->full >> 8;
            pa_ILI9341::instance.pa_ILI9341_burst_buffer[cnt + 1] = color_p->full;
            cnt += 2;

            if (cnt == 500)
            {
                step++;
                cnt = 0;
                pa_spiTransmit(pa_ILI9341::instance.pa_ILI9341_burst_buffer, 500);
            }
            else if (step == total && cnt == left)
            {
                pa_spiTransmit(pa_ILI9341::instance.pa_ILI9341_burst_buffer, left);
                break;
            }
            // unsigned char buffer[2];
            // buffer[0] = color_p->full >> 8;
            // buffer[1] = color_p->full;
            // if((area->x2-area->x1)+1<100){
            //     arr1[x+y*(area->x2-area->x1)]=color_p->full>>8;
            //     arr1[x+y*(area->x2-area->x1)+1]=color_p->full;
            // }

            // pa_spiTransmit(buffer, 2);
            // pa_ILI9341::instance.flush(x, y, x, y, color_p->full);
            // set_pixel(x, y, *color_p); /* Put a pixel to the display.*/
            color_p++;
        }
    }

    pa_ILI9341::instance.setCS(1);
    lv_disp_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

void pa_Lvgl_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{

    data->state = pa_touchScreen::instance.isPressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    if (data->state == LV_INDEV_STATE_PR)
    {
        uint16_t coord[2];
        pa_touchScreen::instance.readRaw(coord);
        GUI::updateTouchXY(coord[0],coord[1]);
        pa_touchScreen::instance.turnRawToScreen(coord);
        data->point.x = coord[0];
        data->point.y = coord[1];
        // touchpad_get_xy(&data->point.x, &data->point.y);
    }

    // return false; /*Return `false` because we are not buffering and no more data to read*/
}