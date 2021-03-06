
extern "C"
{
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
#include "MainGUI.h"
#include "stdio.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"
}
namespace GUI
{
    lv_obj_t *btn_SelectMode_PinMap;
    lv_obj_t *btn_SelectMode_values;

    lv_obj_t *pinmapPage;
    ////////////////////////////////
    lv_obj_t *valuePage;
    lv_obj_t *encoderLabelValue;
    lv_obj_t *adcLabelValue;
    lv_obj_t *posLabelValue;
    lv_obj_t *attitudeLabelValue;
    /////////////////////////////////
    lv_obj_t *menuPage;

    lv_obj_t *countlabel; /*Add a label to the button*/

    lv_obj_t *curPage;

    void initMenu();
    void initPinMapPage();
    void initValuePage();
    static void menuBtn_event_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_CLICKED)
        {

            lv_obj_set_hidden(curPage, true);
            lv_obj_set_hidden(menuPage, false);
            // if (lv_obj_is_visible(menuPage))
            // {
            //     lv_obj_set_hidden(menuPage, true);
            // }
            // else
            // {
            //     lv_obj_set_hidden(menuPage, false);
            // }
            // printf("Clicked\n");
        }
    }
    static void btn_SelectMode_PinMap_event_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_CLICKED)
        {
            lv_obj_set_hidden(menuPage, true);
            lv_obj_set_hidden(pinmapPage, false);
            curPage = pinmapPage;
        }
    }
    static void btn_SelectMode_values_event_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_CLICKED)
        {
            lv_obj_set_hidden(menuPage, true);
            lv_obj_set_hidden(valuePage, false);
            curPage = valuePage;
        }
    }
    void initMainGUI()
    {
        initMenu();
        initPinMapPage();
        initValuePage();
        //label

        countlabel = lv_label_create(lv_scr_act(), NULL);
        lv_label_set_text(countlabel, "count");
        lv_obj_set_pos(countlabel, 190, 7);   /*Set its position*/
        lv_obj_set_size(countlabel, 120, 50); /*Set its size*/
    }
    void initMenu()
    {
        menuPage = lv_page_create(lv_scr_act(), NULL);
        lv_obj_set_size(menuPage, 165, 310);
        lv_obj_set_pos(menuPage, 70, 5); /*Set its position*/

        lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button the current screen*/
        lv_obj_set_pos(btn, 5, 5);                         /*Set its position*/
        lv_obj_set_size(btn, 60, 20);                      /*Set its size*/
        // lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/
        lv_obj_set_event_cb(btn, menuBtn_event_handler);
        lv_obj_t *label = lv_label_create(btn, NULL); /*Add a label to the button*/
        lv_label_set_text(label, "menu");             /*Set the labels text*/
    }
    void initPinMapPage()
    {
        btn_SelectMode_PinMap = lv_btn_create(menuPage, NULL); /*Add a button the current screen*/
        lv_obj_set_pos(btn_SelectMode_PinMap, 0, 0);           /*Set its position*/
        lv_obj_set_size(btn_SelectMode_PinMap, 130, 20);       /*Set its size*/
        // lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/
        lv_obj_set_event_cb(btn_SelectMode_PinMap, btn_SelectMode_PinMap_event_handler);
        lv_obj_t *label2 = lv_label_create(btn_SelectMode_PinMap, NULL); /*Add a label to the button*/
        lv_label_set_text(label2, "PinMap");

        pinmapPage = lv_page_create(lv_scr_act(), NULL);
        lv_obj_set_size(pinmapPage, 230, 285);
        lv_obj_set_pos(pinmapPage, 5, 30); /*Set its position*/
        // lv_obj_align(page, NULL, LV_ALIGN_CENTER, 0, 0);

        lv_obj_t *pinmap1 = lv_label_create(pinmapPage, NULL); /*Add a label to the button*/
        lv_label_set_text(pinmap1, "E1 E0\nB9 B8\nB7 B6\nB5 B4\nB3 D7\nD6 D5\nD4 D3\nD2 D1\nD0 C12\nC11 C10\nA15 A12\nA11 A10\nA9 A8\nC9 C8\nC7 C6\nD15 D14\nD13 D12\nD11 D10\nD9 D8\n\GND \GND\n3V3 3V3\n5V 5V");
        // lv_obj_set_pos(pinmap1, 5,30);   /*Set its position*/
        // lv_obj_set_size(pinmap1, 120, 40); /*Set its size*/

        lv_obj_t *pinmap2 = lv_label_create(pinmapPage, NULL); /*Add a label to the button*/
        lv_label_set_text(pinmap2, "E3 E2\nE5 E4\nC13 E6\nC1 C0\nC3 C2\nA1 A0\nA3 A2\nA5 A4\nA7 A6\nC5 C4\nB1 B0\nE7 B2\nE9 E8\nE11 E10\nE13 B12\nE15 E14\nB11 B10\nB13 B12\nB15 B14\n5V 5V\nGND GND\n3V3 3V3");
        lv_obj_set_pos(pinmap2, 105, 0); /*Set its position*/

        lv_obj_set_hidden(pinmapPage, true);

        curPage = pinmapPage;
        // lv_obj_set_hidden(pinmap1, true);
    }
    void initValuePage()
    {
        btn_SelectMode_values = lv_btn_create(menuPage, NULL); /*Add a button the current screen*/
        lv_obj_set_pos(btn_SelectMode_values, 0, 30);          /*Set its position*/
        lv_obj_set_size(btn_SelectMode_values, 130, 20);       /*Set its size*/
        // lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/
        lv_obj_set_event_cb(btn_SelectMode_values, btn_SelectMode_values_event_handler);
        lv_obj_t *label2 = lv_label_create(btn_SelectMode_values, NULL); /*Add a label to the button*/
        lv_label_set_text(label2, "Values");

        valuePage = lv_page_create(lv_scr_act(), NULL);
        lv_obj_set_size(valuePage, 230, 285);
        lv_obj_set_pos(valuePage, 5, 30); /*Set its position*/
        // lv_obj_align(page, NULL, LV_ALIGN_CENTER, 0, 0);

        lv_obj_t *pinmap1 = lv_label_create(valuePage, NULL); /*Add a label to the button*/
        lv_label_set_text(pinmap1, "Values:");

        encoderLabelValue = lv_label_create(valuePage, NULL); /*Add a label to the button*/
        lv_label_set_text(encoderLabelValue, "Encoder");
        lv_obj_set_pos(encoderLabelValue, 5, 20);

        adcLabelValue = lv_label_create(valuePage, NULL); /*Add a label to the button*/
        lv_label_set_text(adcLabelValue, "Adc");
        lv_obj_set_pos(adcLabelValue, 5, 80);

        posLabelValue = lv_label_create(valuePage, NULL); /*Add a label to the button*/
        lv_label_set_text(posLabelValue, "pos");
        lv_obj_set_pos(posLabelValue, 5, 100);

        attitudeLabelValue= lv_label_create(valuePage, NULL); /*Add a label to the button*/
        lv_label_set_text(attitudeLabelValue, "pos");
        lv_obj_set_pos(attitudeLabelValue, 5, 130);

        lv_obj_set_hidden(valuePage, true);
    }
    void updateRuningTime(int time)
    {
        {
            char strbuf[20];
            sprintf(strbuf, "t%d", time);
            lv_label_set_text(countlabel, strbuf);
        }
    }
    void updateEncoder(int E1, int E1_d,int E2, int E2_d)
    {
        {
            char strbuf[40];
            snprintf(strbuf, 40, "Encoder:\n  %d %d\n  %d %d", E1, E1_d,E2,E2_d);
            lv_label_set_text(encoderLabelValue, strbuf);
        }
    }
    void updateAdc( float value)
    {
        {
            char strbuf[20];
            // char * pre="Adc:";
            // pa_Convert_Float2Str(value,strbuf,20,5);
            // char * add=(char *) pa_MEM_CUSTOM_ALLOC(strlen(pre) + strlen(strbuf)+12);
            // // snprintf(strbuf,20, "Adc:%d", (int)value);
            // sprintf(add, "%s%6d\n%s", pre,(int) value,strbuf);
            pa_snprintf(strbuf,20,"adc:%05.3f",value);
            lv_label_set_text(adcLabelValue, strbuf);
            // pa_MEM_CUSTOM_FREE(add);
        }
    }

    void updateTouchXY(int x,int y){
        {
            char strbuf[20];
            // char * pre="Adc:";
            // pa_Convert_Float2Str(value,strbuf,20,5);
            // char * add=(char *) pa_MEM_CUSTOM_ALLOC(strlen(pre) + strlen(strbuf)+12);
            // // snprintf(strbuf,20, "Adc:%d", (int)value);
            // sprintf(add, "%s%6d\n%s", pre,(int) value,strbuf);
            pa_snprintf(strbuf,20,"pos:%d\n%d",x,y);
            lv_label_set_text(posLabelValue, strbuf);
            // pa_MEM_CUSTOM_FREE(add);
        }
    }
    void updateAttitude(float x,float y,float z){
        {
            char strbuf[30];
            // char * pre="Adc:";
            // pa_Convert_Float2Str(value,strbuf,20,5);
            // char * add=(char *) pa_MEM_CUSTOM_ALLOC(strlen(pre) + strlen(strbuf)+12);
            // // snprintf(strbuf,20, "Adc:%d", (int)value);
            // sprintf(add, "%s%6d\n%s", pre,(int) value,strbuf);
            pa_snprintf(strbuf,30,"att:%3.2f %3.2f %3.2f",x,y,z);
            lv_label_set_text(attitudeLabelValue, strbuf);
            // pa_MEM_CUSTOM_FREE(add);
        }
    }

} // namespace GUI
