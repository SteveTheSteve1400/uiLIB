#include "liblvgl/core/lv_obj.h"
#include "robodash/api.h"
#include "robodash/views/image.hpp"
#include <string>
#include <sys/types.h>
#pragma once

namespace rd{
    class PIDView{
        private:
            rd_view_t *view;

            //PID vars
            static float kP;
            static float kI;
            static float kD;

            //chart
            lv_obj_t * chart;

            //chart series
            lv_chart_series_t * seriesP;
            lv_chart_series_t * seriesD;

            lv_chart_series_t * seriesTarg;
            lv_chart_series_t * seriesCur;

            //still labels
            lv_obj_t * labelTitle;//added to button later
            lv_obj_t * labelP;
            lv_obj_t * labelI;
            lv_obj_t * labelD;

            //still buttons
            lv_obj_t * imgbuttonType;//added to label later

            static lv_obj_t * imgButtonPDec;
            static lv_obj_t * imgButtonPInc;
            static lv_obj_t * imgButtonIDec;
            static lv_obj_t * imgButtonIInc;
            static lv_obj_t * imgButtonDDec;
            static lv_obj_t * imgButtonDInc;

            //changing labels
            lv_obj_t * labelPVar;
            lv_obj_t * labelIVar;
            lv_obj_t * labelDVar;

        public:
            //rd functions
            PIDView();
            void focus();
            
            //event handler
            static void eventHandler(lv_event_t * event);
            
            //updates
            void updateFromSD(float kP, float kI, float kD);
            void updateLabels();
            void updateChart(float P, float D, float target, float current);

    };
}