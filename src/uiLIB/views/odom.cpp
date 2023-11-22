// File: src/uiLIB/views/odom.cpp
// @Brief: Odometry view implementation
// @Credit: Using Robodash's View, also partially using Lemlib's Pose functions
// @Description: Image of field, robot that updates position, and stats of robot's pose on the right
#include "uiLIB/views/odom.hpp"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/widgets/lv_img.h"
#include "liblvgl/widgets/lv_label.h"
#include "main.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
rd::OdomView::OdomView() {
    //creating view named odomview
    this->view = rd_view_create("odomview");

    //setting variables
    this->x = 0;
    this->y = 0;
    this->theta = 0;
    this->timer = 0;

    //creating images
    field = lv_img_create(view->obj);
    lv_img_set_src(field, "S:/uiLIB/field.png");
    robot = lv_img_create(view->obj);
    lv_img_set_src(robot, "S:/uiLIB/robot.png");

    //creating changing images

    MatchState = lv_img_create(view->obj);
    lv_img_set_src(MatchState, "S:/uiLIB/DisconnectedState.png");
    DisabledState = lv_img_create(view->obj);
    lv_img_set_src(DisabledState, "S:/uiLIB/DisconnectedState.png");
 
    //creating labels
    labelTitle = lv_label_create(view->obj);
    lv_label_set_text(labelTitle, "Odometry");
    labelX = lv_label_create(view->obj);
    lv_label_set_text(labelX, "X");
    labelY = lv_label_create(view->obj);
    lv_label_set_text(labelY, "Y");
    labelTheta = lv_label_create(view->obj);
    lv_label_set_text(labelTheta, "θ");

    //creating variable labels

    labelXVar = lv_label_create(view->obj);
    lv_label_set_text(labelXVar, "0");
    labelYVar = lv_label_create(view->obj);
    lv_label_set_text(labelYVar, "0");
    labelThetaVar = lv_label_create(view->obj);
    lv_label_set_text(labelThetaVar, "0");

    //creating timer label
    timerVarMin = lv_label_create(view->obj);
    timerVarSec = lv_label_create(view->obj);
    lv_label_set_text(timerVarMin, "0:");
    lv_label_set_text(timerVarSec, "00");
    
    

}
void rd::OdomView::update(float posX, float posY, float posTheta){
    this->x = posX;
    this->y = posY;
    this->theta = posTheta;
    timer = pros::millis();
    timerMin = (timer/1000)/60;
    timerSec = (timer/1000)%60;
    isConnected = pros::competition::is_connected();
    isAuton = pros::competition::is_autonomous();
    isDisabled = pros::competition::is_disabled();
}

void rd::OdomView::updateLabels(){
    lv_label_set_text(labelXVar, (std::to_string(x)).c_str());
    lv_label_set_text(labelYVar, (std::to_string(y)).c_str());
    lv_label_set_text(labelThetaVar, (std::to_string(theta)).c_str());
    lv_label_set_text(timerVarMin, (std::to_string(timerMin)).c_str());
    lv_label_set_text(timerVarSec, (std::to_string(timerSec)).c_str());
    
}
void rd::OdomView::updateImage(){
    lv_obj_set_pos(robot, x, y);
    lv_img_set_angle(robot, theta*10);
}

void rd::OdomView::updateState(){
    if(isConnected){
        if(isAuton){
            lv_img_set_src(MatchState, "S:/uiLIB/Auton.png");
        }
        else{
            lv_img_set_src(MatchState, "S:/uiLIB/OP.png");
        }
        if(isDisabled){
            lv_img_set_src(DisabledState, "S:/uiLIB/Disabled.png");
        }
        else{
            lv_img_set_src(DisabledState, "S:/uiLIB/Enabled.png");
        }

    }
    else{
        lv_img_set_src(MatchState, "S:/uiLIB/DisconnectedState.png");
        lv_img_set_src(DisabledState, "S:/uiLIB/DisconnectedState.png");
    
    }
}
void rd::OdomView::focus(){
    rd_view_focus(this->view);
}