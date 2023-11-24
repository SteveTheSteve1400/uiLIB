#include "pidView.hpp"
#include "api.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/misc/lv_color.h"

void rd::PIDView::eventHandler( lv_obj_t * obj,lv_event_t * event){
    lv_event_code_t code = lv_event_get_code(event);
    if(code == LV_EVENT_CLICKED){
        if(obj == imgButtonPDec){
            kP -= 0.1;
        }
        else if(obj == imgButtonPInc){
            kP += 0.1;
        }
        else if(obj == imgButtonIDec){
            kI -= 0.1;
        }
        else if(obj == imgButtonIInc){
            kI += 0.1;
        }
        else if(obj == imgButtonDDec){
            kD -= 0.1;
        }
        else if(obj == imgButtonDInc){
            kD += 0.1;
        }
    }


}

rd::PIDView::PIDView() {
    //creating view named pidview
    this->view = rd_view_create("pidview");

    //setting variables
    this->kP = 0;
    this->kI = 0;
    this->kD = 0;

    //creating chart
    chart = lv_chart_create(view->obj);
    lv_obj_set_size(chart, 200, 200);
    lv_obj_align(chart, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart, 0, 100,0);
    lv_chart_set_point_count(chart, 100);
    lv_chart_set_div_line_count(chart, 0, 0);
    
    //creating chart series
    seriesP = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    seriesD = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE),LV_CHART_AXIS_PRIMARY_Y);
    seriesTarg = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN),LV_CHART_AXIS_PRIMARY_Y);
    seriesCur = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW),LV_CHART_AXIS_PRIMARY_Y);

    //creating still labels
    labelTitle = lv_label_create(view->obj);
    lv_label_set_text(labelTitle, "PID");

    labelP = lv_label_create(view->obj);
    lv_label_set_text(labelP, "P");
    labelI = lv_label_create(view->obj);
    lv_label_set_text(labelI, "I");
    labelD = lv_label_create(view->obj);
    lv_label_set_text(labelD, "D");

    //creating type buttons
    imgbuttonType = lv_btn_create(view->obj);
    lv_imgbtn_set_src(imgbuttonType, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/typeLeft.png","S:/uiLIB/typeMiddle.png","S:/uiLIB/typeRight.png");


    //creating the PID buttons
    imgButtonPDec = lv_imgbtn_create(view->obj);
    lv_imgbtn_set_src(imgButtonPDec, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_imgbtn_set_src(imgButtonPDec, LV_IMGBTN_STATE_PRESSED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_obj_set_size(imgButtonPDec, 50, 50);
    lv_obj_align(imgButtonPDec, LV_ALIGN_CENTER, -50, 0);

    imgButtonPInc = lv_imgbtn_create(view->obj);
    lv_imgbtn_set_src(imgButtonPInc, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/plusLeft.png","S:/uiLIB/plusMiddle.png","S:/uiLIB/plusRight.png");
    lv_imgbtn_set_src(imgButtonPInc, LV_IMGBTN_STATE_PRESSED, "S:/uiLIB/plusLeft.png","S:/uiLIB/plusMiddle.png","S:/uiLIB/plusRight.png");
    lv_obj_set_size(imgButtonPInc, 50, 50);
    lv_obj_align(imgButtonPInc, LV_ALIGN_CENTER, 50, 0);

    imgButtonIDec = lv_imgbtn_create(view->obj);
    lv_imgbtn_set_src(imgButtonIDec, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_imgbtn_set_src(imgButtonIDec, LV_IMGBTN_STATE_PRESSED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_obj_set_size(imgButtonIDec, 50, 50);
    lv_obj_align(imgButtonIDec, LV_ALIGN_CENTER, -50, 50);

    imgButtonIInc = lv_imgbtn_create(view->obj);
    lv_imgbtn_set_src(imgButtonIInc, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/plusLeft.png","S:/uiLIB/plusMiddle.png","S:/uiLIB/plusRight.png");
    lv_imgbtn_set_src(imgButtonIInc, LV_IMGBTN_STATE_PRESSED, "S:/uiLIB/plusLeft.png","S:/uiLIB/plusMiddle.png","S:/uiLIB/plusRight.png");
    lv_obj_set_size(imgButtonIInc, 50, 50);
    lv_obj_align(imgButtonIInc, LV_ALIGN_CENTER, 50, 50);

    imgButtonDDec = lv_imgbtn_create(view->obj);
    lv_imgbtn_set_src(imgButtonDDec, LV_IMGBTN_STATE_RELEASED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_imgbtn_set_src(imgButtonDDec, LV_IMGBTN_STATE_PRESSED, "S:/uiLIB/minusLeft.png","S:/uiLIB/minusMiddle.png","S:/uiLIB/minusRight.png");
    lv_obj_set_size(imgButtonDDec, 50, 50);
    lv_obj_align(imgButtonDDec, LV_ALIGN_CENTER, -50, 100);
    lv_obj_add_event_cb(imgButtonDDec, eventHandler, LV_EVENT_CLICKED, NULL);






}

void rd::PIDView::focus(){
    rd_view_focus(this->view);
}

void rd::PIDView::updateFromSD(float kP, float kI, float kD){
    //add later
}

